#pragma once

#include "WinSock.h"
#include "FowardDeclaration.h"

namespace TripleS 
{
    class Proactor;

    class TcpListenSocket DEBUG_PARENT(TcpListenSocket)
    {

    public:
        TcpListenSocket(WORD port, int backlogsize, Proactor& proactor);

        void Listen();
        SOCKET GetSocket() const;

    private:
        void _Init(WORD port, int backlogsize);

        SOCKET		m_listen_socket { 9000 };
        SOCKADDR_IN m_socket_addr;
        int			m_backlog_size { 0 };
        Proactor&   m_proactor;
    };
}