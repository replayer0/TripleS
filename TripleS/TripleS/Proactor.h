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
    class Proactor : private Uncopyable DEBUG_PARENTS(Proactor)
    {
    public:
        Proactor(thread_desc desc);
        ~Proactor();

        const void Register(const HANDLE handle);
        const BOOL PostPrivateEvent(const DWORD completion_key, Act* p_act);
        const void ProcEvents(ThreadParameter* input_parma);
        const void RunThread();

        static UINT WINAPI ThreadProc(ThreadParameter* input_param);

    private:
        void _Init(thread_desc desc);
        void _Release();

        HANDLE m_handle_iocp { INVALID_HANDLE_VALUE };
        HANDLE m_handle_sleep{ INVALID_HANDLE_VALUE };
        Threads* m_threads{ NULL };
    };
};
