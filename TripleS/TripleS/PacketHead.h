#pragma once

template <typename T>
class PacketHead
{
public:

	PacketHead( T packetType = 0 )
		: m_packetType( packetType )
	{
	}

	UShort GetPacketType() const
	{
		assert( m_packetType );
		return m_packetType;
	}

	void SetHead( const T& packetType )
	{
		assert( packetType );
		m_packetType = packetType;
	}

private:
	T m_packetType;
};