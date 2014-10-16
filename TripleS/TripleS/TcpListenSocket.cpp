#include "stdafx.h"
#include "TcpListenSocket.h"
#include "Proactor.h"

TripleS::iocp::TcpListenSocket::TcpListenSocket()
{
    m_backlog_size = 0;
}

void TripleS::iocp::TcpListenSocket::Init(WORD port, int backlogsize /*= 0*/)
{
    m_listen_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

    m_socket_addr.sin_family = AF_INET;
    m_socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_socket_addr.sin_port = htons(port);

    m_backlog_size = backlogsize;
}

void TripleS::iocp::TcpListenSocket::Listen(TripleS::type::P_PROACTOR proactor)
{
    proactor->Register(reinterpret_cast<HANDLE>(m_listen_socket));

    bind(m_listen_socket, (SOCKADDR*)&m_socket_addr, sizeof(m_socket_addr));
    listen(m_listen_socket, m_backlog_size);
}

SOCKET TripleS::iocp::TcpListenSocket::GetSocket() const
{
    return m_listen_socket;
}
