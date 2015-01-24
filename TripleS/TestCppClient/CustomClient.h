#ifndef _HEADER_CUSTOM_CLIENT_
#define _HEADER_CUSTOM_CLIENT_

/***************************************************************************************************
**  Name : CustomClient
**  Auth : 임상수
**  Date : 2014-5-22
**  Desc : TcpClient를 상속받아 실제 통신 내용을 정의한다.
**         Custom For Echo
****************************************************************************************************
**  Todo : 
****************************************************************************************************
**  Author:         Date:               Description:
**  -----------     ----------------    ------------------------------------------------------------
**  임상수          2014-5-22           파일 생성
***************************************************************************************************/

#include "TcpClient.h"

class CustomClient : public TcpClient
{
public:
    CustomClient(void);
    ~CustomClient(void);

private:
    virtual void _Working(SOCKET client_sock);
};

#endif //_HEADER_CUSTOM_CLIENT_