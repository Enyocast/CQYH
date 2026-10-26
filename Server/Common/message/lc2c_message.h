#ifndef lc2c_message_h__
#define lc2c_message_h__


#include "external_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace ExternalMessage
{
	enum LC2C_MESSAGE_ID
	{
        lc2c_message_begin = 1024,

		lc2c_server_state,
		lc2c_group_state,

		lc2c_message_end = 2000,
	};

	struct LC_SERVER_STATE
	{
		UINT8	byAreaID;
		UINT8	byState;
	};

    struct LC2C_SERVER_STATE : FLEX_MESSAGE_HEADER
    {
		char	LCServerState[0];
    };

	struct LC2C_GROUP_STATE : MESSAGE_HEADER
	{
		UINT8	byAreaID;
		UINT8	byGroupID;
		UINT8	byOpen;
		INT32	nPlayerCount;
		INT32	nMaxPlayerCount;
	};
};

// tolua_end
#pragma pack(pop)

#endif // lc2c_message_h__
