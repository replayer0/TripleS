#pragma once

#include "PacketHead.h"

#ifndef _DEBUG
#define PACKET_DECL_BEGIN( _packet_class, _super_class, _protocol ) \
struct _packet_class : public _super_class {	\
private: \
	typedef _super_class super; \
public: \
	static const UShort cProtocol = _protocol; \
	_packet_class() { \
		SetHead( cProtocol ); \
		Reset(); \
	} \

	virtual ~_packet_class() {}
#else
#define PACKET_DECL_BEGIN( _packet_class, _super_class, _protocol ) \
struct _packet_class : public _super_class { \
private: \
	typedef _super_class super; \
public: \
	static const UShort cProtocol = _protocol; \
	_packet_class() { \
		SetHead( cProtocol ); \
		Reset(); \
	} \
	virtual ~_packet_class() {} \

#endif
#define PACKET_DECL_END };


#pragma push( push, 1 )
struct PacketInfo
{
	// 패킷 타입.(프로토콜 코드)
	UShort code;

};
#pragma  pop(pop)



struct Packet : public PacketHead
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


PACKET_DECL_BEGIN( SamplePacket, Packet, 10 )
	UInt32 age = 30;
	void Reset()
	{
		age = 0;
	}

	Bool Input( PacketStream& ps )
	{
		super::Input( ps );
		ps.Write( age );
	}

	Bool Output( PacketStream& ps )
	{
		super::Output( ps );
		ps.Read( age );
	}
PACKET_DECL_END