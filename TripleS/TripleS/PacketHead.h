#pragma once
typedef UInt32  PACKET_TYPE;

class PacketHead
{
public:

    PacketHead(PACKET_TYPE packetType)
		: m_packetType( packetType )
	{
	}

    PACKET_TYPE GetPacketType() const
	{
		return m_packetType;
	}


private:
    PACKET_TYPE m_packetType;
};