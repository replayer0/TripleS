#pragma once

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

namespace TripleS 
{
    class TcpService : public Service DEBUG_PARENTS(TcpService)
    {
    public:
        void Start(BaseIocpDesc desc);
        void Join();

    private:
        TripleS::P_TCPLISTENSOCKET m_tcp_listen_socket;
        TripleS::P_PROACTOR m_proactor;
        TripleS::P_ACCEPTOR m_acceptor;
        TripleS::P_DISCONNECTOR m_disconnector;
        TripleS::P_SENDER m_sender;
        TripleS::P_RECEIVER m_receiver;
        TripleS::P_THREADS  m_threads;
    };
};