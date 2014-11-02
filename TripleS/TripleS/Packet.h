#pragma once


#include "PacketHead.h"
#include "PacketStream.h"

namespace TripleS
{

#pragma pack( push, 1 )
	struct PacketInfo
	{
		// 패킷 타입.(프로토콜 코드)
		UShort code;

	};
#pragma  pack(pop)

	struct Packet : public PacketHead < UInt32 >
	{
		UInt32 idx; // 소켓 세션인덱스

		Packet()
		{
			Reset();
		}

		virtual ~Packet(){}

		virtual void Reset()
		{
			idx = 0;
		}


		virtual Bool Input( PacketStream& ps )
		{
			ps.Write( GetPacketType() );
			return true;
		}

		virtual Bool Output( PacketStream& ps )
		{
			UShort code = 0;
			ps.Read( code );
			SetHead( code );
			return true;
		}
	};


 	struct SamplePacket : public Packet
 	{
 		static const UInt32 cProtocol = 10;
 
 		UInt32 age = 30;
 
 		SamplePacket()
 		{
 			SetHead( cProtocol );
 			Reset();
 		}
 
 		void Reset()
 		{
 			age = 0;
 		}
 	};
}