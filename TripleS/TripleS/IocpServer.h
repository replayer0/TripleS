#pragma once
#ifndef _TRIPLE_S_BASE_IOCP_H
#define _TRIPLE_S_BASE_IOCP_H
/*******************************************************************************
**  Name : 
**  Auth : 임상수
**  Date : 2014-08-03
**  Desc :
********************************************************************************
**  Todo : 
********************************************************************************
**  Date:    Author:    Description:
**  -------- ---------- --------------------------------------------------------
**  임상수   2014-09-16 파일 생성
*******************************************************************************/

#include "WinSock.h"

#include <thread>
#include <memory>

#include "BaseIocp_parameter.h"
#include "Act.h"
#include "FowardDeclaration.h"

namespace TripleS {
    namespace iocp {
        class Proactor;

        class Iocp DEBUG_PARENT(Iocp)
        {
        public:
            Iocp();// todo : temp Initializer, do erase

            Iocp(TripleS::type::P_PROACTOR p_proactor
                , TripleS::type::P_THREADS p_threads);
            ~Iocp();

            void Start(BaseIocpDesc desc);
            void Join();

        private:
            Iocp(Iocp const& object);
            Iocp& operator=(Iocp const& object);

            TripleS::type::P_PROACTOR m_proactor;
            TripleS::type::P_THREADS  m_threads;
        };
    };
};

#endif // _TRIPLE_S_BASE_IOCP_H