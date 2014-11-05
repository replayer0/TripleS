#pragma once

#include "Actor.h"
#include "TcpAct.h"
#include "TcpSocket.h"

//--------------------------------------------------------
// 이름 :	Receiver.h
//
// 역할 :	1)  ACT의 Complete()에서 ProcEvent() 콜
//			2)	ACT의 Error()에서 ProcError() 콜
//
// 기타	:	Actor 의 SubClass
//--------------------------------------------------------

namespace TripleS
{
    class Receiver : public Actor DEBUG_PARENTS(Receiver)
    {
    public:
        Receiver(Proactor& proactor)
            : Actor(proactor)
        {
        }

    public:
        void ProcEvent(Act* act, DWORD bytes_transferred)
        {
            //assert(dynamic_cast<TcpAct*>(act));

            TcpAct& tcpact = *dynamic_cast<TcpAct*>(act);

            //assert(tcpact.TcpSocket_);

            TcpSocket& tcpsocket = *tcpact.TcpSocket_;

            //printf("...Receiver (%d byte) s(%d)\n", bytes_transferred, tcpsocket.GetSocket() );

            // passive 연결끊김
            if (bytes_transferred == 0)
            {
                tcpsocket.Disconnect();
            }
            else
            {
                //printf("받은 값 = %s\n", tcpsocket.RecvBuf_);

                // Async Recv 포스트
                // tcpsocket.Recv();

				tcpsocket.RecvCompleted( act, m_proactor,  bytes_transferred );

                //받은만큼 에코
				// 일단 주석..
                //tcpsocket.Send((BYTE*)tcpsocket.RecvBuf_, bytes_transferred);
            }

        }

        void ProcError(Act* act, DWORD error)
        {
            //assert(dynamic_cast<TcpAct*>(act));

            TcpAct& tcpact = *dynamic_cast<TcpAct*>(act);

            //assert(tcpact.TcpSocket_);

            TcpSocket& tcpsocket = *tcpact.TcpSocket_;

            //printf("...에러처리 Receiver s(%d) err(%d)\n", tcpsocket.GetSocket(), error );

            tcpsocket.Disconnect();

        }
    };
}