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
    
    //run
    server.Start(desc);

    Sleep(2000);
    //wait
    //server.Release();

	return 0;
}

