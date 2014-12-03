#include "stdafx.h"

#include "ProtoBuffer.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

// 이클래스는 조금더 생각해봐야겠다.. 
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
		// 버퍼포인터를 이동시키면서 데이터를 가져와야하나? 리시브버퍼나 이런데서..
		m_buffer = reinterpret_cast< Byte* >(buffer);
	}
	
	const Int32 ProtoBuffer::GetBufferSize()
	{
		return m_bufferSize;
	}

	void ProtoBuffer::Serialization()
	{
		protobuf::io::ArrayOutputStream output( m_buffer, m_bufferSize );
		// protoc.exe로 생성된 클래스 오브젝트가 필요한데.. 어케 가져오지..
		// object.SerializeToZeropCopyStream( &output ).. 을 해야하는데..
		// object를 어케 가져오지...
	}
}