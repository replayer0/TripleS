#pragma once

#include "WinSock.h"

namespace TripleS 
{
    class Actor;

    class Act : public OVERLAPPED
    {
    public:
        Act()
        {
            hEvent = NULL;
            Internal = 0;
            InternalHigh = 0;
            Offset = 0;
            OffsetHigh = 0;

            //Actor_ = NULL;
        };
        virtual ~Act(){};

        virtual void Complete(DWORD bytes_transferred) = 0;
        virtual void Error(DWORD error) = 0;
        int io_type; // todo - connect functor

    protected:
        std::shared_ptr<Actor> m_actor;
    };
};
