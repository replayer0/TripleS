#include "stdafx.h"

#ifdef TRIPLE_S_DEBUG_MODE
#include "vld.h"
#endif // TRIPLE_S_DEBUG_MODE

#include "TcpService.h"
#include "TcpSocket.h"

//test option
#define num_socket 10

int _tmain(int argc, _TCHAR* argv[])
{
    //define desc
    TripleS::service_desc desc;

    //create
    TripleS::TcpService server(desc);
    Sleep(2000);

    //create socket
    TripleS::TcpSocket tcpsocket(server);
    Sleep(2000);

    //run
    server.Start();

    //regist
    //for (int i = 0; i < num_socket; ++i)
    {
        //server.RegistSocket(&tcpsocket);
    }

    Sleep(2000);
	return 0;
}

