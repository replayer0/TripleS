#pragma once

#include "WinSock.h"
#include "MSWSock.h"
#include "BaseIocp_parameter.h"

/*******************************************************************************
**  Name : TcpConnectSocket
**  Auth : 임상수
**  Date : 2014-12-03
**  Desc :
********************************************************************************
**  Todo : 미완성 클래스 입니다.
*******************************************************************************/

namespace TripleS
{
    class Proactor;

    class TcpConnectSocket
    {
    public:
        TcpConnectSocket();

        void Connect();
        SOCKET GetSocket() const;
    private:
        void _Init();

        SOCKET		m_connect_socket{ INVALID_SOCKET };
        SOCKADDR_IN m_socket_addr;
        int			m_backlog_size{ 0 };
        LPFN_CONNECTEX ConnectEx;
    };
}