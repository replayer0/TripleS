#pragma once
/*******************************************************************************
**  Name : FunctorAdapter_concurrency
**  Auth : �ӻ��
**  Date : 2014-09-15
**  Desc : FunctorAdapter�� ��Ƽ ������ ����
********************************************************************************
**  Todo : ConcurrencyFunctorAdapter�� �߰��� ���� Ŭ���� �߰��� ����������.
**         ��ü ��ü�� ����ȭ�� ���������� BaseFunctor���� �����Ǿ���Ѵ�.
********************************************************************************
**  Date:    Author:    Description:
**  -------- ---------- --------------------------------------------------------
**  �ӻ��   2014-09-15 ���� ����
*******************************************************************************/

#include <functional>
#include "tbb/tbb.h"
#include "FunctorAdapter.h"

namespace TripleS {
    namespace util {
        template<typename key_tn = int, typename...arg_tns>
        class LockFunctor : public BaseFunctor < key_tn, arg_tns... >
        {
        public:
            LockFunctor()
            {
                InitializeCriticalSectionAndSpinCount(&m_cs, 200);
            };
            virtual ~LockFunctor()
            {
                DeleteCriticalSection(&m_cs);
            };
            virtual void lock_method(arg_tns...params) = 0;

        private:
            virtual void method(arg_tns...params)
            {
                lock_method(params...);
            }
            CRITICAL_SECTION m_cs;
        };

        template<typename key_tn = int, typename...arg_tns>
        class ConcurrencyFunctorAdapter : public BaseAdapter<key_tn, arg_tns...>
        {
        public:
            ConcurrencyFunctorAdapter(){};
            virtual ~ConcurrencyFunctorAdapter()
            {
                m_container.clear();
            };

            bool Regist(const key_tn key, BaseFunctor<arg_tns...>* base_functor)
            {
                if (base_functor == NULL)
                {
                    return false;
                }

                CONTAINER::accessor acc;
                if (m_container.insert(acc, key))
                {
                    acc->second = FUNCTOR_PTR(base_functor);
                    return true;
                }
                return false;
            }

            bool Execute(const key_tn key_value, arg_tns...params)
            {
                CONTAINER::const_accessor acc;
                if (m_container.find(acc, key_value) == true)
                {
                    if (acc->second != NULL)
                    {
                        (acc->second)->method(params...);
                    }
                    return true;
                }
                return false;
            }

            BaseFunctor<arg_tns...>* GetFunctor(const key_tn key_value) const
            {
                CONTAINER::const_accessor acc;
                if (m_container.find(acc, key_value) == true)
                {
                    return acc->second.get();
                }
                return NULL;
            }

        private:
            typedef std::shared_ptr<BaseFunctor<arg_tns...>>    FUNCTOR_PTR;
            typedef tbb::concurrent_hash_map<key_tn, FUNCTOR_PTR> CONTAINER;
            CONTAINER m_container;
        };
    }
}