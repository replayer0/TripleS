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
    m_functorAdapter = new FunctorAdapter < PACKET_TYPE, PACKET_PTR& > ;
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

bool TripleS::TcpService::RegistFunctor(PACKET_TYPE key, TcpFunctor* base_functor)
{
    return m_functorAdapter->Regist(key, base_functor);
}

bool TripleS::TcpService::RegistFunction(UInt32 key, void(*func)(PACKET_PTR&))
{
    return RegistFunctor(key, new TripleS::FunctionFunctor<void(*)(PACKET_PTR&), PACKET_PTR&>(func));
}

void TripleS::TcpService::_Release()
{
    if (m_proactor != NULL)
    {
        delete[] m_proactor;
        m_proactor = NULL;
    }

    if (m_tcp_listen_socket != NULL)
    {
        delete[] m_tcp_listen_socket;
        m_tcp_listen_socket = NULL;
    }

    if (m_acceptor != NULL)
    {
        delete[] m_acceptor;
        m_acceptor = NULL;
    }

    if (m_disconnector != NULL)
    {
        delete[] m_disconnector;
        m_disconnector = NULL;
    }

    if (m_sender != NULL)
    {
        delete[] m_sender;
        m_sender = NULL;
    }

    if (m_receiver != NULL)
    {
        delete[] m_receiver;
        m_receiver = NULL;
    }

    if (m_functorAdapter != NULL)
    {
        delete[] m_functorAdapter;
        m_functorAdapter = NULL;
    }
}