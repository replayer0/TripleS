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


struct Packet : public PacketHead
{
	// 패킷이 어떤타입인지.?
	// 패킷에 송신측의 정보를 담을 것인지? (ex :  sessionIndex , 등등.. )
	// 	

	virtual void Reset()
	{
		// 내용.
	}
};


PACKET_DECL_BEGIN( SamplePacket, Packet, 10 )
	UInt32 age = 30;
	void Reset()
	{
		age = 0;
	}

	// PacketStream으로 버퍼에 쓰기 동작.
	// PacketStream으로 버퍼에서 읽기 동작.
	// TODO...::

PACKET_DECL_END