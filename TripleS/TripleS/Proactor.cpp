#include "stdafx.h"

#include <iostream>

#include "Proactor.h"
#include "Threads.h"

using namespace TripleS;

Proactor::Proactor(TripleS::P_THREADS p_threads)
    : m_threads(p_threads)
{
    m_handle_iocp = NULL;
}

Proactor::~Proactor()
{
    _Release();
}

const bool Proactor::Init()
{
    m_handle_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
    if (m_handle_iocp == NULL)
    {
        return false;
    }
    return true;
}

bool Proactor::_Release()
{
    if (m_handle_iocp != NULL)
    {
        CloseHandle(m_handle_iocp);
        m_handle_iocp = NULL;
    }
    return true;
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