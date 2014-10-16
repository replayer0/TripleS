#pragma once
/*******************************************************************************
**  Name : TcpListenSocket
**  Auth : �ӻ��
**  Date : 2014-09-17
**  Desc : Win Tcp Listen ������ ������ Ŭ����
********************************************************************************
**  Todo : 
********************************************************************************
**  Date:    Author:    Description:
**  -------- ---------- --------------------------------------------------------
**  �ӻ��   2014-09-17 ���� �ۼ�
*******************************************************************************/

#include "WinSock.h"
#include "FowardDeclaration.h"

namespace TripleS 
{
    namespace iocp 
    {
        class Proactor;

        class TcpListenSocket DEBUG_PARENT(TcpListenSocket)
        {

        public:
            TcpListenSocket();

            void Init(WORD port, int backlogsize = 0);
            void Listen(TripleS::type::P_PROACTOR proactor);
            SOCKET GetSocket() const;

        private:
            SOCKET		m_listen_socket;
            SOCKADDR_IN m_socket_addr;

            // ���� �̰��� ����鿡 ���� ���� ��û ť�� �þ �� �ִ� �ִ� ����
            int			m_backlog_size;
        };
    }
}