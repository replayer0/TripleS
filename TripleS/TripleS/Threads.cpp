#include "stdafx.h"

#include "Threads.h"
using namespace TripleS;

TripleS::Threads::Threads(unsigned int max_thread)
    : m_worker_threads(max_thread, nullptr)
{
}

TripleS::Threads::~Threads()
{
    _Release();
}

const bool Threads::UnRegist(const THREAD_KEY key)
{
    if (m_worker_threads.erase(key) == false)
    {
        return false;
    }

    return true;
}

const bool Threads::IsRegist(const THREAD_KEY key)
{
    return m_worker_threads.exist(key);
}

const void Threads::Join()
{
    m_worker_threads.method
        (
        [](THREAD_KEY key, THREAD_PTR thr_ptr)
    {
        auto thread_ptr = thr_ptr.get();
        if (thread_ptr != NULL && thread_ptr->joinable())
        {
            thread_ptr->join();
        };
    }
    );
}

const void Threads::_Release()
{
    std::vector<THREAD_KEY> temp_vec;
    m_worker_threads.method
        (
        [&temp_vec](THREAD_KEY key, THREAD_PTR thr_ptr)
    {
        temp_vec.push_back(key);
    }
    );

    for (auto cur_iter = temp_vec.begin(); cur_iter != temp_vec.end();
        ++cur_iter)
    {
        UnRegist(*cur_iter);
    }

    Join();
}
