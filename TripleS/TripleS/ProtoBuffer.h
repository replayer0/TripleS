#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

// �̰��� ���� ��������ۿ� ������ ����� ���۸� �������Ѵ�.
// 1 . protobuf::io::ArrayOutputStream   os( ����ȭ�� ����, ���� ������ )
// 2. object.SerializeToZeroCopyStream( &os )  ����ȭ
// 3. protobuf::io::ArrayInputStream is( ������ȭ�� ����, bufsize );
// 4. object.ParseFromZeroCopyStream( &is ) ������ȭ -> object�� ������ ä����
// �� �� ������ ����ȭ, ������ȭ�� �Ϸ��� protoc.exe�� ������ �������� Ŭ���� ��ü�� ����ؾ���

namespace TripleS
{

	class ProtoBuffer
	{
	public:
		
		ProtoBuffer();
		explicit ProtoBuffer( void* dataBuffer, Int32 bufferSize );
		
		void SetBufferSize( Int32 bufferSize );
		void SetBufferPtr( void* buffer );
		const Int32 GetBufferSize();

		void Serialization();

	private:
		Int32  m_bufferSize;
		Byte*  m_buffer;

	};

}