#pragma once

/*******************************************************************************
**  Name :
**  Auth : �ӻ��
**  Date : 2014-09-18
**  Desc :
********************************************************************************
**  Todo :
********************************************************************************
**  Date:    Author:    Description:
**  -------- ---------- --------------------------------------------------------
**  �ӻ��   2014-09-18 ���� ����
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
        ~TcpService();

        void Start(service_desc desc);

    private:
        TcpListenSocket* m_tcp_listen_socket;
        Proactor* m_proactor;
        Acceptor* m_acceptor;
        Disconnector* m_disconnector;
        Sender* m_sender;
        Receiver* m_receiver;
    };
};