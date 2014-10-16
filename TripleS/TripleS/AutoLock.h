#pragma once
#ifndef _TRIPLE_S_UTIL_AUTOLOCK_H_
#define _TRIPLE_S_UTIL_AUTOLOCK_H_

#include "WinSock.h"

namespace TripleS
{
    namespace util
    {
        class Lock
        {
        public:
            Lock()
            {
                InitializeCriticalSection(&m_cs);
            }

            ~Lock()
            {
                DeleteCriticalSection(&m_cs);
            }

            void Enter()
            {
                EnterCriticalSection(&m_cs);
            }

            void Leave()
            {
                LeaveCriticalSection(&m_cs);
            }

        private:
            CRITICAL_SECTION m_cs;
        };

        class AutoLock
        {
        public:
            AutoLock(Lock* lock)
            {
                m_p_lock = lock;
                m_p_lock->Enter();
            }
            ~AutoLock()
            {
                m_p_lock->Leave();
            }

        private:
            Lock* m_p_lock;
        };
    };
};

#endif // _TRIPLE_S_UTIL_AUTOLOCK_H_