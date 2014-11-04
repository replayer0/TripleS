#include "stdafx.h"

#include "Acceptor.h"

#include "TcpListenSocket.h"
#include "TcpSocket.h"

using namespace TripleS;

TripleS::Acceptor::Acceptor(TcpListenSocket& tcp_listen_socket, Proactor& proactor)
    : Actor(proactor), m_tcp_listen_socket(tcp_listen_socket)
{

}

void TripleS::Acceptor::ProcEvent(Act* act, DWORD bytes_transferred)
{
	TcpAct& tcpact = *dynamic_cast<TcpAct*>(act);

	//assert(tcpact.TcpSocket_);
	TcpSocket& tcpsocket = *tcpact.TcpSocket_;
	
	//assert(Proactor_);

	//printf("...Acceptor s(%d)\n", tcpsocket.GetSocket());

	m_proactor.Register(reinterpret_cast<HANDLE>(tcpsocket.GetSocket()));

	tcpsocket.Recv();
}

void TripleS::Acceptor::ProcError(Act* act, DWORD error)
{
	//assert(dynamic_cast<TcpAct*>(act));

	TcpAct& tcpact = *dynamic_cast<TcpAct*>(act);

	//assert(tcpact.TcpSocket_);

	TcpSocket& tcpsocket = *tcpact.TcpSocket_;

	//printf("...에러처리 Acceptor s(%d) err(%d)\n", tcpsocket.GetSocket(), error );
}

void TripleS::Acceptor::Register(TcpSocket& acceptsocket)
{
    m_sockets.push(&acceptsocket);
	DWORD byte_transferred;
		
	BOOL ret =	AcceptEx(
			m_tcp_listen_socket.GetSocket(), 
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

TripleS::Acceptor::~Acceptor()
{
    // 임시 떔빵
    while (m_sockets.empty() == false)
    {
        auto socket = m_sockets.front();
        delete socket;
        m_sockets.pop();
    }
}