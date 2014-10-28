#include "stdafx.h"
#include "IocpServer.h"
#include "Proactor.h"
#include "Threads.h"

TripleS::Iocp::Iocp(TripleS::P_PROACTOR p_proactor
    , TripleS::P_THREADS p_threads)
    : m_proactor(TripleS::P_PROACTOR(p_proactor))
    , m_threads(TripleS::P_THREADS(p_threads))
{
    //
}

TripleS::Iocp::Iocp()
{
    m_threads = TripleS::P_THREADS(new TripleS::Threads(128));
    m_proactor = TripleS::P_PROACTOR(new Proactor(m_threads));
}

TripleS::Iocp::~Iocp()
{
}

void TripleS::Iocp::Start(BaseIocpDesc desc)
{
    m_proactor->Init();
    
    // todo:: 아래부분을 어떻게 뺼것인가.. 걍 다시 proactor에 넣을까.. 아니면 최상위 인터페이스에서 어찌..
    // 키값의 관리와 다양한 종류의 스레드를 생성하려면..
    //iocpServer가 차라리 Threads를 상속??
    for (unsigned int thread_idx = 0; //std::thread::hardware_concurrency();
        thread_idx < desc.m_begin_thread_count; ++thread_idx)
    {
        ThreadParameter* input_param = new ThreadParameter(m_proactor.get());
        input_param->SetThreadIndex(thread_idx);

        m_threads->Regist(thread_idx, Proactor::ThreadProc, input_param);
        Sleep(200);
    }
}

void TripleS::Iocp::Join()
{
    m_threads->Join();
}
