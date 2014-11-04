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
    delete[] m_proactor;
    delete[] m_tcp_listen_socket;
    delete[] m_acceptor;
    delete[] m_disconnector;
    delete[] m_sender;
    delete[] m_receiver;
}

void TripleS::TcpService::Start(service_desc desc)
{
    m_proactor = new Proactor(desc.m_thread_desc);
    m_tcp_listen_socket = new TcpListenSocket(desc.m_port, desc.m_backlog_size, *m_proactor);
    m_acceptor = new Acceptor(*m_tcp_listen_socket, *m_proactor);
    m_disconnector = new Disconnector(*m_proactor);
    m_sender = new Sender(*m_proactor);
    m_receiver = new Receiver(*m_proactor);

    m_tcp_listen_socket->Listen();

    for (unsigned int i = 0; i < desc.m_accept_pool_size; i++)
    {
        /*TcpSocket* socket = new TcpSocket;
        socket->Init();
        socket->InitAct(m_proactor.get(), m_acceptor.get(), m_disconnector.get(), m_sender.get(), m_receiver.get());

        m_acceptor->Register(*socket);*/
    }
}