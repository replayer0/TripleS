#pragma once

#include "Actor.h"

#include "TcpAct.h"
#include "TcpListenSocket.h"
#include "TcpSocket.h"
#include "FowardDeclaration.h"

#include <queue>

namespace TripleS 
{
    class Acceptor : public Actor DEBUG_PARENTS(Acceptor)
    {
    public:
        Acceptor(){};
        ~Acceptor();

    public:
        void ProcEvent(Act* act, DWORD bytes_transferred);
        void ProcError(Act* act, DWORD error);

        void Init(TripleS::P_TCPLISTENSOCKET tcplistensocket,
            TripleS::P_PROACTOR proactor);

        void Register(TcpSocket& acceptsocket);

    public:
        TripleS::P_TCPLISTENSOCKET TcpListenSocket_;
        std::queue<TcpSocket*> m_sockets;
    };
}