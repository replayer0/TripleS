#include "stdafx.h"

#include "ProtoBuffer.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

// ��Ŭ������ ���ݴ� �����غ��߰ڴ�.. 
namespace TripleS
{
	ProtoBuffer::ProtoBuffer()
		: m_bufferSize( 0 )
	{
		
	}

	explicit ProtoBuffer::ProtoBuffer( void* dataBuffer, Int32 bufferSize )
		: m_bufferSize( bufferSize )
		, m_buffer( dataBuffer )
	{
		
	}

	void ProtoBuffer::SetBufferSize( Int32 bufferSize )
	{
		m_bufferSize = bufferSize;
	}

	void ProtoBuffer::SetBufferPtr( void* buffer )
	{
		// ���������͸� �̵���Ű�鼭 �����͸� �����;��ϳ�? ���ú���۳� �̷�����..
		m_buffer = reinterpret_cast< Byte* >(buffer);
	}
	
	const Int32 ProtoBuffer::GetBufferSize()
	{
		return m_bufferSize;
	}

	void ProtoBuffer::Serialization()
	{
		protobuf::io::ArrayOutputStream output( m_buffer, m_bufferSize );
		// protoc.exe�� ������ Ŭ���� ������Ʈ�� �ʿ��ѵ�.. ���� ��������..
		// object.SerializeToZeropCopyStream( &output ).. �� �ؾ��ϴµ�..
		// object�� ���� ��������...
	}
}