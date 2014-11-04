#include "stdafx.h"
#include "TcpListenSocket.h"
#include "Proactor.h"

TripleS::TcpListenSocket::TcpListenSocket(listen_desc desc, Proactor& proactor)
    : m_proactor(proactor)
{
    _Init(desc.m_port, desc.m_backlog_size);
}

void TripleS::TcpListenSocket::_Init(WORD port, int backlogsize)
{
    m_listen_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

    m_socket_addr.sin_family = AF_INET;
    m_socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_socket_addr.sin_port = htons(port);

    m_backlog_size = backlogsize;
}

void TripleS::TcpListenSocket::Listen()
{
    m_proactor.Register(reinterpret_cast<HANDLE>(m_listen_socket));

    bind(m_listen_socket, (SOCKADDR*)&m_socket_addr, sizeof(m_socket_addr));
    listen(m_listen_socket, m_backlog_size);
    DEBUG_INFO(eDEBUG_LOW, "start listen (%d)", m_listen_socket);
}

SOCKET TripleS::TcpListenSocket::GetSocket() const
{
    return m_listen_socket;
}
