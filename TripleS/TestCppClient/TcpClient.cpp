#include "TcpClient.h"
#include <stdio.h>

TcpClient::TcpClient(void)
{
}

TcpClient::~TcpClient(void)
{
    Release();
}

void TcpClient::Initialize( const char* ip /*= "127.0.0.1"*/, const u_short port /*= 9000*/ )
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    m_connect_sock = socket(AF_INET, SOCK_STREAM, 0);

    ZeroMemory(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);
}

void TcpClient::Run()
{
    if (connect(m_connect_sock, (SOCKADDR *)&server_addr, sizeof(server_addr)) != SOCKET_ERROR)
    {
        printf("연결 성공\n");
        this->_Working(m_connect_sock);
    }
    else
    {
        printf("연결 실패\n");
    }
}

void TcpClient::Release()
{
    closesocket(m_connect_sock);

    WSACleanup();
}
