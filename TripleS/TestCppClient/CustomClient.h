#ifndef _HEADER_CUSTOM_CLIENT_
#define _HEADER_CUSTOM_CLIENT_

/***************************************************************************************************
**  Name : CustomClient
**  Auth : �ӻ��
**  Date : 2014-5-22
**  Desc : TcpClient�� ��ӹ޾� ���� ��� ������ �����Ѵ�.
**         Custom For Echo
****************************************************************************************************
**  Todo : 
****************************************************************************************************
**  Author:         Date:               Description:
**  -----------     ----------------    ------------------------------------------------------------
**  �ӻ��          2014-5-22           ���� ����
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