#pragma once

#include "WinSock.h"
#include "BaseIocp_parameter.h"
#include "Act.h"

namespace TripleS 
{
	class TcpSocket;
    class Threads;

    class Proactor : private Uncopyable DEBUG_PARENTS(Proactor)
    {
    public:
        Proactor(thread_desc desc);
        ~Proactor();

        const void Register(const HANDLE handle);
        const BOOL PostPrivateEvent(const DWORD completion_key, Act* p_act);
        const void ProcEvents(ThreadParameter* input_parma);
        const void RunThread();

        static UINT WINAPI ThreadProc(ThreadParameter* input_param);
		Bool ProcessPacket( TcpSocket* sock, void* data, Int32 size );
    private:
        void _Init(thread_desc desc);
        void _Release();

        HANDLE m_handle_iocp { INVALID_HANDLE_VALUE };
        HANDLE m_handle_sleep{ INVALID_HANDLE_VALUE };
        Threads* m_threads{ NULL };
    };
};
