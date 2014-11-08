#pragma once

#include "stdafx.h"

namespace TripleS
{
    class Session
    {
    public:
        Session()
        {
            static UInt32 session_idx = 0;
            m_session_idx = session_idx++;
        }

        ~Session()
        {

        }
        UInt32 GetSessionIdx() {return m_session_idx;}

    protected:
        PacketStream    RecvBuf;		// 이게 레알 버퍼.
        UInt32 m_session_idx;
    };
}