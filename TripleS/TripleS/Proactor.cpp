#include "stdafx.h"

#include <iostream>

#include "Proactor.h"
#include "Threads.h"

using namespace TripleS;

Proactor::Proactor(thread_desc desc)
{
    _Init(desc);
}

Proactor::~Proactor()
{
    _Release();
}

void Proactor::_Init(thread_desc desc)
{
    m_handle_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
    if (m_handle_iocp == INVALID_HANDLE_VALUE)
    {
        return;
    }

    if (!(m_threads = new TripleS::Threads(desc.m_max_thread_count)))
    {
        return;
    }

    for (unsigned int thread_idx = 0; thread_idx < desc.m_begin_thread_count; ++thread_idx)
    {
        ThreadParameter* input_param = new ThreadParameter(this);
        input_param->SetThreadIndex(thread_idx);

        m_threads->Regist(thread_idx, Proactor::ThreadProc, input_param);
        Sleep(200);
    }
}

void Proactor::_Release()
{
    if (m_handle_iocp != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_handle_iocp);
        m_handle_iocp = NULL;
    }

    if (m_threads != NULL)
    {
        delete[] m_threads;
    }
}

UINT WINAPI Proactor::ThreadProc(ThreadParameter* input_param)
{
    DEBUG_INFO(eDEBUG_LOW, "run thread (%d)", input_param->GetThreadIndex());
    input_param->GetBaseIocp()->ProcEvents(input_param);
    DEBUG_INFO(eDEBUG_LOW, "end thread (%d)", input_param->GetThreadIndex());
    delete[] input_param;
    return 1;
}

const void Proactor::ProcEvents(ThreadParameter* input_param)
{
    int thread_index = input_param->GetThreadIndex();

    __try // two-phase termination pattern
    {
        __try
        {
            while (m_threads->IsRegist(thread_index) == true)
            {
                DWORD io_size = 0;
                ULONG completion_key = 0;
                OVERLAPPED* overlapped = NULL;

                BOOL return_value = GetQueuedCompletionStatus(m_handle_iocp,
                    &io_size,
                    static_cast<PULONG_PTR>(&completion_key),
                    &overlapped,
                    INFINITE);

                if (return_value == false && overlapped == NULL
                    && ERROR_IO_PENDING != WSAGetLastError())
                {
                    //disconnect & delete & destroy
                    if (overlapped != NULL)
                    {
                        Act* Actkn = static_cast<Act*>(overlapped);
                        Actkn->Error(WSAGetLastError());
                    }

                    delete overlapped;
                    continue;
                }


                Act* async_completion_token = static_cast<Act*>(overlapped);
                async_completion_token->Complete(io_size);

                delete overlapped;
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            std::cout << "__except : " << thread_index << std::endl;
        }
    }
    __finally
    {
        // std::cout << "__finally : " << thread_index << std::endl;
    }
    
    return;
}

const BOOL TripleS::Proactor::PostPrivateEvent(const DWORD completion_key, Act* p_act)
{
    return PostQueuedCompletionStatus(m_handle_iocp, 0, completion_key, p_act);
}

const void TripleS::Proactor::Register(const HANDLE handle)
{
    CreateIoCompletionPort(handle, m_handle_iocp, 0, 0);
}