#pragma once
#ifndef _TRIFLE_S_BASE_IOCP_PARAMETER_H_
#define _TRIFLE_S_BASE_IOCP_PARAMETER_H_

#include "WinSock.h"
#include "Act.h"

namespace TripleS {
    class Proactor;

    class ThreadParameter
    {
    public:
        ThreadParameter(Proactor* base_iocp)
            :m_base_iocp(base_iocp)
        {
            m_thread_idx = -1;
        }
        virtual ~ThreadParameter(){};

        Proactor* const GetBaseIocp() { return m_base_iocp; };
        void SetThreadIndex(int thread_idx) { m_thread_idx = thread_idx; };
        int  GetThreadIndex() { return m_thread_idx; };

    private:
        Proactor* const m_base_iocp{ NULL };
        int m_thread_idx{ -1 };
    };

    // Todo - ....
    struct thread_desc
    {
        unsigned int m_begin_thread_count{ 2 };
        unsigned int m_max_thread_count{ 4 };
    };
    struct listen_desc
    {
        int          m_backlog_size{ 0 };
        WORD         m_port{ 9000 };
    };
    class service_desc
    {
    public:
        thread_desc  m_thread_desc;
        listen_desc  m_listen_desc;
        //unsigned int m_time_out{ 5000 };
    };
};

#endif // _TRIFLE_S_BASE_IOCP_PARAMETER_H_
