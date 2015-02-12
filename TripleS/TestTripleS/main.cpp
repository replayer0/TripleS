#ifdef _DEBUG
    // 
#else
    #define VLD_FORCE_ENABLE
#endif

#include "TcpService.h"
#include "vld.h"
#include "packet.pb.h"
#include "AutoLock.h"
#include "Singleton.h"

//test logger
TripleS::Lock g_log_lock;
void LogCallbackFunction(int log_type, std::string log)
{
    /*switch (log_type)
    {
    case TripleS::eLOG_TYPE_CONSTRUCT_CLASS:
        return;
    }*/

    TripleS::AutoLock auto_lock(&g_log_lock);
    std::cout << "<" << log_type << "> " << log << std::endl;
}

//test option
#define num_socket 50

//test functor
class EchoFunctor : public TripleS::TcpService::TcpFunctor
{
public:
    EchoFunctor(){};
    ~EchoFunctor(){};

    virtual void method(TripleS::FUNCTOR_PARAM params)
    {
        // default process
        InterlockedIncrement(&m_count);
        auto packet_stream = params.first;
        auto socket = params.second;

        // packet convert
        EchoPacket packet;
        if (false == packet.ParseFromCodedStream(packet_stream))
        {
            printf("error convert stream to packet");
        }
        else
        {
            std::wcout << TripleS::PacketToString(packet).c_str() << "count:" << m_count << std::endl;
            std::wcout << packet.name().c_str() << "/" << packet.name().size() << std::endl;
        }

        // process packet
        socket->SendProtobuf(eEchoPacket, packet);
    }

private:
    volatile unsigned int m_count{ 0 };
};

void StringFunction(TripleS::FUNCTOR_PARAM params)
{
    // default process
    auto packet_stream = params.first;
    auto socket = params.second;

    // packet convert
    StringPacket packet;
    if (false == packet.ParseFromCodedStream(packet_stream))
    {
        printf("error convert stream to packet");
    }
    else
    {
        std::wcout << TripleS::PacketToString(packet).c_str() << std::endl;
        std::cout << packet.str().c_str() << "/" << packet.str().size() << std::endl;
        std::wcout << packet.str().c_str() << "/" << packet.str().size() << std::endl;
    }

    // process packet
    socket->SendProtobuf(eStringPacket, packet);
}


void AddFunction(TripleS::FUNCTOR_PARAM params)
{
    // default process
    auto packet_stream = params.first;
    auto socket = params.second;

    // packet convert
    AddPacket packet;
    if (false == packet.ParseFromCodedStream(packet_stream))
    {
        printf("error convert stream to packet");
    }
    else
    {
        std::wcout << TripleS::PacketToString(packet).c_str() << std::endl;
    }

    AddResultPacket result_packet;
    result_packet.set_result(packet.first() + packet.second());

    // process packet
    socket->SendProtobuf(eAddResultpacket, result_packet);
}

void ReqLoginProcess(TripleS::FUNCTOR_PARAM params)
{
    // default process
    auto packet_stream = params.first;
    auto socket = params.second;

    // packet convert
    ReqLoginPacket packet;
    if (false == packet.ParseFromCodedStream(packet_stream))
    {
        printf("error convert stream to packet");
    }
    else
    {
        std::wcout << TripleS::PacketToString(packet).c_str() << std::endl;
    }

    std::wcout << packet.id().c_str() << "/" << packet.id().size() << std::endl;

    AckLoginPacket result_packet;
    result_packet.set_id(packet.id());
    result_packet.set_result(1);

    // process packet
    socket->SendProtobuf(eAckLoginPacket, result_packet);
}
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
            delete g_tcp_service;
            g_tcp_service = NULL;
        }
        return FALSE;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    // set log callback
    LogCallback = LogCallbackFunction;

    // define desc
    TripleS::service_desc desc;
    desc.m_thread_desc.m_begin_thread_count = 1;

    // create
    g_tcp_service = NULL;
    g_tcp_service = new TripleS::TcpService(desc);
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
    Sleep(2000);

    // regist functor
    g_tcp_service->RegistFunctor(eEchoPacket, new EchoFunctor);
    g_tcp_service->RegistFunction(eStringPacket, StringFunction);
    g_tcp_service->RegistFunction(eAddPacket, AddFunction);
    g_tcp_service->RegistFunction(eReqLoginPacket, ReqLoginProcess);

    // run
    g_tcp_service->Start();

    // alloc socket
    std::vector<TripleS::TcpSocket*> vec;
    for (int i = 0; i < num_socket; ++i)
    {
        TripleS::TcpSocket* tcp_socket = new TripleS::TcpSocket(*g_tcp_service);
        g_tcp_service->RegistAccept(*tcp_socket);
        vec.push_back(tcp_socket);
    }

    char command_buf[1024];
    while (true)
    {
        fgets(command_buf, 1024, stdin);
        auto is_command = strncmp(command_buf, "END", 3);
        if (is_command == 0)
        {
            break;
        }
    }

    if (g_tcp_service != NULL)
    {
        delete g_tcp_service;
        g_tcp_service = NULL;
    }

    // dealloc socket
    for (auto cur_iter = vec.begin(); cur_iter != vec.end(); ++cur_iter)
    {
        delete *cur_iter;
    }
    return 0;
}
