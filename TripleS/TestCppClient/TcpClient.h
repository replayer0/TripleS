#pragma once
#ifndef _HEADER_TCP_CLIENT_
#define _HEADER_TCP_CLIENT_

/***************************************************************************************************
**  Name : TcpClient
**  Auth : 임상수
**  Date : 2014-5-22
**  Desc : 기본 TCP/IP 클라이언트,
**         지금은 예외처리를 줄여 가독성을 올리는데 주력하였다. 발표 후 예외처리를 추가할 예정이다.
****************************************************************************************************
**  Todo : 예외처리, 패킷조립
****************************************************************************************************
**  Author:         Date:               Description:
**  -----------     ----------------    ------------------------------------------------------------
**  임상수          2014-5-22           파일 생성
***************************************************************************************************/

#pragma  comment(lib, "ws2_32")
#include <WinSock2.h>

class TcpClient
{
public:
    void Initialize(const char* ip = "127.0.0.1", const u_short port = 9000);
    void Run();
    void Release();

protected:
    TcpClient(void);
    virtual ~TcpClient(void);

private:
    virtual void _Working(SOCKET client_sock) = 0;

    SOCKET      m_connect_sock;
    SOCKADDR_IN server_addr;
};

#endif //_HEADER_TCP_CLIENT_
