#pragma once

#include <map>
#include "User.h"
#include "AutoLock.h"

class UserManager
{
public:
    void AddUser(TripleS::TcpSocket* socket, UInt32 session_idx = 0)
    {
        TripleS::AutoLock auto_lock(&m_user_manager_lock);

        static UInt32 session_idx = 0;
        auto cur_iter = m_users.find(session_idx);
        if (cur_iter == m_users.end())
        {
            User user;
            socket->SetSessionIdx(++session_idx);
            user.SetSocket(socket);
            m_users.insert(std::make_pair(session_idx, user));
        }
        else
        {
            // 실제에서는 RECONNECT시에 재인증을 해야한다
            cur_iter->second.SetSocket(socket);
        }
    }

    void DelUser(const UInt32 session_idx)
    {
        TripleS::AutoLock auto_lock(&m_user_manager_lock);

        m_users.erase(session_idx);
    }

private:
    TripleS::Lock m_user_manager_lock;
    std::map<UInt32, User> m_users;
};