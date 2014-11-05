#pragma once

#include "WinSock.h"
#include <memory>

namespace TripleS 
{
    class WSA
    {
    public:
        WSA()
        {
            WSADATA	wsaData;
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
            {
                //
            }
        }

        virtual ~WSA()
        {
            WSACleanup();
        }
    };
};

static TripleS::WSA WSA_GLOBAL;