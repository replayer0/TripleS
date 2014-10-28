#pragma once

/*******************************************************************************
**  Name : BaseIOCP
**  Auth : �ӻ��
**  Date : 2014-08-03
**  Desc : IOCP�� ����ϱ����� �⺻ ���̽� Ŭ����
********************************************************************************
**  Todo : ���� �и�, �Ʒ� todo ����
**         �� Ŭ������ �������� ������ ����.
**         Ŭ������ ��Ȱ�� �и��� �ϰ� Ŭ������ ������� �� �� ����.
********************************************************************************
**  Date:    Author:    Description:
**  -------- ---------- --------------------------------------------------------
**  �ӻ��   2014-08-03 ���� ����
**  �ӻ��   2014-08-28 ���� �Ҹ��� �߰�
**  �ӻ��   2014-08-28 BaseIocpFuntor �߰�
**  �ӻ��   2014-09-01 ���� thread ���� �߰�
**  �ӻ��   2014-09-16 Thread �����κ� �и�
**  �ӻ��   2014-09-16 Proactor �������� �����丵
**  �ӻ��   2014-09-17 ProcEvents()�� Two-phase termination pattern ����
*******************************************************************************/

#include "WinSock.h"

#include "BaseIocp_parameter.h"
#include "Act.h"
#include "FowardDeclaration.h"

namespace TripleS { 
    class Proactor DEBUG_PARENT(Proactor)
    {
    public:
        Proactor(TripleS::P_THREADS p_threads);
        ~Proactor();

        const bool Init();
        const void Register(const HANDLE handle);
        const BOOL PostPrivateEvent(const DWORD completion_key, Act* p_act);
        const void ProcEvents(ThreadParameter* input_parma);

        static UINT WINAPI ThreadProc(ThreadParameter* input_param);

    private:
        Proactor(Proactor const& object);
        Proactor& operator=(Proactor const& object);

        bool _Release();

        HANDLE m_handle_iocp;
        TripleS::P_THREADS m_threads;
    };
};
