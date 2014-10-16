#include "stdafx.h"

#include "TcpService.h"
#include "TcpListenSocket.h"
#include "Threads.h"
#include "Proactor.h"
#include "Acceptor.h"
#include "Disconnector.h"
#include "Sender.h"
#include "Receiver.h"

void TripleS::iocp::TcpService::Start(BaseIocpDesc desc)
{
    m_threads = TripleS::type::P_THREADS(new TripleS::util::Threads(128));
    m_proactor = TripleS::type::P_PROACTOR(new Proactor(m_threads));
    m_tcp_listen_socket = TripleS::type::P_TCPLISTENSOCKET(new TcpListenSocket);
    m_acceptor = TripleS::type::P_ACCEPTOR(new Acceptor);
    m_disconnector = TripleS::type::P_DISCONNECTOR(new Disconnector);
    m_sender = TripleS::type::P_SENDER(new Sender);
    m_receiver = TripleS::type::P_RECEIVER(new Receiver);

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

    m_tcp_listen_socket->Init(9000);
    m_tcp_listen_socket->Listen(m_proactor);

    m_acceptor->Init(m_tcp_listen_socket, m_proactor);

    m_disconnector->Init(m_proactor);

    m_sender->Init(m_proactor);

    m_receiver->Init(m_proactor);

    for (int i = 0; i < 10; i++)
    {
        TcpSocket* socket = new TcpSocket;
        socket->Init();
        socket->InitAct(m_proactor, m_acceptor, m_disconnector, m_sender, m_receiver);

        m_acceptor->Register(*socket);
        // ���� socket�� ���� �޸� ������ �ȵǼ� ������ ���� �߻��Ѵ�.
    }
}

void TripleS::iocp::TcpService::Join()
{
    m_threads->Join();
}
