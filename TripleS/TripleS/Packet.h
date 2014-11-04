#pragma once


#include "PacketHead.h"
#include "PacketStream.h"
#include "PacketQueue.h"

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

	// 패킷은 복제되어선 안되고, 항상 유일해야 한다.
	// unique_ptr 은 대입연산자, 복사생성자가 없다. 
	// 소유권이전을 시키고 싶으면 utility를 include해서 move()를 쓸것.
	// 그럼 이전 소유권자는 nullptr이 되고 안전할 것이다.
	typedef std::unique_ptr<Packet> PacketPtr;
	typedef TripleS::PacketConcurrentQ<PacketPtr> PacketQ;
	
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