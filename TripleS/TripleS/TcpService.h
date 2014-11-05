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
    class TcpService DEBUG_PARENT(TcpService)
    {
    public:
        TcpService(service_desc desc);
        ~TcpService();

        void Start();
        void RegistSocket(TcpSocket* tcp_socket); //�� �Լ��� �������� ���Ŀ� ȣ��Ǿ���Ѵ�(Start)

    private:
        void _Release();

        TcpListenSocket*m_tcp_listen_socket { NULL };
        Proactor*       m_proactor          { NULL };
        Acceptor*       m_acceptor          { NULL };
        Disconnector*   m_disconnector      { NULL };
        Sender*         m_sender            { NULL };
        Receiver*       m_receiver          { NULL };
    };
};