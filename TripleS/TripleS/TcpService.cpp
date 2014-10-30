#include "stdafx.h"

#include "TcpService.h"
#include "TcpListenSocket.h"
#include "Threads.h"
#include "Proactor.h"
#include "Acceptor.h"
#include "Disconnector.h"
#include "Sender.h"
#include "Receiver.h"

TripleS::TcpService::~TcpService()
{
}

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

    // todo:: 아래부분을 어떻게 뺼것인가.. 걍 다시 proactor에 넣을까.. 아니면 최상위 인터페이스에서 어찌..
    // 키값의 관리와 다양한 종류의 스레드를 생성하려면..
    //iocpServer가 차라리 Threads를 상속??
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

    for (unsigned int i = 0; i < desc.m_accept_pool_size; i++)
    {
        TcpSocket* socket = new TcpSocket;
        socket->Init();
        socket->InitAct(m_proactor.get(), m_acceptor.get(), m_disconnector.get(), m_sender.get(), m_receiver.get());

        m_acceptor->Register(*socket);
    }
}

void TripleS::TcpService::Join()
{
    m_threads->Join();
}