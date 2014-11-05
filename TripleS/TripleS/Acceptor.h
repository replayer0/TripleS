#pragma once

#include "Actor.h"

#include "TcpAct.h"
#include "TcpListenSocket.h"
#include "TcpSocket.h"
#include "FowardDeclaration.h"


namespace TripleS 
{
    class Acceptor : public Actor DEBUG_PARENTS(Acceptor)
    {
    public:
        Acceptor(TcpListenSocket& tcp_listen_socket, Proactor& proactor);
        ~Acceptor();

    public:
        void ProcEvent(Act* act, DWORD bytes_transferred);
        void ProcError(Act* act, DWORD error);

        void Register(TcpSocket& acceptsocket);

    public:
        TcpListenSocket& m_tcp_listen_socket;
    };
}