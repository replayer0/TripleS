#pragma once

#include "Act.h"
#include "Proactor.h"

namespace TripleS 
{
    class Actor
    {
    public:
        Actor(Proactor& proactor)
            : m_proactor(proactor)
        {
        }

        virtual void ProcEvent(Act* act, DWORD bytes_transferred) = 0;
        virtual void ProcError(Act* act, DWORD error) = 0;

    protected:
        Proactor& m_proactor;
    };
};