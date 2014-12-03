#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

// 이곳에 구글 프로토버퍼와 연결해 사용할 버퍼를 만들어야한다.
// 1 . protobuf::io::ArrayOutputStream   os( 직렬화할 버퍼, 버퍼 사이즈 )
// 2. object.SerializeToZeroCopyStream( &os )  직렬화
// 3. protobuf::io::ArrayInputStream is( 역직렬화할 버퍼, bufsize );
// 4. object.ParseFromZeroCopyStream( &is ) 역직렬화 -> object의 내용을 채워줌
// 위 의 과정중 직렬화, 역직렬화를 하려면 protoc.exe로 생성된 프로토콜 클래스 객체를 사용해야함

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