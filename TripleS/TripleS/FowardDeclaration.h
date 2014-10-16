#pragma once
#ifndef _TRIFLE_S_FORWARD_DECLARATION_H_
#define _TRIFLE_S_FORWARD_DECLARATION_H_
#include <memory>

namespace TripleS
{
    namespace iocp
    {
        // base server class
        class Proactor;
        class Iocp;
        class TcpListenSocket;
        class TcpSocket;
        class Acceptor;
        class Receiver;
        class Sender;
        class Disconnector;

        // data class
        class Act;
        class OverlappedParameter;
        class BaseIocpFunctor;

        // enum // todo
        enum eDEFAULT_FUNCTOR_KEY;
    };

    namespace util
    {
        // functor Adapter
        template<typename ... arg>
        class BaseFunctor;
        template<typename T, typename ... arg>
        class FunctorAdapter;
        template<typename T, typename ... arg>
        class ConcurrencyFunctorAdapter;

        class Threads;

        // macro // debug
        template<typename T>
        class _DEBUG_PARENT;
    };

    namespace type
    {
        typedef std::shared_ptr<TripleS::iocp::Iocp> P_IOCP;
        typedef std::shared_ptr<TripleS::iocp::Proactor> P_PROACTOR;
        typedef std::shared_ptr<TripleS::util::Threads> P_THREADS;
        typedef std::shared_ptr<TripleS::iocp::TcpListenSocket> P_TCPLISTENSOCKET;
        typedef std::shared_ptr<TripleS::iocp::TcpSocket> P_TCPSOCKET;
        typedef std::shared_ptr<TripleS::iocp::Acceptor> P_ACCEPTOR;
        typedef std::shared_ptr<TripleS::iocp::Disconnector> P_DISCONNECTOR;
        typedef std::shared_ptr<TripleS::iocp::Receiver> P_RECEIVER;
        typedef std::shared_ptr<TripleS::iocp::Sender> P_SENDER;
    };
};

#endif // _TRIFLE_S_FORWARD_DECLARATION_H_