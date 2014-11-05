#pragma once


#include "PacketHead.h"
#include "PacketStream.h"
#include "PacketQueue.h"

namespace TripleS
{

#pragma pack( push, 1 )
	struct PacketInfo
	{
		// ��Ŷ Ÿ��.(�������� �ڵ�)
		UShort code;

	};
#pragma  pack(pop)

	struct Packet : public PacketHead < UInt32 >
	{
		UInt32 idx; // ���� �����ε���

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

	// ��Ŷ�� �����Ǿ �ȵǰ�, �׻� �����ؾ� �Ѵ�.
	// unique_ptr �� ���Կ�����, ��������ڰ� ����. 
	// ������������ ��Ű�� ������ utility�� include�ؼ� move()�� ����.
	// �׷� ���� �������ڴ� nullptr�� �ǰ� ������ ���̴�.
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