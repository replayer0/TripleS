#pragma once

#define BUFSIZE 8192

#include "TcpAct.h"
#include "PacketStream.h"

namespace TripleS 
{
    class Proactor;
    class Acceptor;
    class Disconnector;
    class Sender;
    class Receiver;
    class TcpService;

    class TcpSocket DEBUG_PARENT(TcpSocket)
    {
    public:
        TcpSocket(TcpService& tcp_service);
        ~TcpSocket();

        enum ACT_TYPE
        {
            ACT_SEND = 0,
            ACT_RECV,
            ACT_ACCEPT,
            ACT_DISCONNECT,
            ACT_TYPE_CNT
        };

		void SetTotalRecvSize( const UInt32& size );
		void BuildPacket();
		Int32 RecvCompleted(Act* act, Proactor& proactor, UInt32 len );

		PacketStream& GetRecvBuff() { return RecvBuf; }
        char* GetAcceptBuffer() { return AcceptBuf_; }
        SOCKET GetSocket() const;
        TcpAct& GetAct(ACT_TYPE act_type) { return m_act[act_type]; }

        void Recv();
        void Send(BYTE* buf, int buflen);
        const bool RegistAccept(); // 이름을 못짓겠다..
        const bool Disconnect();

    private:
        TcpAct			m_act[ACT_TYPE_CNT];

        char            AcceptBuf_[BUFSIZE];
        char            SendBuf_[BUFSIZE];

        WSABUF          wsaRecvBuf;
        WSABUF          wsaSendBuf;

		PacketStream    RecvActBuf;	    // 리시브액터가 동작할때 사용하는 버퍼.
		PacketStream    RecvBuf;		// 이게 레알 버퍼.
        UInt32          TotalRecvSize { 0 };

        SOCKET          m_socket{ INVALID_SOCKET };
        SOCKADDR_IN     m_addr;

        Proactor&       m_proactor;
        Acceptor&       m_acceptor;
        Disconnector&   m_disconnector;
        Sender&         m_sender;
        Receiver&       m_receiver;
    };
}