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
        PACKET_TYPE code;

	};
#pragma  pack(pop)

	class Packet : public PacketHead
	{
    public:
		UInt32 idx; // ���� �����ε���

        Packet(PACKET_TYPE packet_type)
			: PacketHead(packet_type)
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
			return true;
		}

        
	};

    typedef std::unique_ptr<Packet> PacketPtr;

    struct SamplePacket : public TripleS::Packet
    {
        UInt32 age = 30;
        SamplePacket()
            : Packet(10)
        {
            Reset();
        }

        ~SamplePacket()
        {

        }

 		void Reset()
 		{
 			age = 0;
 		}
 	};
}