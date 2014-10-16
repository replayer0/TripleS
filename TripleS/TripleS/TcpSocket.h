#pragma once

#define BUFSIZE 8192

#include "TcpAct.h"
#include "FowardDeclaration.h"

namespace TripleS {
    namespace iocp {
        class Proactor;
        class Acceptor;
        class Disconnector;
        class Sender;
        class Receiver;

        class TcpSocket DEBUG_PARENT(TcpSocket)
        {

        public:
            TcpSocket();

        public:
            void Init();
            void InitBuf();
            void InitAct(TripleS::type::P_PROACTOR proactor, 
                TripleS::type::P_ACCEPTOR acceptor,
                TripleS::type::P_DISCONNECTOR disconnector,
                TripleS::type::P_SENDER sender,
                TripleS::type::P_RECEIVER receiver);

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
            SOCKET			Socket_;
            SOCKADDR_IN		Addr_;

        public:
            char			AcceptBuf_[BUFSIZE];

            char			RecvBuf_[BUFSIZE];
            char			SendBuf_[BUFSIZE];

            WSABUF			wsaRecvBuf;
            WSABUF			wsaSendBuf;

        private:
            TripleS::type::P_PROACTOR Proactor_;
            TripleS::type::P_ACCEPTOR Acceptor_;
            TripleS::type::P_DISCONNECTOR Disconnector_;
            TripleS::type::P_SENDER Sender_;
            TripleS::type::P_RECEIVER Receiver_;

        };
    }
}