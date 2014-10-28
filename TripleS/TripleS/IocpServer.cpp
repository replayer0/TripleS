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
    
    // todo:: �Ʒ��κ��� ��� �E���ΰ�.. �� �ٽ� proactor�� ������.. �ƴϸ� �ֻ��� �������̽����� ����..
    // Ű���� ������ �پ��� ������ �����带 �����Ϸ���..
    //iocpServer�� ���� Threads�� ���??
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
