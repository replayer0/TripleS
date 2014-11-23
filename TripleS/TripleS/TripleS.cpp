#include "stdafx.h"

#ifdef TRIPLE_S_DEBUG_MODE
#include "vld.h"
#endif // TRIPLE_S_DEBUG_MODE

#include "TcpService.h"
#include "TcpSocket.h"

//test option
#define num_socket 10

//test functor
<<<<<<< HEAD
// class testFunctor : public TripleS::TcpService::TcpFunctor
// {
//     int distanceche(){};
//     virtual void method( TripleS::PacketPtr& params )
//     {
//         ;
//     }
// };

// void test2( TripleS::PacketPtr& params )
// {}
=======
class testFunctor : public TripleS::TcpService::TcpFunctor
{
public:
    testFunctor()
    {
        InitializeCriticalSection(&m_cs);
    }
    ~testFunctor()
    {
        DeleteCriticalSection(&m_cs);
    }

    virtual void method(TripleS::PacketPtr& params)
    {
        _IncCount();
    }

private:
    UInt32 m_count{ 0 };
    CRITICAL_SECTION m_cs;
    void _IncCount()
    {
        EnterCriticalSection(&m_cs);
        m_count++;
        LeaveCriticalSection(&m_cs);
    };
};

void testFunction( TripleS::PacketPtr& params )
{}
>>>>>>> origin/master

int _tmain(int argc, _TCHAR* argv[])
{
    //define desc
    TripleS::service_desc desc;

    //create
    TripleS::TcpService server(desc);
<<<<<<< HEAD
//    server.RegistFunctor(1, new testFunctor);
 //   server.RegistFunction(2, test2);
=======
    server.RegistFunctor(1, new testFunctor);
    server.RegistFunction(2, testFunction);
>>>>>>> origin/master
    Sleep(2000);

    //create socket
    std::shared_ptr<TripleS::TcpSocket> tcp_socket[num_socket];
    for (int i = 0; i < num_socket; ++i)
    {
        tcp_socket[i] = std::shared_ptr<TripleS::TcpSocket>(new TripleS::TcpSocket(server));
    }
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

