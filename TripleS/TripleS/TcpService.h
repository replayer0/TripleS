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
       // typedef TripleS::BaseFunctor<PacketPtr&> TcpFunctor;

    public:
        TcpService(service_desc desc);
        ~TcpService();

        void Start();

<<<<<<< HEAD
//         bool RegistFunction(UInt32 key, void(*func)(PacketPtr&) )
//         {
//             return RegistFunctor(key, new TripleS::FunctionFunctor<void(*)(PacketPtr&), PacketPtr&>(func));
//         }
//         bool RegistFunctor(UInt32 key, TcpFunctor* base_functor)
//         {
//             return m_functorAdapter.Regist(key, base_functor);
//         }
=======
        bool RegistFunction(PACKET_TYPE key, void(*func)(PacketPtr&) );
        bool RegistFunctor(PACKET_TYPE key, TcpFunctor* base_functor);
>>>>>>> origin/master

    private:
        void _Release();

        TcpListenSocket*m_tcp_listen_socket { NULL };
        Proactor*       m_proactor          { NULL };
        Acceptor*       m_acceptor          { NULL };
        Disconnector*   m_disconnector      { NULL };
        Sender*         m_sender            { NULL };
        Receiver*       m_receiver          { NULL };
<<<<<<< HEAD
  //      FunctorAdapter<UInt32, PacketPtr&> m_functorAdapter;
=======
        FunctorAdapter<PACKET_TYPE, PacketPtr&> m_functorAdapter;
>>>>>>> origin/master

        friend TcpSocket::TcpSocket(TcpService& tcp_service);
        friend bool TcpSocket::Completed(PACKET_TYPE key, PacketPtr& packet);
    };
};