#pragma once
/*******************************************************************************
**  Name : TcpListenSocket
**  Auth : 임상수
**  Date : 2014-09-17
**  Desc : Win Tcp Listen 동작을 정의한 클래스
********************************************************************************
**  Todo : 
********************************************************************************
**  Date:    Author:    Description:
**  -------- ---------- --------------------------------------------------------
**  임상수   2014-09-17 파일 작성
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

            // 아직 미결인 연결들에 대한 연결 요청 큐의 늘어날 수 있는 최대 길이
            int			m_backlog_size;
        };
    }
}