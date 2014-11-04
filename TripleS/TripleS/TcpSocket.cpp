#include "StdAfx.h"

#include "TcpSocket.h"

#include "Proactor.h"
#include "Disconnector.h"
#include "Acceptor.h"
#include "Sender.h"
#include "Receiver.h"

TripleS::TcpSocket::TcpSocket()
	: TotalRecvSize( 0 )
{
	m_socket = INVALID_SOCKET;
	m_acceptor = NULL;
}

void TripleS::TcpSocket::Init()
{
	m_socket = WSASocket( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );

	if( m_socket == INVALID_SOCKET )
	{
		printf("WSASocket() Error!!! err(%d)\n", WSAGetLastError());
	}

	InitBuf();
}

void TripleS::TcpSocket::InitBuf()
{
	wsaRecvBuf.buf = (char*)RecvActBuf.GetPtr();
	wsaRecvBuf.len = BUFSIZE;

	wsaSendBuf.buf = SendBuf_;
	wsaSendBuf.len = BUFSIZE;

	ZeroMemory( SendBuf_, BUFSIZE );

	ZeroMemory( AcceptBuf_, BUFSIZE );
}

void TripleS::TcpSocket::InitAct(
    Proactor* proactor,
    Acceptor* acceptor,
    Disconnector* disconnector,
    Sender* sender,
    Receiver* receiver
    )
{
    m_proactor = proactor;
    m_acceptor = acceptor;
    m_disconnector = disconnector;
    m_sender = sender;
    m_receiver = receiver;

	Act_[ACT_ACCEPT].Init( m_acceptor, this );
	Act_[ACT_RECV].Init( m_receiver, this );
	Act_[ACT_SEND].Init( m_sender, this );
	Act_[ACT_DISCONNECT].Init( m_disconnector, this );
}

SOCKET TripleS::TcpSocket::GetSocket() const
{
	return m_socket;
}

Int32 TripleS::TcpSocket::RecvCompleted( UInt32 len )
{
	
	if ( len <= 0 )
	{
		return -1;
	}

	RecvBuf.Write( RecvActBuf.GetPtr(), len );

	SetTotalRecvSize( len );
	
	BuildPacket();
		
	Recv();
}

void  TripleS::TcpSocket::BuildPacket( )
{
	// ��Ŷ ������ �ؾ� �Ѵ�.
	//TODO::  ...
}

void TripleS::TcpSocket::Recv()
{
	DWORD recvbytes = wsaRecvBuf.len;
	DWORD flags = 0;
	
	RecvActBuf.SetCapacity( BUFSIZE );

	INT ret	= WSARecv( m_socket, &(wsaRecvBuf), 1, &recvbytes, &flags, static_cast<OVERLAPPED*>(&(Act_[ACT_RECV])), NULL );

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

	INT ret	= WSASend(m_socket, &(wsaSendBuf), 1, &sentbytes, 0, static_cast<OVERLAPPED*>(&(Act_[ACT_SEND])), NULL);

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

void TripleS::TcpSocket::Reuse()
{
	m_acceptor->Register( *this );
}

void TripleS::TcpSocket::Disconnect()
{
	BOOL ret = TransmitFile(	
		m_socket, 
		NULL, 
		0, 
		0, 
		static_cast<OVERLAPPED*>(&(Act_[ACT_DISCONNECT])), 
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
}

void TripleS::TcpSocket::SetTotalRecvSize( const UInt32& size )
{
	// �ϴ��� �ܼ��ϰ�.. ���.. ���߿� ���ú� �ϴٰ� ���� �ɸ��ų�( �̷���찡 �߻��ұ�? ) �ϸ� �ð��� üũ�ؼ� �������ִ°� �ʿ��ҵ�..
	TotalRecvSize += size;
}