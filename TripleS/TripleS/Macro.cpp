#include "stdafx.h"
#include "Macro.h"
#include "WinSock.h"
#include "AutoLock.h"

/* SHOW DEBUG INFO LEVEL*/
#define DEBUG_INFO_LEVEL eDEBUG_ALL

/* SHOW DEBUG INFO OPTION*/
//#define DEBUG_INFO_NAME
//#define DEBUG_INFO_DATE
//#define DEBUG_INFO_DATE_NEW_LINE
//#define DEBUG_INFO_FILE
//#define DEBUG_INFO_FILE_NEW_LINE
#define DEBUG_INFO_FUNCTION
//#define DEBUG_INFO_FUNCTION_NEW_LINE
//#define DEBUG_INFO_LINE
//#define DEBUG_INFO_LINE_NEW_LINE
//#define DEBUG_INFO_NEW_LINE

/* SHOW DEBUG INFO LOCK */
#ifdef TRIPLE_S_DEBUG_MODE
TripleS::Lock g_debug_info_lock;
#endif // TRIPLE_S_DEBUG_MODE

void TripleS::_DEBUG_INFO(
    eDEBUG_INFO_LEVEL level,
    std::string date,
    std::string file,
    std::string function,
    std::string line,
    const TCHAR* format, ...)
{
    if (level < DEBUG_INFO_LEVEL)
    {
        return;
    }

    TripleS::AutoLock autolock(&g_debug_info_lock);

    va_list args;
    va_start(args, format);
    TCHAR buf[1024] = { 0, };
    _vsntprintf_s(buf, _countof(buf), format, args);
    va_end(args);

    std::string debug_str;
    debug_str =
#ifdef DEBUG_INFO_DATE
#ifdef DEBUG_INFO_DATE_NEW_LINE
        std::string("\n") +
#else
        std::string(" / ") +
#endif // DEBUG_INFO_DATE_NEW_LINE
#ifdef DEBUG_INFO_NAME
#endif //DEBUG_INFO_NAME
        "date : " + date +
#endif // DEBUG_INFO_DATE
#ifdef DEBUG_INFO_FILE
#ifdef DEBUG_INFO_FILE_NEW_LINE
        std::string("\n") +
#else
        std::string(" / ") +
#endif // DEBUG_INFO_FILE_NEW_LINE
#ifdef DEBUG_INFO_NAME
        "file : " +
#endif //DEBUG_INFO_NAME
        file +
#endif // DEBUG_INFO_FILE
#ifdef DEBUG_INFO_FUNCTION
#ifdef DEBUG_INFO_FUNCTION_NEW_LINE
        std::string("\n") +
#else
        std::string(" / ") +
#endif // DEBUG_INFO_FUNCTION_NEW_LINE
#ifdef DEBUG_INFO_NAME
        "function : " +
#endif //DEBUG_INFO_NAME
        function +
#endif // DEBUG_INFO_FUNCTION
#ifdef DEBUG_INFO_LINE
#ifdef DEBUG_INFO_LINE_NEW_LINE
        std::string("\n") +
#else
        std::string(" / ") +
#endif // DEBUG_INFO_LINE_NEW_LINE
#ifdef DEBUG_INFO_NAME
        "line : " +
#endif //DEBUG_INFO_NAME
        line +
#endif // DEBUG_INFO_LINE
#ifdef DEBUG_INFO_NEW_LINE
        std::string("\n") +
#else
        std::string(" ¢º ");
#endif // DEBUG_INFO_NEW_LINE

#ifdef DEBUG_INFO_FUNCTION
    // FUNCTION split debug_str
    std::string delimiter = "::";
    size_t pos = 0;
    std::string token;
    int count = 0;
    while ((pos = debug_str.find(delimiter)) != std::string::npos)
    {
        token = debug_str.substr(0, pos);
        debug_str.erase(0, pos + delimiter.length());
        count++;
        if (count >= 2)
        {
            break;
        }
    }
#endif // DEBUG_INFO_FUNCTION

    std::cout << debug_str << buf << std::endl;
}