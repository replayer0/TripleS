#include "stdafx.h"
#include "TcpConnectSocket.h"
#include "Proactor.h"

TripleS::TcpConnectSocket::TcpConnectSocket()
{
    _Init();
}

void TripleS::TcpConnectSocket::_Init()
{
    SOCKET temp_socket;
    temp_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (temp_socket == INVALID_SOCKET)
    {
        printf("%s\n", WSAGetLastError());
        return;
    }

    GUID guid = WSAID_CONNECTEX;
    DWORD bytes;

    WSAIoctl(temp_socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guid,
        sizeof(guid), &ConnectEx, sizeof(ConnectEx), &bytes, NULL, NULL);

    closesocket(temp_socket);
}

void TripleS::TcpConnectSocket::Connect()
{
    memset(&m_socket_addr, 0, sizeof(m_socket_addr));
    m_socket_addr.sin_family = AF_INET;
    m_socket_addr.sin_addr.s_addr = INADDR_ANY;
    m_socket_addr.sin_port = 0;

    m_connect_socket = socket(AF_INET, SOCK_STREAM, 0);
    int ret = bind(m_connect_socket, (SOCKADDR*)&m_socket_addr, sizeof(m_socket_addr));
    if (ret != 0)
    {
        printf("%s\n", WSAGetLastError());
        return;
    }

    setsockopt(m_connect_socket, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, NULL, 0);

    memset(&m_socket_addr, 0, sizeof(m_socket_addr));
    m_socket_addr.sin_family = AF_INET;
    m_socket_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    m_socket_addr.sin_port = htons(9000);

    ret = ConnectEx(m_connect_socket, (LPSOCKADDR)&m_socket_addr, sizeof(m_socket_addr),
        NULL, 0, NULL, 0);
    if (ret != 0)
    {
        printf("%s\n", WSAGetLastError());
        return;
    }
}

SOCKET TripleS::TcpConnectSocket::GetSocket() const
{
    return m_connect_socket;
}
