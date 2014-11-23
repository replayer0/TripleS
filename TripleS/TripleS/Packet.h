#pragma once


#include "PacketHead.h"

namespace TripleS
{

#pragma pack( push, 1 )
	struct PacketInfo
	{
		// 패킷 타입.(프로토콜 코드)
        PACKET_TYPE code;

	};
#pragma  pack(pop)


}