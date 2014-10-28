#pragma once

class PacketHead
{
public:

	PacketHead( UShort packetType = 0 )
		: m_packetType( packetType )
	{
	}

	UShort GetPacketType() const
	{
		assert( m_packetType );
		return m_packetType;
	}

	void SetHead( const UShort& packetType )
	{
		assert( packetType );
		m_packetType = packetType;
	}

private:
	UShort m_packetType;
};