#pragma once

#include "TcpSocket.h"
#include <string>

class User
{
public:
    User()
    {
    };
    ~User(){};

    void SetID(std::string id)
    {
        m_id = id;
    }
    std::string& GetID()
    {
        return m_id;
    }
    void SetSocket(TripleS::TcpSocket* socket)
    {
        m_socket = socket;
        if (m_session_idx == 0)
        {
            m_session_idx = m_socket->GetSessionIdx();
        }
        else
        {
            m_socket->SetSessionIdx(m_session_idx);
        }
    }
    void SendToUser(TripleS::PACKET_TYPE packet_type, const TripleS::PROTOBUF_PACKET& message)
    {
        m_socket->SendProtobuf(packet_type, message);
    }
    UInt32 GetSessionIdx()
    {
        return m_session_idx;
    }

private:
    TripleS::TcpSocket* m_socket{ nullptr };
    std::string         m_id;
    UInt32              m_session_idx;
};