#include "stdafx.h"

#ifdef TRIPLE_S_DEBUG_MODE
#include "vld.h"
#endif // TRIPLE_S_DEBUG_MODE

#include "TcpService.h"
#include "TcpSocket.h"

#include "TcpConnectSocket.h"
//test option
#define num_socket 10

//test functor
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

TripleS::TcpService* g_tcp_service;
BOOL CtrlHandler(DWORD ctrl_type)
{
    switch (ctrl_type)
    {
    case CTRL_C_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
    default:
        if (g_tcp_service != NULL)
        {
            delete[] g_tcp_service;
            g_tcp_service = NULL;
        }
        return FALSE;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    TripleS::TcpConnectSocket so;
    so.Connect();

    //define desc
    TripleS::service_desc desc;

    //create
    TripleS::TcpService* server = new TripleS::TcpService(desc);
    g_tcp_service = server;
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
    Sleep(2000);

    //regist functor
    server->RegistFunctor(1, new testFunctor);
    server->RegistFunction(2, testFunction);

    //run
    server->Start();

    //while (true)
    {
    }

    if (server != NULL)
    {
        delete[] server;
        server = NULL;
    }

	return 0;
}

