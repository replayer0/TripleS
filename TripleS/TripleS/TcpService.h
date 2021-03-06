#pragma once

#include <memory>
#include "WinSock.h"
#include "WSA.h"
#include "BaseIocp_parameter.h"
#include "TcpSocket.h"
#include "FunctorAdapter.h"
#include "Packet.h"

namespace TripleS 
{
    class TcpListenSocket;
    class Proactor;
    class Acceptor;
    class Disconnector;
    class Sender;
    class Receiver;

    class TcpService DEBUG_PARENT( TcpService )
    {
    public:
        typedef TripleS::BaseFunctor<PACKET_PTR&> TcpFunctor;

    public:
        TcpService(service_desc desc);
        ~TcpService();

        void Start();

        bool RegistFunction(UInt32 key, void(*func)(PACKET_PTR&));
        bool RegistFunctor(UInt32 key, TcpFunctor* base_functor);

    private:
        void _Release();

        TcpListenSocket*m_tcp_listen_socket { NULL };
        Proactor*       m_proactor          { NULL };
        Acceptor*       m_acceptor          { NULL };
        Disconnector*   m_disconnector      { NULL };
        Sender*         m_sender            { NULL };
        Receiver*       m_receiver          { NULL };
        FunctorAdapter<PACKET_TYPE, PACKET_PTR&>* m_functorAdapter{ NULL };

        friend TcpSocket::TcpSocket(TcpService& tcp_service);
        friend bool TcpSocket::Completed(PACKET_TYPE key, PACKET_PTR& packet);
    };
};