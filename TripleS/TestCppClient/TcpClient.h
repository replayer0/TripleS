#pragma once
#ifndef _HEADER_TCP_CLIENT_
#define _HEADER_TCP_CLIENT_

/***************************************************************************************************
**  Name : TcpClient
**  Auth : �ӻ��
**  Date : 2014-5-22
**  Desc : �⺻ TCP/IP Ŭ���̾�Ʈ,
**         ������ ����ó���� �ٿ� �������� �ø��µ� �ַ��Ͽ���. ��ǥ �� ����ó���� �߰��� �����̴�.
****************************************************************************************************
**  Todo : ����ó��, ��Ŷ����
****************************************************************************************************
**  Author:         Date:               Description:
**  -----------     ----------------    ------------------------------------------------------------
**  �ӻ��          2014-5-22           ���� ����
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
