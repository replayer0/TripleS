#pragma once

#include "WinSock.h"

#include <thread>
#include <memory>

#include "BaseIocp_parameter.h"
#include "Act.h"
#include "FowardDeclaration.h"

namespace TripleS 
{
    class Proactor;

    class Iocp DEBUG_PARENT(Iocp)
    {
    public:
        Iocp();// todo : temp Initializer, do erase

        Iocp(TripleS::P_PROACTOR p_proactor
            , TripleS::P_THREADS p_threads);
        ~Iocp();

        void Start(service_desc desc);
        void Join();

    private:
        Iocp(Iocp const& object);
        Iocp& operator=(Iocp const& object);

        TripleS::P_PROACTOR m_proactor;
        TripleS::P_THREADS  m_threads;
    };
};
