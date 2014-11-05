#pragma once

#include "Actor.h"
#include "TcpAct.h"
#include "TcpSocket.h"

//--------------------------------------------------------
// �̸� :	Receiver.h
//
// ���� :	1)  ACT�� Complete()���� ProcEvent() ��
//			2)	ACT�� Error()���� ProcError() ��
//
// ��Ÿ	:	Actor �� SubClass
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

            // passive �������
            if (bytes_transferred == 0)
            {
                tcpsocket.Disconnect();
            }
            else
            {
                //printf("���� �� = %s\n", tcpsocket.RecvBuf_);

                // Async Recv ����Ʈ
                // tcpsocket.Recv();

				tcpsocket.RecvCompleted( act, m_proactor,  bytes_transferred );

                //������ŭ ����
				// �ϴ� �ּ�..
                //tcpsocket.Send((BYTE*)tcpsocket.RecvBuf_, bytes_transferred);
            }

        }

        void ProcError(Act* act, DWORD error)
        {
            //assert(dynamic_cast<TcpAct*>(act));

            TcpAct& tcpact = *dynamic_cast<TcpAct*>(act);

            //assert(tcpact.TcpSocket_);

            TcpSocket& tcpsocket = *tcpact.TcpSocket_;

            //printf("...����ó�� Receiver s(%d) err(%d)\n", tcpsocket.GetSocket(), error );

            tcpsocket.Disconnect();

        }
    };
}