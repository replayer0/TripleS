#include "stdafx.h"

#ifdef TRIPLE_S_DEBUG_MODE
#include "vld.h"
#endif // TRIPLE_S_DEBUG_MODE

#include "TcpService.h"

int _tmain(int argc, _TCHAR* argv[])
{
    //create
    TripleS::iocp::TcpService server;
    
    //define desc
    TripleS::iocp::BaseIocpDesc desc;
    desc.m_begin_thread_count = 4;
    desc.m_maximun_thread_count = 4;// std::thread::hardware_concurrency() * 2;
    
    //run
    server.Start(desc);

    //wait
    //server.Join();

	return 0;
}

