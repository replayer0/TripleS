#pragma once

#include <concurrent_queue.h>

namespace TripleS
{
	template < typename T >
	class PacketConcurrentQ
	{
	public:
		Bool push( const T& v )
		{
			m_queue.push( v );

			return true;
		}

		Bool pop( T& v )
		{
			return m_queue.try_pop( v );
		}

		size_t size()
		{
			return m_queue.unsafe_size();
		}

	private:
		concurrency::concurrent_queue<T> m_queue;
	};
}

