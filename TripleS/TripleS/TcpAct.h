#pragma once

#include "Act.h"
#include "Actor.h"

//--------------------------------------------------------
// 이름 :	TcpAct
//
// 역할 :	1)	OVERLAPPED 확장
//			2)	구체클래스.
//			3)	Proactor의 ProcEvents에서 I/O 완료시 
//				Complete() 와 Error() 콜
//
// 기타	:	Actor 의 SubClass
//--------------------------------------------------------

namespace TripleS {
    namespace iocp {
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
}
