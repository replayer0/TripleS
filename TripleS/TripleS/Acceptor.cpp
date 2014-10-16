#include "stdafx.h"

#include "Acceptor.h"

#include "TcpListenSocket.h"
#include "TcpSocket.h"

using namespace TripleS::iocp;

void TripleS::iocp::Acceptor::ProcEvent(Act* act, DWORD bytes_transferred)
{
	TcpAct& tcpact = *dynamic_cast<TcpAct*>(act);

	//assert(tcpact.TcpSocket_);
	TcpSocket& tcpsocket = *tcpact.TcpSocket_;
	
	//assert(Proactor_);

	//printf("...Acceptor s(%d)\n", tcpsocket.GetSocket());

	Proactor_->Register(reinterpret_cast<HANDLE>(tcpsocket.GetSocket()));

	tcpsocket.Recv();
}

void TripleS::iocp::Acceptor::ProcError(Act* act, DWORD error)
{
	//assert(dynamic_cast<TcpAct*>(act));

	TcpAct& tcpact = *dynamic_cast<TcpAct*>(act);

	//assert(tcpact.TcpSocket_);

	TcpSocket& tcpsocket = *tcpact.TcpSocket_;

	//printf("...에러처리 Acceptor s(%d) err(%d)\n", tcpsocket.GetSocket(), error );
}

void TripleS::iocp::Acceptor::Init(TripleS::type::P_TCPLISTENSOCKET tcplistensocket,
    TripleS::type::P_PROACTOR proactor)
{
	TcpListenSocket_ = tcplistensocket;
	Proactor_ = proactor;
}

void TripleS::iocp::Acceptor::Register(TcpSocket& acceptsocket)
{
	DWORD byte_transferred;
		
	BOOL ret =	AcceptEx(
			TcpListenSocket_->GetSocket(), 
			acceptsocket.GetSocket(), 
			acceptsocket.AcceptBuf_, 
			0, 
			sizeof(SOCKADDR_IN) + 16,
			sizeof(SOCKADDR_IN) + 16,
			&byte_transferred,
			static_cast<OVERLAPPED*>(&acceptsocket.Act_[TcpSocket::ACT_ACCEPT])
 			);

	int error = WSAGetLastError();

	if( ret == FALSE && error != ERROR_IO_PENDING ) 
	{
		printf( "AcceptEx Error!!! s(%d), err(%d)\n", acceptsocket.GetSocket(), error );	
	}
}
