#ifndef _ROBOT_MESSAGE_NOTIFIER_H_
#define _ROBOT_MESSAGE_NOTIFIER_H_

#include "irobot_message_notifier.h"

class CRobotMessageNotifier : public IRobotMessageNotifier
{
public:
    virtual BOOL SendToServer(UINT32 dwClientSessionID, PACKET_BUFFER* pData, UINT32 dwSize);
};

#endif  // _ROBOT_MESSAGE_NOTIFIER_H_