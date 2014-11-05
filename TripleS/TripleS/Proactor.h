#pragma once

/*******************************************************************************
**  Name : BaseIOCP
**  Auth : 임상수
**  Date : 2014-08-03
**  Desc : IOCP를 사용하기위한 기본 베이스 클래스
********************************************************************************
**  Todo : 파일 분리, 아래 todo 참고
**         이 클래스의 문제점이 많은것 같다.
**         클래스의 역활을 분명히 하고 클래스를 나누어야 할 것 같다.
********************************************************************************
**  Date:    Author:    Description:
**  -------- ---------- --------------------------------------------------------
**  임상수   2014-08-03 파일 생성
**  임상수   2014-08-28 가상 소멸자 추가
**  임상수   2014-08-28 BaseIocpFuntor 추가
**  임상수   2014-09-01 동적 thread 관리 추가
**  임상수   2014-09-16 Thread 관리부분 분리
**  임상수   2014-09-16 Proactor 패턴으로 리팩토링
**  임상수   2014-09-17 ProcEvents()에 Two-phase termination pattern 적용
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
