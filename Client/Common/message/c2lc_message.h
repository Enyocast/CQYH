#ifndef c2lc_message_h__
#define c2lc_message_h__


#include "external_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace ExternalMessage
{
	enum C2LC_MESSAGE_ID
	{
        c2lc_message_begin = 910,

		c2lc_group_state,

		c2lc_message_end = 920,
	};

    struct C2LC_GROUP_STATE : MESSAGE_HEADER
    {
		INT32	nAreaID;
		INT32	nGroupID;
    };
};

// tolua_end
#pragma pack(pop)

#endif // c2lc_message_h__
