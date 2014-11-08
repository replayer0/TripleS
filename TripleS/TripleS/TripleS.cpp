#include "stdafx.h"

#ifdef TRIPLE_S_DEBUG_MODE
#include "vld.h"
#endif // TRIPLE_S_DEBUG_MODE

#include "TcpService.h"
#include "TcpSocket.h"

//test option
#define num_socket 10

//test functor
class testFunctor : public TripleS::TcpService::TcpFunctor
{
    int distanceche(){};
    virtual void method( TripleS::PacketPtr& params )
    {
        ;
    }
};

void test2( TripleS::PacketPtr& params )
{}

int _tmain(int argc, _TCHAR* argv[])
{
    //define desc
    TripleS::service_desc desc;

    //create
    TripleS::TcpService server(desc);
    server.RegistFunctor(1, new testFunctor);
    server.RegistFunction(2, test2);
    Sleep(2000);

    //create socket
    std::shared_ptr<TripleS::TcpSocket> tcp_socket[num_socket];
    for (int i = 0; i < num_socket; ++i)
    {
        tcp_socket[i] = std::shared_ptr<TripleS::TcpSocket>(new TripleS::TcpSocket(server));
    }

    TripleS::TcpSocket tcpsocket(server);
    Sleep(2000);

    //run
    server.Start();

    //regist
    for (int i = 0; i < num_socket; ++i)
    {
        tcp_socket[i]->RegistAccept();
    }

    Sleep(2000);
	return 0;
}

