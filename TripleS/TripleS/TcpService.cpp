#include "stdafx.h"

#include "TcpService.h"
#include "TcpListenSocket.h"
#include "Threads.h"
#include "Proactor.h"
#include "Acceptor.h"
#include "Disconnector.h"
#include "Sender.h"
#include "Receiver.h"

void TripleS::TcpService::Start(service_desc desc)
{
    m_threads = TripleS::P_THREADS(new TripleS::Threads(std::thread::hardware_concurrency() * 4));
    m_proactor = TripleS::P_PROACTOR(new Proactor(m_threads));
    m_tcp_listen_socket = TripleS::P_TCPLISTENSOCKET(new TcpListenSocket);
    m_acceptor = TripleS::P_ACCEPTOR(new Acceptor);
    m_disconnector = TripleS::P_DISCONNECTOR(new Disconnector);
    m_sender = TripleS::P_SENDER(new Sender);
    m_receiver = TripleS::P_RECEIVER(new Receiver);

    m_proactor->Init();

    // todo:: �Ʒ��κ��� ��� �E���ΰ�.. �� �ٽ� proactor�� ������.. �ƴϸ� �ֻ��� �������̽����� ����..
    // Ű���� ������ �پ��� ������ �����带 �����Ϸ���..
    //iocpServer�� ���� Threads�� ���??
    for (unsigned int thread_idx = 0; //std::thread::hardware_concurrency();
        thread_idx < desc.m_begin_thread_count; ++thread_idx)
    {
        ThreadParameter* input_param = new ThreadParameter(m_proactor.get());
        input_param->SetThreadIndex(thread_idx);

        m_threads->Regist(thread_idx, Proactor::ThreadProc, input_param);
        Sleep(200);
    }

    m_tcp_listen_socket->Init(desc.m_port);
    m_tcp_listen_socket->Listen(m_proactor);

    m_acceptor->Init(m_tcp_listen_socket, m_proactor);

    m_disconnector->Init(m_proactor);

    m_sender->Init(m_proactor);

    m_receiver->Init(m_proactor);


    /*for (unsigned int i = 0; i < desc.m_accept_pool_size; i++)
    {
        TcpSocket* socket = new TcpSocket;
        socket->Init();
        socket->InitAct(m_proactor, m_acceptor, m_disconnector, m_sender, m_receiver);

        m_acceptor->Register(*socket);
        // ���� socket�� ���� �޸� ������ �ȵǼ� ������ ���� �߻��Ѵ�.
    }*/
}

void TripleS::TcpService::Join()
{
    m_threads->Join();
}

void TripleS::TcpService::Release()
{
    m_tcp_listen_socket.reset();
    m_proactor.reset();
    m_acceptor.reset();
    m_disconnector.reset();
    m_sender.reset();
    m_receiver.reset();
    m_threads.reset();
}

TripleS::TcpService::~TcpService()
{
    Release();
}
