#pragma once

#include <memory>
#include "WinSock.h"
#include "WSA.h"
#include "BaseIocp_parameter.h"
#include "TcpSocket.h"

namespace TripleS 
{
    class TcpListenSocket;
    class Proactor;
    class Acceptor;
    class Disconnector;
    class Sender;
    class Receiver;

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

        friend TcpSocket::TcpSocket(TcpService& tcp_service);
    };
};