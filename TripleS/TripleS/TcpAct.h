#pragma once

#include "Act.h"
#include "Actor.h"

namespace TripleS 
{
    class TcpSocket;
    class TcpAct : public Act
    {
    public:
        TcpAct()
        {
            TcpSocket_ = NULL;
        }

        void Complete(DWORD bytes_transferred)
        {
            m_actor->ProcEvent(this, bytes_transferred);
        }

        void Error(DWORD error)
        {
            m_actor->ProcError(this, error);
        }

        void Init(std::shared_ptr<Actor> actor, TcpSocket* tcpsocket)
        {
            m_actor = actor;
            TcpSocket_ = tcpsocket;
        }

        const TcpSocket* GetTcpSocket()
        {
            return TcpSocket_;
        }

    public:
        TcpSocket* TcpSocket_;
    };
}