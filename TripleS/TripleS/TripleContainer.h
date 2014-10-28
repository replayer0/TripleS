#pragma once

/*******************************************************************************
**  Name : TripleFastContainer, TripleSlowContainer
**  Auth : �ӻ��
**  Date : 2014-08-28
**  Desc : ��Ƽ ������� �����̳�
********************************************************************************
**  Todo : queue, vector..
********************************************************************************
** Test - Debug mode, data 1���� insert, ���� ������
** TripleF - 47 ms
** STL map - ms
** TripleS - 7500 ms, ������ �� 10���̻� �ҿ�
** Test - Release mode, data 100���� ������ ����, ���� ������
** TripleFast - 250
** STL map - 350
** TripleSlow - 600
** ������ ���۽� Stl�� TripleF ���� �� ���� ������ TripleS�� ������ ��������� ������
** but TripleSlow�� ������ �ӵ��� �������������� ������ ����, ���� ����ȭ�� ���� ���󰡳�?
** Test - Release mode, data 10���� ������ ����, 4�� ������, lock
** STL map - 140 (������ 1,2,3,4�� ���� ���� ����)
** TripleFast - 140
** �ӵ� ���̰� ���µ� �׳� lock�ɰ� ����ϳ�? ������
// ������ 1,2�� ���̳�
** tbb c hashmap�� ���� ����� ����ϴ� ������ 1�� 1200 2�� 800 �� ���Դ�
** stl map - 1250, 950, 950, 1200
** TripleFast - 1�� 1280, 2�� 880, 3�� 1000, 4��, 1210
** TripleSlow - 1�� 1530, 2�� 1030, 3�� 900, 4��, 1050
** ���� ���� ���̰� ���� ���� �ھ 2���� ���� �̷� ������ �Ͼ�����ϴ�.
** 4�� �̻��� ���� �ھ�� �׽�Ʈ�� �ʿ��ϴ�!
** ������ ������ TripleFast�� 2���� �����忡�� stl map���� �����ٴ� �Ͱ�
** TripleSlow�� �������� �׸� ������ �ʴٴ� ���̴�!
** �� �� ������ ���۰� ���� �ڷᱸ���� ���� �Ǵ� �������� lock�� ��쵵 ��������!
** ovelapped�� new�ϴ� ������ �ſ� �����Ƿ� ���� �ڵ忡�� Overlapped�� ���� ���� �Ҵ� �ϵ��� ����
** �������� 10���� ���⼭�� 100������ �����͸� �����Ѵ�!!
** stl map - 1100, 870, 830, 830
** TripleFast - 1�� 1200, 2�� 770, 3�� 850, 4��, 980
** TripleSlow - 1�� 1500, 2�� 1000, 3�� 780, 4��, 800~1200
********************************************************************************
**  Date:    Author:    Description:
**  -------- ---------- --------------------------------------------------------
**  �ӻ��   2014-08-28 ���� ����
**  �ӻ��   2014-09-01 Slow �����̳� �߰�
*******************************************************************************/

#include "tbb/tbb.h"
namespace TripleS 
{
    template<typename key_tn, typename value_tn>
    class TripleFastContainer // ���ͷ����� ���Ұ� ���� ���� �˻��� ����
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
    class TripleSlowContainer // ����, ����, �˻�, ��ȸ ��� ���� �ϳ� �ִ� ũ��� null_value�� �����ؾ���
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