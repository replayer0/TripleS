#pragma once

//#include <Windows.h>

#undef max
#undef min


#include <hash_map>
#include <map>
#include <string>
#include <vector>
#include <deque>
#include <set>


typedef	bool						Bool;			
typedef	unsigned char				Byte;			
typedef	short						Short;			
typedef	unsigned short				UShort;			
typedef char						Int8;
typedef unsigned char				UInt8;
typedef short						Int16;
typedef unsigned short				UInt16;
typedef	int							Int32;			
typedef	unsigned int				UInt32;			
typedef	__int64						Int64;			
typedef	unsigned __int64			UInt64;			
typedef	float						Float;			
typedef	double						Double;			
typedef	char 						Char;			
typedef	wchar_t						WChar;			
typedef	long						Long;
typedef	unsigned long				ULong;

typedef unsigned long				ThreadId;
typedef std::string					String;

#ifdef  UNICODE                   
typedef	WChar						TChar;
typedef	std::wstring				TString;
typedef	std::wstring				tstring;
#else
typedef	Char						TChar;
typedef	std::string					TString;
typedef	std::string					tstring;
#endif

typedef std::set<UInt32>			UInt32_Set;
typedef	std::vector<String>			StringVector;
//typedef	std::list<UInt32>			UInt32List;
typedef	std::vector<UInt32>			UInt32Vector;
typedef	std::list<UInt64>			UInt64List;
typedef	std::vector<UInt64>			UInt64Vector;
typedef	std::vector<Byte>			ByteVector;

#if(0x0600 <= WINVER)
typedef	UInt64						TTickCount;
#else
typedef	UInt32						TTickCount;
#endif