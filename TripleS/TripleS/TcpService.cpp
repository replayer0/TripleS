#include "stdafx.h"

#include "TcpService.h"
#include "TcpListenSocket.h"
#include "Threads.h"
#include "Proactor.h"
#include "Acceptor.h"
#include "Disconnector.h"
#include "Sender.h"
#include "Receiver.h"

TripleS::TcpService::TcpService(service_desc desc)
{
    m_proactor = new Proactor(desc.m_thread_desc);
    m_disconnector = new Disconnector(*m_proactor);
    m_sender = new Sender(*m_proactor);
    m_receiver = new Receiver(*m_proactor);
    m_tcp_listen_socket = new TcpListenSocket(desc.m_listen_desc, *m_proactor);
    m_acceptor = new Acceptor(*m_tcp_listen_socket, *m_proactor);
}

TripleS::TcpService::~TcpService()
{
    _Release();
}

void TripleS::TcpService::Start()
{
    m_tcp_listen_socket->Listen();
    m_proactor->RunThread();
}

/*
void TripleS::TcpService::RegistSocket(TcpSocket* tcp_socket)
{
    m_acceptor->Register(*tcp_socket);
}*/

void TripleS::TcpService::_Release()
{
    if (m_proactor != NULL)
    {
        delete[] m_proactor;
    }

    if (m_tcp_listen_socket != NULL)
    {
        delete[] m_tcp_listen_socket;
    }

    if (m_acceptor != NULL)
    {
        delete[] m_acceptor;
    }

    if (m_disconnector != NULL)
    {
        delete[] m_disconnector;
    }

    if (m_sender != NULL)
    {
        delete[] m_sender;
    }

    if (m_receiver != NULL)
    {
        delete[] m_receiver;
    }
}
