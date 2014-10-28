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

        // ���� �̰��� ����鿡 ���� ���� ��û ť�� �þ �� �ִ� �ִ� ����
        int			m_backlog_size;
    };
}