#pragma once


#include "PacketHead.h"

namespace TripleS
{

#pragma pack( push, 1 )
	struct PacketInfo
	{
		// ��Ŷ Ÿ��.(�������� �ڵ�)
        PACKET_TYPE code;

	};
#pragma  pack(pop)


}