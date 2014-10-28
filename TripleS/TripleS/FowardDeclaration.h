#pragma once

#include <memory>

namespace TripleS
{
    /************************************************************************/
    /* Service                                                              */
    /************************************************************************/
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

    /************************************************************************/
    /* Util                                                                 */
    /************************************************************************/
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

    /************************************************************************/
    /* Type                                                                 */
    /************************************************************************/
    typedef std::shared_ptr<TripleS::Iocp> P_IOCP;
    typedef std::shared_ptr<TripleS::Proactor> P_PROACTOR;
    typedef std::shared_ptr<TripleS::Threads> P_THREADS;
    typedef std::shared_ptr<TripleS::TcpListenSocket> P_TCPLISTENSOCKET;
    typedef std::shared_ptr<TripleS::TcpSocket> P_TCPSOCKET;
    typedef std::shared_ptr<TripleS::Acceptor> P_ACCEPTOR;
    typedef std::shared_ptr<TripleS::Disconnector> P_DISCONNECTOR;
    typedef std::shared_ptr<TripleS::Receiver> P_RECEIVER;
    typedef std::shared_ptr<TripleS::Sender> P_SENDER;
};