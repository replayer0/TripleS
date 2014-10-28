#pragma once

#include "Actor.h"
#include "TcpAct.h"
#include "TcpSocket.h"
//--------------------------------------------------------
// 이름 :	Sender
//
// 역할 :	1)  ACT의 Complete()에서 ProcEvent() 콜
//			2)	ACT의 Error()에서 ProcError() 콜
//
// 기타	:	Actor 의 SubClass
//--------------------------------------------------------

namespace TripleS
{
    class Sender : public Actor DEBUG_PARENTS(Sender)
    {
    public:
        Sender(){};

    public:
        void ProcEvent(Act* act, DWORD bytes_transferred)
        {
            // assert(dynamic_cast<TcpAct*>(act));

            TcpAct& tcpact = *dynamic_cast<TcpAct*>(act);

            // assert(tcpact.TcpSocket_);

            TcpSocket& tcpsocket = *tcpact.TcpSocket_;

            //printf("...Sender (%d byte) s(%d)\n", bytes_transferred, tcpsocket.GetSocket() );
        }

        void ProcError(Act* act, DWORD error)
        {
            // assert(dynamic_cast<TcpAct*>(act));

            TcpAct& tcpact = *dynamic_cast<TcpAct*>(act);

            // assert(tcpact.TcpSocket_);

            TcpSocket& tcpsocket = *tcpact.TcpSocket_;

            //printf("...에러처리 Sender s(%d) err(%d)\n", tcpsocket.GetSocket(), error);
        }

        void Init(TripleS::P_PROACTOR proactor)
        {
            Proactor_ = proactor;
        }
    };
}