#pragma once

#include "WinSock.h"
#include "FowardDeclaration.h"

namespace TripleS 
{
    class Proactor;

    class TcpListenSocket DEBUG_PARENT(TcpListenSocket)
    {

    public:
        TcpListenSocket();

        void Init(WORD port, int backlogsize = 0);
        void Listen(TripleS::P_PROACTOR proactor);
        SOCKET GetSocket() const;

    private:
        SOCKET		m_listen_socket;
        SOCKADDR_IN m_socket_addr;

        // 아직 미결인 연결들에 대한 연결 요청 큐의 늘어날 수 있는 최대 길이
        int			m_backlog_size;
    };
}