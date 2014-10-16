#pragma once

#include "Actor.h"

#include "TcpAct.h"
#include "TcpListenSocket.h"
#include "TcpSocket.h"
#include "FowardDeclaration.h"

//--------------------------------------------------------
// �̸� :	Acceptor
//
// ���� :	1)  ACT�� Complete()���� ProcEvent() ��
//			2)	ACT�� Error()���� ProcError() ��
//			3)  Register()�� ���� AcceptEx() ����Ǯ�� ����
//
// ��Ÿ	:	Actor �� SubClass
//--------------------------------------------------------

namespace TripleS {
    namespace iocp {
        class Acceptor : public Actor DEBUG_PARENTS(Acceptor)
        {
        public:
            Acceptor(){};

        public:
            void ProcEvent(Act* act, DWORD bytes_transferred);
            void ProcError(Act* act, DWORD error);

            void Init(TripleS::type::P_TCPLISTENSOCKET tcplistensocket, 
                TripleS::type::P_PROACTOR proactor);

            void Register(TcpSocket& acceptsocket);

        public:
            TripleS::type::P_TCPLISTENSOCKET TcpListenSocket_;
        };
    }
}