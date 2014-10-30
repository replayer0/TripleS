#pragma once

#define BUFSIZE 8192

#include "TcpAct.h"
#include "FowardDeclaration.h"

namespace TripleS 
{
    class Proactor;
    class Acceptor;
    class Disconnector;
    class Sender;
    class Receiver;

    class TcpSocket DEBUG_PARENT(TcpSocket)
    {

    public:
        TcpSocket();
        ~TcpSocket()
        {
        }

    public:
        void Init();
        void InitBuf();
        void InitAct(Proactor* proactor, 
            Acceptor* acceptor,
            Disconnector* disconnector,
            Sender* sender,
            Receiver* receiver);

        SOCKET GetSocket() const;

    public:
        void Recv();
        void Send(BYTE* buf, int buflen);
        void Reuse();
        void Disconnect();

    public:
        enum ACT_TYPE
        {
            ACT_SEND = 0,
            ACT_RECV,
            ACT_ACCEPT,
            ACT_DISCONNECT,
            ACT_TYPE_CNT
        };

        TcpAct			Act_[ACT_TYPE_CNT];

    public:
        char			AcceptBuf_[BUFSIZE];

        char			RecvBuf_[BUFSIZE];
        char			SendBuf_[BUFSIZE];

        WSABUF			wsaRecvBuf;
        WSABUF			wsaSendBuf;

    private:
        SOCKET			m_socket;
        SOCKADDR_IN		m_addr;

        Proactor* m_proactor;
        Acceptor* m_acceptor;
        Disconnector* m_disconnector;
        Sender* m_sender;
        Receiver* m_receiver;
    };
}