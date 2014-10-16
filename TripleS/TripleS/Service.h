#pragma once
#ifndef _TRIPLE_S_SERVICE_H
#define _TRIPLE_S_SERVICE_H
/*******************************************************************************
**  Name :
**  Auth : 임상수
**  Date : 2014-09-17
**  Desc :
********************************************************************************
**  Todo :
********************************************************************************
**  Date:    Author:    Description:
**  -------- ---------- --------------------------------------------------------
**  임상수   2014-09-17 파일 생성
*******************************************************************************/

#include "WinSock.h"
#include <memory>

namespace TripleS {
    namespace iocp {
        class Service
        {
        public:
            Service()
            {
                WSADATA	wsaData;
                if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
                {
                    //
                }
            }

            virtual ~Service()
            {
                WSACleanup();
            }
        };
    };
};

#endif // _TRIPLE_S_SERVICE_H