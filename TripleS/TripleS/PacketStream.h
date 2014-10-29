#pragma once


namespace TripleS
{
	class PacketStream
	{
	public:
		enum 
		{
			DEFAULT_BUFFER_SIZE = 1024,
			DEFAULT_INCREASE_SIZE = 1024
		};

		PacketStream()
		{
			DataBuffer	   = new Byte[ DEFAULT_BUFFER_SIZE ];
			Capacity	   = DEFAULT_BUFFER_SIZE;
			BufferEndPos   = DataBuffer + DEFAULT_BUFFER_SIZE;
			BufferPos	   = DataBuffer;
			IncSize        = DEFAULT_INCREASE_SIZE;
			OwnBuffer	   = TRUE;
			IsValid		   = TRUE;
			::memset( DataBuffer, 0, DEFAULT_BUFFER_SIZE );
		}

		explicit PacketStream( UInt32 bufferSize )
		{
			if ( bufferSize < DEFAULT_BUFFER_SIZE )
			{
				bufferSize = DEFAULT_BUFFER_SIZE;
			}

			DataBuffer	   = new Byte[ bufferSize ];
			Capacity	   = bufferSize;
			BufferEndPos   = DataBuffer + bufferSize;
			BufferPos	   = DataBuffer;
			IncSize		   = DEFAULT_INCREASE_SIZE;
			OwnBuffer	   = TRUE;
			::memset( DataBuffer, 0, DEFAULT_BUFFER_SIZE );
		}

		PacketStream( Byte* data, UInt32 size )
		{
			DataBuffer		= data;
			Capacity		= size;
			BufferEndPos	= DataBuffer + Capacity;
			BufferPos		= DataBuffer;
			IncSize			= DEFAULT_INCREASE_SIZE;
			OwnBuffer		= FALSE;
		}

		~PacketStream()
		{
			if ( OwnBuffer )
			{
				delete[] DataBuffer;
			}
		}

		void ResetIncSize()
		{
			IncSize = DEFAULT_INCREASE_SIZE;
		}

		void ResetSize()
		{
			if ( Capacity > DEFAULT_BUFFER_SIZE && OwnBuffer )
			{
				delete[] DataBuffer;

				DataBuffer		= new Byte[ DEFAULT_BUFFER_SIZE ];
				Capacity		= DEFAULT_BUFFER_SIZE;
				BufferPos		= DataBuffer;
				BufferEndPos	= DataBuffer + Capacity;
				IncSize			= DEFAULT_INCREASE_SIZE;
			}
		}

		void SetCapacity( UInt32 size )
		{
			if ( Capacity < size )
			{
				Resize( size );
			}
		}
		
		void ResetBufferPos()
		{
			BufferPos = DataBuffer;
		}

		void Reset()
		{
			ResetBufferPos();

			assert( BufferEndPos == DataBuffer + Capacity );
			assert( BufferPos == DataBuffer );
		}
		
		UInt32 Write( const char* buf, UInt32 count );
		UInt32 Write( const Byte* buf, UInt32 count );
		UInt32 Read( char* buf, UInt32 count );
		UInt32 Read( Byte* buf, UInt32 count );
		
		//string, wstring,은 따로 해둬야하나?.. 템플릿으로 다 가능할까?.
		// 생각해보니 string, wstring은 문자열의 길이를 알아야하는구나.. 구현 해야할듯.. 나중에 하자..
		template <typename T>
		UInt32 Write( const T& data );

		template <typename T>
		UInt32 Read( T& data );
		
		Byte*  GetPtr()			{ return DataBuffer; }
		Byte*  GetCurPos()		{ return BufferPos;  }
		UInt32 GetCurSize()		{ return static_cast< UInt32 >( BufferPos - DataBuffer ); }
		UInt32 GetRemainSize()  { return static_cast< UInt32 >( BufferEndPos - BufferPos ); }

	private:
		void   Resize( UInt32 requiredSize );

	private:
		Byte*	DataBuffer;			// 버퍼
		Byte*	BufferPos;		    // 현재 버퍼포인터의 위치.
		Byte*	BufferEndPos;		// 버퍼의 끝 포인터
		UInt32	Capacity;			// 버퍼의 크기
		UInt32	IncSize;			// 기본 증가 크기
		Bool    OwnBuffer;			// 외부의 버퍼와 연결시켰다면 false 내부의 생성 버퍼라면 true
		Bool    IsValid;			// 버퍼가 유효한가? 
	};

	inline void PacketStream::Resize( UInt32 requiredSize )
	{
		UInt32 newSize = 1 << 8;

		if ( newSize < requiredSize )
		{
			newSize += IncSize;
		}

		Byte* p = new Byte[ newSize ];

		if ( DataBuffer != 0 )
		{
			assert( Capacity > 0 );

			::memcpy( p, ( void* )DataBuffer, Capacity );

			Capacity = newSize;
			
			UInt32 newPos = 0;
			
			newPos			= static_cast< UInt32 >( BufferPos - DataBuffer );
			BufferPos		= p + newPos;
			BufferEndPos	= p + newSize;

			delete [] DataBuffer;
		}

		DataBuffer = p;
	}

	inline UInt32 Write( const char* buf, UInt32 count )
	{
		return Write( ( const Byte* )buf, count );
	}

	inline UInt32 Write( const Byte* buf, UInt32 count )
	{
		UInt32 written = count;

		// 버퍼의 사이즈를 초과했다. 버퍼크기를 리사이징 하자.
		if ( BufferPos + written >= BufferEndPos )
		{
			
			// 초과된 크기를 알아내자
			UInt32 requireSize = static_cast< UInt32 >( ( BufferPos + written ) - BufferEndPos );
			Resize( ( UInt32 )( Capacity + requireSize ) );
		}

		memcpy( BufferPos, buf, count );
		BufferPos += count;

		return count;
	}


	inline UInt32 Read( char* buf, UInt32 count )
	{
		return Read( ( Byte* )buf, count );
	}

	inline UInt32 Read( Byte* buf, UInt32 count )
	{
		if ( nullptr == buf )
		{
			return 0;
		}

		if ( !IsValid )
		{
			return 0;
		}

		UInt32 size = count;

		if ( BufferPos + size > BufferEndPos )
		{
			IsValid = FALSE;

			size = static_cast< UInt32 >( BefferEndPos - BufferPos );
		}

		if ( size == 0 )
		{
			return 0;
		}

		assert( size <= count );
		memcpy( buf, BufferPos, size );

		BufferPos += size;

		return size;
	}

	template <typename T>
	inline UInt32 Write( const T& data )
	{
		return Write( ( const Byte* )&data, sizeof( T ) );
	}

	template <typename T>
	inline UInt32 Read( T& data )
	{
		return Read( ( Byte* )&data, sizeof( T ) );
	}
}// namespace end


