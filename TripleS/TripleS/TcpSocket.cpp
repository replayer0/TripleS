#include "StdAfx.h"

#include "TcpSocket.h"

#include "Proactor.h"
#include "Disconnector.h"
#include "Acceptor.h"
#include "Sender.h"
#include "Receiver.h"

TripleS::TcpSocket::TcpSocket()
{
	Socket_ = INVALID_SOCKET;
	Acceptor_ = NULL;
}

void TripleS::TcpSocket::Init()
{
	Socket_ = WSASocket( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );

	if( Socket_ == INVALID_SOCKET )
	{
		printf("WSASocket() Error!!! err(%d)\n", WSAGetLastError());
	}

	InitBuf();
}

void TripleS::TcpSocket::InitBuf()
{
	wsaRecvBuf.buf = RecvBuf_;
	wsaRecvBuf.len = BUFSIZE;

	wsaSendBuf.buf = SendBuf_;
	wsaSendBuf.len = BUFSIZE;

	ZeroMemory( RecvBuf_, BUFSIZE );
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
    Proactor_ = proactor;
    Acceptor_ = acceptor;
    Disconnector_ = disconnector;
    Sender_ = sender;
    Receiver_ = receiver;

	Act_[ACT_ACCEPT].Init( Acceptor_, this );
	Act_[ACT_RECV].Init( Receiver_, this );
	Act_[ACT_SEND].Init( Sender_, this );
	Act_[ACT_DISCONNECT].Init( Disconnector_, this );
}

SOCKET TripleS::TcpSocket::GetSocket() const
{
	return Socket_;
}

void TripleS::TcpSocket::Recv()
{
	DWORD recvbytes = 0;
	DWORD flags = 0;


	INT ret	= WSARecv( Socket_, &(wsaRecvBuf), 1, &recvbytes, &flags, static_cast<OVERLAPPED*>(&(Act_[ACT_RECV])), NULL );

	if( ret != 0 )
	{
		int error = WSAGetLastError();

		if( error != ERROR_IO_PENDING )
		{
			printf( "WSARecv() Error!!! s(%d) err(%d)\n", Socket_, error );
			Disconnect();
		}
	}
}

void TripleS::TcpSocket::Send(BYTE* buf, int buflen)
{
	DWORD sentbytes = 0;
	wsaSendBuf.buf	= reinterpret_cast<char*>(buf);
	wsaSendBuf.len	= buflen;

	INT ret	= WSASend(Socket_, &(wsaSendBuf), 1, &sentbytes, 0, static_cast<OVERLAPPED*>(&(Act_[ACT_SEND])), NULL);

	if( ret != 0 )
	{
		int error = WSAGetLastError();

		if( error != ERROR_IO_PENDING )
		{
			printf( "WSASend() Error!!! s(%d) err(%d)\n", Socket_, error );
			Disconnect();
		}
	}
}

void TripleS::TcpSocket::Reuse()
{
	Acceptor_->Register( *this );
}

void TripleS::TcpSocket::Disconnect()
{
	BOOL ret = TransmitFile(	
		Socket_, 
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
			printf("DisconnectEx Error!!! s(%d), err(%d)\n", Socket_, error);
		}
	}
}