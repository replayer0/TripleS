#pragma once
#ifndef _TRIPLE_S_UTIL_MACRO_H_
#define _TRIPLE_S_UTIL_MACRO_H_

////////////////////////////////////////////////////////////////////////////////
/* ¡Ú */ #define TRIPLE_S_DEBUG_MODE /* ¡Ú */
#ifndef TRIPLE_DEBUG_MODE
/* ¡Ú */ #define TRIPLE_S_RELEASE_MODE /* ¡Ú */
#endif // n TRIPLE_S_DEBUG_MODE
////////////////////////////////////////////////////////////////////////////////


#include <string>
#include <iostream>
#include <stdarg.h>

namespace TripleS 
{
    namespace util
    {
        enum eDEBUG_INFO_LEVEL
        {
            eDEBUG_ALL = 0,
            eDEBUG_LOW = 1,
            eDEBUG_MIDLLE = 2,
            eDEBUG_HIGH = 3,
        };

        //void _DEBUG_INFO(const TCHAR* format, ...);
        void _DEBUG_INFO(
            eDEBUG_INFO_LEVEL level,
            std::string date,
            std::string file,
            std::string function,
            std::string line,
            const TCHAR* format, ...);

        template<typename T>
        class _DEBUG_PARENT
        {
        public:
            _DEBUG_PARENT();
            virtual ~_DEBUG_PARENT();

        private:
            void construct();
            void destruct();
            std::string m_child_name;
        };


        template<typename T>
        TripleS::util::_DEBUG_PARENT<T>::_DEBUG_PARENT()
        {
            m_child_name = std::string(typeid(T).name());
            construct();
        }

        template<typename T>
        TripleS::util::_DEBUG_PARENT<T>::~_DEBUG_PARENT()
        {
            destruct();
        }

    };
};

////////////////////////////////////////////////////////////////////////////////
// Global Define
#define eDEBUG_ALL TripleS::util::eDEBUG_INFO_LEVEL::eDEBUG_ALL
#define eDEBUG_LOW TripleS::util::eDEBUG_INFO_LEVEL::eDEBUG_LOW
#define eDEBUG_MIDLLE TripleS::util::eDEBUG_INFO_LEVEL::eDEBUG_MIDLLE
#define eDEBUG_HIGH TripleS::util::eDEBUG_INFO_LEVEL::eDEBUG_HIGH


////////////////////////////////////////////////////////////////////////////////
#ifdef TRIPLE_S_DEBUG_MODE

#define DEBUG_INFO(level, str, ...) \
 TripleS::util::_DEBUG_INFO(\
 level,\
 std::string(__TIMESTAMP__),\
 std::string(__FILE__),\
 std::string(__FUNCTION__),\
 std::to_string(__LINE__),\
 str, __VA_ARGS__);

#define DEBUG_PARENT(T) : public TripleS::util::_DEBUG_PARENT<T>
#define DEBUG_PARENTS(T) ,public TripleS::util::_DEBUG_PARENT<T>

#else  // TRIPLE_S_DEBUG_MODE
#define DEBUG_INFO(level, str, ...) ;
#define DEBUG_PARENT(T) 
#define DEBUG_PARENTS(T) 
#endif // TRIPLE_S_DEBUG_MODE

////////////////////////////////////////////////////////////////////////////////
namespace TripleS
{
    namespace util
    {
        template<typename T>
        void TripleS::util::_DEBUG_PARENT<T>::construct()
        {
            DEBUG_INFO(eDEBUG_LOW, "")//, (m_child_name + "called").c_str());
        }

        template<typename T>
        void TripleS::util::_DEBUG_PARENT<T>::destruct()
        {
            DEBUG_INFO(eDEBUG_LOW, "")//, (m_child_name + "called").c_str());
        }
    };
};

#endif // _TRIPLE_S_UTIL_MACRO_H_