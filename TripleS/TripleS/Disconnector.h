#pragma once

#include "Actor.h"
#include "TcpSocket.h"

namespace TripleS
{
    class Disconnector : public Actor DEBUG_PARENTS(Disconnector)
    {
    public:
        Disconnector(Proactor& proactor)
            : Actor(proactor)
        {
        }

    public:
        void ProcEvent(Act* act, DWORD bytes_transferred)
        {
            TcpAct& tcpact = *dynamic_cast<TcpAct*>(act);

            //assert(tcpact.TcpSocket_);
            TcpSocket& tcpsocket = *tcpact.TcpSocket_;

            //printf("...Disconnector s(%d)\n", tcpsocket.GetSocket());

            //assert(tcpsocket.Acceptor_);

            // ���� ����
            tcpsocket.RegistAccept();
        }

        void ProcError(Act* act, DWORD error)
        {
            //assert(dynamic_cast<TcpAct*>(act));

            TcpAct& tcpact = *dynamic_cast<TcpAct*>(act);

            //assert(tcpact.TcpSocket_);

            TcpSocket& tcpsocket = *tcpact.TcpSocket_;

            printf("...����ó�� Disconnector s(%d) err(%d)\n", tcpsocket.GetSocket(), error);
        }
    };
}