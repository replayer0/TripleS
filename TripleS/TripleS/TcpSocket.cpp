#include "StdAfx.h"

#include "TcpSocket.h"
#include "TcpService.h"
#include "Proactor.h"
#include "Disconnector.h"
#include "Acceptor.h"
#include "Sender.h"
#include "Receiver.h"

TripleS::TcpSocket::TcpSocket(TcpService& tcp_service)
    : m_tcp_service(tcp_service),
    m_proactor(*tcp_service.m_proactor),
    m_acceptor(*tcp_service.m_acceptor),
    m_disconnector(*tcp_service.m_disconnector),
    m_sender(*tcp_service.m_sender),
    m_receiver(*tcp_service.m_receiver)
{
    // socket
    m_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (m_socket == INVALID_SOCKET)
    {
        DEBUG_INFO(eDEBUG_LOW, "WSASocket() Error!!! err(%d)\n", WSAGetLastError());
    }

    // buffer
    wsaRecvBuf.buf = (char*)RecvActBuf.GetPtr();
    wsaRecvBuf.len = BUFSIZE;
    wsaSendBuf.buf = SendBuf_;
    wsaSendBuf.len = BUFSIZE;

    ZeroMemory(SendBuf_, BUFSIZE);
    ZeroMemory(AcceptBuf_, BUFSIZE);

    // act
    m_act[ACT_ACCEPT].Init(&m_acceptor, this);
    m_act[ACT_RECV].Init(&m_receiver, this);
    m_act[ACT_SEND].Init(&m_sender, this);
    m_act[ACT_DISCONNECT].Init(&m_disconnector, this);
}

TripleS::TcpSocket::~TcpSocket()
{
}

bool TripleS::TcpSocket::Completed(PACKET_TYPE key, PacketPtr& packet)
{
    return m_tcp_service.m_functorAdapter.Execute(key, packet);
};

SOCKET TripleS::TcpSocket::GetSocket() const
{
	return m_socket;
}

Int32 TripleS::TcpSocket::RecvCompleted(Act* act, Proactor& proactor, UInt32 len )
{
	
	if ( len <= 0 )
	{
		return -1;
	}

	RecvBuf.Write( RecvActBuf.GetPtr(), len );

	SetTotalRecvSize( len );
	
	BuildPacket();
		
	Recv();

	return len;
}

#define PACKET_SIZE 4
void  TripleS::TcpSocket::BuildPacket()
{
	
	PacketStream& recvBuff = GetRecvBuff();
	Byte* data = recvBuff.GetPtr();
	UInt32 dataSize = recvBuff.GetCurSize();
	UInt32 processedSize = 0;
	UInt32 packetCount = 0;

	while ( PACKET_SIZE <= dataSize )
	{
		Int32* packetSizePtr = reinterpret_cast< Int32* >( data );
		UInt32 packetLength = *packetSizePtr;

		// 패킷이 버퍼를 초과.
		if ( packetLength > BUFSIZE )
		{
			Disconnect();
			break;
		}

		// data가 아직 덜 쌓임.
		if ( packetLength + PACKET_SIZE > dataSize )
		{
			break;
		}

		UInt32 length = packetLength;

		void* packet = ( void* )( data + PACKET_SIZE );

		if ( !m_proactor.ProcessPacket( this, packet, static_cast< Int32 >( length ) ) )
		{
			Disconnect();
			break;
		}

		++packetCount;

		processedSize += ( packetLength + PACKET_SIZE );
		data = data + ( packetLength + PACKET_SIZE ); // 이전 위치에서 처리 길이만큼 앞으로 이동
		dataSize = dataSize - ( packetLength + 4 ); //처리한만큼 줄여줌.
				
	} // while end

	if ( processedSize > 0 )
	{
		recvBuff.Pop( processedSize );
	}
}

void TripleS::TcpSocket::Recv()
{
	DWORD recvbytes = wsaRecvBuf.len;
	DWORD flags = 0;
	
	RecvActBuf.SetCapacity( BUFSIZE );

	INT ret	= WSARecv( m_socket, &(wsaRecvBuf), 1, &recvbytes, &flags, static_cast<OVERLAPPED*>(&(m_act[ACT_RECV])), NULL );

	if( ret != 0 )
	{
		int error = WSAGetLastError();

		if( error != ERROR_IO_PENDING )
		{
			printf( "WSARecv() Error!!! s(%d) err(%d)\n", m_socket, error );
			Disconnect();
		}
	}
}

void TripleS::TcpSocket::Send(BYTE* buf, int buflen)
{
	DWORD sentbytes = 0;
	wsaSendBuf.buf	= reinterpret_cast<char*>(buf);
	wsaSendBuf.len	= buflen;

	INT ret	= WSASend(m_socket, &(wsaSendBuf), 1, &sentbytes, 0, static_cast<OVERLAPPED*>(&(m_act[ACT_SEND])), NULL);

	if( ret != 0 )
	{
		int error = WSAGetLastError();

		if( error != ERROR_IO_PENDING )
		{
			printf( "WSASend() Error!!! s(%d) err(%d)\n", m_socket, error );
			Disconnect();
		}
	}
}

const bool TripleS::TcpSocket::RegistAccept()
{
	return m_acceptor.Register( *this );
}

const bool TripleS::TcpSocket::Disconnect()
{
	BOOL ret = TransmitFile(	
		m_socket, 
		NULL, 
		0, 
		0, 
		static_cast<OVERLAPPED*>(&(m_act[ACT_DISCONNECT])), 
		NULL, 
		TF_DISCONNECT | TF_REUSE_SOCKET
		);

	if( !ret )
	{
		int error = WSAGetLastError();
		if( error != ERROR_IO_PENDING )
		{
			printf("DisconnectEx Error!!! s(%d), err(%d)\n", m_socket, error);
		}
	}

    return ret;
}

void TripleS::TcpSocket::SetTotalRecvSize( const UInt32& size )
{
	// 일단은 단순하게.. 계산.. 나중엔 리시브 하다가 오래 걸리거나( 이럴경우가 발생할까? ) 하면 시간도 체크해서 리셋해주는게 필요할듯..
	TotalRecvSize += size;
}