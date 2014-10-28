#pragma once

/*******************************************************************************
**  Name : ThreadManager
**  Auth : �ӻ��
**  Date : 2014-09-15
**  Desc : 
********************************************************************************
**  Todo : TripleSlowContainer�� �ٲ���Ѵ�..
********************************************************************************
**  Date:    Author:    Description:
**  -------- ---------- --------------------------------------------------------
**  �ӻ��   2014-09-15 ���� ����
**  �ӻ��   2014-09-16 Using TripleSlowContainer, Support join & release
*******************************************************************************/

#include <memory>
#include <thread>
#include "tbb/tbb.h"
#include "TripleContainer.h"

namespace TripleS 
{
    class Threads DEBUG_PARENT(Threads)
    {
    public:
        Threads(int max_thread);
        ~Threads();

        typedef unsigned int THREAD_KEY;

        template<class _Fn, class... _Args>
        const bool Regist(THREAD_KEY key, _Fn&& _Fx, _Args&&... _Ax);
        const bool IsRegist(const THREAD_KEY key);
        const void Join();

        // do not terminate thread 
        // ���� ������ ���� ��û // ������ ���ο��� �� �Լ��� ���� ó���� �ʼ����̴�.
        const bool UnRegist(const THREAD_KEY key);

    private:
        Threads();
        Threads(Threads const& object);
        Threads& operator=(Threads const& object);

        // call all thread UnRegist()
        const void _Release();

        typedef std::shared_ptr<std::thread>    THREAD_PTR;
        typedef TripleS::TripleSlowContainer<THREAD_KEY, THREAD_PTR> THREAD_LIST;

        THREAD_LIST m_worker_threads;
    };

    template<class _Fn, class... _Args>
    const bool Threads::Regist(THREAD_KEY key, _Fn&& _Fx, _Args&&... _Ax)
    {
        if (IsRegist(key) == true)
        {
            return false;
        }

        THREAD_PTR thread_ptr(new std::thread(_Fx, _Ax...));

        if (m_worker_threads.insert(key, thread_ptr) == false)
        {
            return false;
        }
        return true;
    }
};