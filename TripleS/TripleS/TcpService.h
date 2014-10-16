#pragma once
#ifndef _TRIPLE_S_TCP_SERVICE_H
#define _TRIPLE_S_TCP_SERVICE_H
/*******************************************************************************
**  Name :
**  Auth : 임상수
**  Date : 2014-09-18
**  Desc :
********************************************************************************
**  Todo :
********************************************************************************
**  Date:    Author:    Description:
**  -------- ---------- --------------------------------------------------------
**  임상수   2014-09-18 파일 생성
*******************************************************************************/

#include <memory>
#include "WinSock.h"
#include "Service.h"
#include "BaseIocp_parameter.h"

namespace TripleS {
    namespace iocp {
        class TcpService : public Service DEBUG_PARENTS(TcpService)
        {
        public:
            void Start(BaseIocpDesc desc);
            void Join();

        private:
            TripleS::type::P_TCPLISTENSOCKET m_tcp_listen_socket;
            TripleS::type::P_PROACTOR m_proactor;
            TripleS::type::P_ACCEPTOR m_acceptor;
            TripleS::type::P_DISCONNECTOR m_disconnector;
            TripleS::type::P_SENDER m_sender;
            TripleS::type::P_RECEIVER m_receiver;
            TripleS::type::P_THREADS  m_threads;
        };
    };
};

#endif // _TRIPLE_S_TCP_SERVICE_H