#pragma once
#ifndef _TRIPLE_S_SERVICE_H
#define _TRIPLE_S_SERVICE_H
/*******************************************************************************
**  Name :
**  Auth : �ӻ��
**  Date : 2014-09-17
**  Desc :
********************************************************************************
**  Todo :
********************************************************************************
**  Date:    Author:    Description:
**  -------- ---------- --------------------------------------------------------
**  �ӻ��   2014-09-17 ���� ����
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