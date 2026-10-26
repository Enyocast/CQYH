#ifndef _NET_EVENT_MSG_H_
#define _NET_EVENT_MSG_H_

// tolua_begin
namespace ExternalMessage
{
    enum 
    {
        b2c_robot_connected     = 0xFFFD,
        t2c_robot_connected     = 0xFFFE,
        t2c_robot_disconnected  = 0xFFFF
    };

    struct T2C_ROBOT_CONNECTED
    {
    };

    struct T2C_ROBOT_DISCONNECTED
    {
    };
    struct B2C_ROBOT_CONNECTED
    {
    };

};

// tolua_end

#endif  // _NET_EVENT_MSG_H_