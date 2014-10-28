#pragma once

#include "Actor.h"
#include "TcpSocket.h"

//--------------------------------------------------------
// 이름 :	Disconnector
//
// 역할 :	1)  ACT의 Complete()에서 ProcEvent() 콜
//			2)	ACT의 Error()에서 ProcError() 콜
//
// 기타	:	Actor 의 SubClass
//--------------------------------------------------------

namespace TripleS
{
    class Disconnector : public Actor DEBUG_PARENTS(Disconnector)
    {
    public:
        Disconnector(){}

    public:
        void ProcEvent(Act* act, DWORD bytes_transferred)
        {
            TcpAct& tcpact = *dynamic_cast<TcpAct*>(act);

            //assert(tcpact.TcpSocket_);
            TcpSocket& tcpsocket = *tcpact.TcpSocket_;

            //printf("...Disconnector s(%d)\n", tcpsocket.GetSocket());

            //assert(tcpsocket.Acceptor_);

            // 소켓 재사용
            tcpsocket.Reuse();
        }

        void ProcError(Act* act, DWORD error)
        {
            //assert(dynamic_cast<TcpAct*>(act));

            TcpAct& tcpact = *dynamic_cast<TcpAct*>(act);

            //assert(tcpact.TcpSocket_);

            TcpSocket& tcpsocket = *tcpact.TcpSocket_;

            printf("...에러처리 Disconnector s(%d) err(%d)\n", tcpsocket.GetSocket(), error);
        }

        void Init(TripleS::P_PROACTOR proactor)
        {
            Proactor_ = proactor;
        }
    };
}