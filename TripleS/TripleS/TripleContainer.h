#pragma once

/*******************************************************************************
**  Name : TripleFastContainer, TripleSlowContainer
**  Auth : 임상수
**  Date : 2014-08-28
**  Desc : 멀티 스레드용 컨테이너
********************************************************************************
**  Todo : queue, vector..
********************************************************************************
** Test - Debug mode, data 1만개 insert, 단일 스레드
** TripleF - 47 ms
** STL map - ms
** TripleS - 7500 ms, 생성자 약 10초이상 소요
** Test - Release mode, data 100만개 데이터 삽입, 단일 스레드
** TripleFast - 250
** STL map - 350
** TripleSlow - 600
** 릴리즈 동작시 Stl이 TripleF 보다 더 빨라 졌으며 TripleS의 동작이 비약적으로 빨라짐
** but TripleSlow는 생성자 속도가 빨라지긴했으나 아직도 느림, 왠지 최적화로 값이 날라가나?
** Test - Release mode, data 10만개 데이터 삽입, 4개 스레드, lock
** STL map - 140 (스레드 1,2,3,4에 따른 차이 없음)
** TripleFast - 140
** 속도 차이가 없는데 그냥 lock걸고 써야하나? ㅎㄷㄷ
// 스레드 1,2개 차이남
** tbb c hashmap을 직접 만들어 사용하니 스레드 1개 1200 2개 800 이 나왔다
** stl map - 1250, 950, 950, 1200
** TripleFast - 1개 1280, 2개 880, 3개 1000, 4개, 1210
** TripleSlow - 1개 1530, 2개 1030, 3개 900, 4개, 1050
** 오오 드디어 차이가 난다 물리 코어가 2개다 보니 이런 현상이 일어나느듯하다.
** 4개 이상의 물리 코어에서 테스트가 필요하다!
** 고무적인 내용은 TripleFast가 2개의 스레드에서 stl map보다 빠르다는 것과
** TripleSlow가 생각보다 그리 느리지 않다는 것이다!
** 좀 더 복잡한 동작과 잦은 자료구조의 접근 또는 광범위한 lock의 경우도 따져보자!
** ovelapped를 new하는 동작이 매우 느리므로 위의 코드에서 Overlapped를 먼저 동적 할당 하도록 변경
** 위에서는 10만개 여기서는 100만개의 데이터를 삽입한다!!
** stl map - 1100, 870, 830, 830
** TripleFast - 1개 1200, 2개 770, 3개 850, 4개, 980
** TripleSlow - 1개 1500, 2개 1000, 3개 780, 4개, 800~1200
********************************************************************************
**  Date:    Author:    Description:
**  -------- ---------- --------------------------------------------------------
**  임상수   2014-08-28 파일 생성
**  임상수   2014-09-01 Slow 컨테이너 추가
*******************************************************************************/

#include "tbb/tbb.h"
namespace TripleS 
{
    template<typename key_tn, typename value_tn>
    class TripleFastContainer // 이터레이터 사용불가 삽입 삭제 검색만 가능
    {
    public:
        TripleFastContainer()
        {
            m_container.clear();
        };
        ~TripleFastContainer()
        {
            // m_container.clear();
        };

        typedef key_tn KEY_TYPE;
        typedef value_tn VALUE_TYPE;

        virtual bool insert(KEY_TYPE key, VALUE_TYPE val)
        {
            CONTAINER_TYPE::accessor acc;
            bool ret_val = m_container.insert(acc, key);
            acc->second = val;
            acc.release();
            return ret_val;
        }

        virtual bool find(KEY_TYPE key, VALUE_TYPE& val) const
        {
            CONTAINER_TYPE::const_accessor acc;
            bool ret_val = m_container.find(acc, key);
            if (ret_val == true)
            {
                val = (acc->second);
            }
            acc.release();
            return ret_val;
        }

        virtual bool erase(KEY_TYPE key)
        {
            bool ret_val = m_container.erase(key);
            return ret_val;
        }
    private:
        typedef tbb::concurrent_hash_map<KEY_TYPE, VALUE_TYPE> CONTAINER_TYPE;
        CONTAINER_TYPE m_container;
    };
};

namespace TripleS 
{
    template<typename key_tn, typename value_tn>
    class TripleSlowContainer // 삽입, 삭제, 검색, 순회 모두 가능 하나 최대 크기와 null_value를 지정해야함
    {
    public:
        typedef key_tn KEY_TYPE;
        typedef value_tn VALUE_TYPE;

        TripleSlowContainer(int max_size, VALUE_TYPE null_value)
        {
            m_cur_size = 0;
            m_max_size = max_size;
            m_null_value = null_value;
            for (int i = 0; i < m_max_size; ++i)
            {
                m_inner_keys.push(i);
                m_values.insert(std::make_pair(i, null_value));
            }
        };
        ~TripleSlowContainer()
        {
            _Release();
        };

        virtual bool insert(KEY_TYPE key, VALUE_TYPE val)
        {
            INNER_KEY inner_key = -1;
            if (m_inner_keys.try_pop(inner_key) == false)
            {
                return false;
            }

            if (m_keys.insert(key, inner_key) == false)
            {
                m_inner_keys.push(inner_key);
                return false;
            }

            if (m_values.insert(std::make_pair(inner_key, val)).second == false)
            {
                m_values.find(inner_key)->second = val;
            }

            InterlockedIncrement((LONG*)&m_cur_size);
            return true;
        }

        virtual bool find(KEY_TYPE key, VALUE_TYPE& val) const
        {
            INNER_KEY inner_key = -1;
            m_keys.find(key, inner_key);
            if (inner_key != -1)
            {
                val = m_values.find(inner_key)->second;
            }
            return true;
        }

        virtual bool exist(KEY_TYPE key) const
        {
            INNER_KEY inner_key = -1;
            m_keys.find(key, inner_key);
            if (inner_key != -1)
            {
                if (m_values.find(inner_key)->second == m_null_value)
                {
                    return false;
                }
                return true;
            }
            return false;
        }

        virtual bool erase(KEY_TYPE key)
        {
            INNER_KEY inner_key = -1;
            if (m_keys.find(key, inner_key) == false)
            {
                return false;
            }
            m_keys.erase(key);

            m_values.insert(std::make_pair(inner_key, m_null_value));
            if (inner_key != -1)
            {
                m_inner_keys.push(inner_key);
            }
            InterlockedDecrement((LONG*)&m_cur_size);
            return true;
        }

        template<typename functor_tn>
        void method(functor_tn functor)
        {
            auto cur_iter = m_values.begin();
            auto end_iter = m_values.end();
            for (; cur_iter != end_iter; ++cur_iter)
            {
                if (cur_iter->second == m_null_value)
                {
                    continue;
                }

                functor(cur_iter->first, cur_iter->second);
            }
        }

        volatile int GetCurSize()
        {
            return m_cur_size;
        }

        int GetMaxSize()
        {
            return m_max_size;
        }

    private:
        void _Release()
        {
            //m_inner_keys.clear();
            //m_values.clear(); //leak
        }

        typedef int INNER_KEY;

        typedef TripleFastContainer<KEY_TYPE, INNER_KEY> KEY_CONTAINER;
        typedef tbb::concurrent_queue<INNER_KEY> INNER_KEY_CONTAINER;
        typedef tbb::concurrent_unordered_map<INNER_KEY, VALUE_TYPE> VALUE_CONTAINER;

        KEY_CONTAINER m_keys;
        INNER_KEY_CONTAINER m_inner_keys;
        VALUE_CONTAINER m_values;

        int m_max_size;
        volatile int m_cur_size;
        VALUE_TYPE m_null_value;
    };
};