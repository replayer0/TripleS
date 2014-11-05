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
    class TcpService DEBUG_PARENT(TcpService)
    {
    public:
        TcpService(service_desc desc);
        ~TcpService();

        void Start();
        void RegistSocket(TcpSocket* tcp_socket); //이 함수는 리슨상태 이후에 호출되어야한다(Start)

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