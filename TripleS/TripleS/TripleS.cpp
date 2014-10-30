#include "stdafx.h"

#ifdef TRIPLE_S_DEBUG_MODE
#include "vld.h"
#endif // TRIPLE_S_DEBUG_MODE

#include "TcpService.h"

int _tmain(int argc, _TCHAR* argv[])
{
    //create
    TripleS::TcpService server;
    
    //define desc
    TripleS::service_desc desc;
    desc.m_begin_thread_count = 1;
    desc.m_max_thread_count = 8; // std::thread::hardware_concurrency() * 2;
    desc.m_accept_pool_size = 1;
    desc.m_port = 9000;
    
    //run
    server.Start(desc);

    Sleep(2000);
    //wait
    //server.Release();

	return 0;
}

