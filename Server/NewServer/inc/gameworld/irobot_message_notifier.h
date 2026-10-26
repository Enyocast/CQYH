#ifndef _IROBOT_MESSAGE_NOTIFIER_H_
#define _IROBOT_MESSAGE_NOTIFIER_H_

class CUser;
struct lua_State;

#include "net.h"

class IRobotMessageNotifier
{
public:
    virtual BOOL SendToServer(UINT32 dwClientSessionID, PACKET_BUFFER* pData, UINT32 dwSize) = 0;
};

#endif  // _IROBOT_MESSAGE_NOTIFIER_H_