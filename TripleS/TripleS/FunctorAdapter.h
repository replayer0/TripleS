#pragma once
/*******************************************************************************
**  Name : FunctorAdapter
**  Auth : 임상수
**  Date : 2014-08-28
**  Desc : Functor를 관리
********************************************************************************
**  Todo : 하나의 FunctorAdapter에서 같은 종류의 parameter만 처리가 가능하다.
**         이 부분을 bind로 해결가능할까? 다양한 종류의 parameter를 가지는
**         functor의 저장이 가능한가? 가능하다해도 bind의 속도가 빠를까?
********************************************************************************
**  Date:    Author:    Description:
**  -------- ---------- --------------------------------------------------------
**  임상수   2014-08-28 파일 생성
**  임상수   2014-09-01 shared_ptr을 사용하도록 변경
**  임상수   2014-09-11 BaseFunctor를 상속받아 중첩 어댑터가 가능하도록 변경
**  임상수   2014-09-15 11자 작업 삭제 및 템플릿 가변인자로 구조변경
**  임상수   2014-09-15 in/output 클래스 삭제, ConcurrencyFunctorAdapter 추가
**  임상수   2014-09-15 cuncerrency 관련 파일 분리
*******************************************************************************/

#include <map>
#include <functional>
#include "tbb/tbb.h"

namespace TripleS { 
    namespace util {
        template<typename...arg_tns>
        class BaseFunctor
        {
        public:
            virtual ~BaseFunctor(){};
            virtual void method(arg_tns...params) = 0;
        };

        // todo...
        template<typename func_tn, typename...arg_tns>
        class FunctionFunctor : public BaseFunctor<arg_tns...>
        {
        public:
            FunctionFunctor(func_tn p_func)
            {
                m_p_func = p_func;
            }

            virtual void method(arg_tns...params)
            {
                m_p_func(params...);
            }
        private:
            typedef void (*func_tn)(arg_tns...);
            func_tn m_p_func;
        };

        template<typename key_tn = int, typename...arg_tns>
        class BaseAdapter
        {
        public:
            virtual ~BaseAdapter(){};
            virtual bool Regist(const key_tn key, BaseFunctor<arg_tns...>* base_functor) = 0;
            virtual bool Execute(const key_tn key_value, arg_tns...params) = 0;
            virtual BaseFunctor<arg_tns...>* GetFunctor(const key_tn key_value) const = 0;
        };

        template<typename key_tn = int, typename...arg_tns>
        class FunctorAdapter : public BaseAdapter<key_tn, arg_tns...>
        {
        public:
            FunctorAdapter(){};
            virtual ~FunctorAdapter()
            {
                m_container.clear();
            };

            bool Regist(const key_tn key, BaseFunctor<arg_tns...>* base_functor)
            {
                if (base_functor == NULL)
                {
                    return false;
                }

                return m_container.insert(std::make_pair(key, FUNCTOR_PTR(base_functor))).second;
            }

            bool Execute(const key_tn key_value, arg_tns...params)
            {
                auto iter = m_container.find(key_value);
                if (iter != m_container.end())
                {
                    if (iter->second != NULL)
                    {
                        (iter->second)->method(params...);
                    }
                    return true;
                }
                return false;
            }

            BaseFunctor<arg_tns...>* GetFunctor(const key_tn key_value) const
            {
                auto iter = m_container.find(key_value);
                if (iter != m_container.end())
                {
                    return (iter->second).get();
                }
                return NULL;
            }

        private:
            typedef std::shared_ptr<BaseFunctor<arg_tns...>>    FUNCTOR_PTR;
            std::map<key_tn, FUNCTOR_PTR> m_container;
        };

        //Example Using Adapter to Functor
        template<typename key_tn = int, typename...arg_tns>
        class FunctorAdaptFunctor 
            : public BaseFunctor<arg_tns...>, 
              public FunctorAdapter<key_tn, arg_tns...>
        {
            virtual key_tn GetKey() = 0;

            virtual void method(arg_tns...params)
            {
                Execute(GetKey(), params...);
            }
        };
    }
}