#pragma once

#include "Actor.h"

#include "TcpAct.h"
#include "TcpListenSocket.h"
#include "TcpSocket.h"
#include "FowardDeclaration.h"

//--------------------------------------------------------
// 이름 :	Acceptor
//
// 역할 :	1)  ACT의 Complete()에서 ProcEvent() 콜
//			2)	ACT의 Error()에서 ProcError() 콜
//			3)  Register()을 통해 AcceptEx() 소켓풀에 넣음
//
// 기타	:	Actor 의 SubClass
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