#pragma once

#include "WinSock.h"
#include <memory>

namespace TripleS 
{
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