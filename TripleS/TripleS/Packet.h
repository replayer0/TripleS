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
	// ��Ŷ�� �Ÿ������.?
	// ��Ŷ�� �۽����� ������ ���� ������? (ex :  sessionIndex , ���.. )
	// 	

	virtual void Reset()
	{
		// ����.
	}
};


PACKET_DECL_BEGIN( SamplePacket, Packet, 10 )
	UInt32 age = 30;
	void Reset()
	{
		age = 0;
	}

	// PacketStream���� ���ۿ� ���� ����.
	// PacketStream���� ���ۿ��� �б� ����.
	// TODO...::

PACKET_DECL_END