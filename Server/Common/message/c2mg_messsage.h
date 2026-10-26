#ifndef _C2MG_MESSAGE_H_
#define _C2MG_MESSAGE_H_

#include "external_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace ExternalMessage
{
	enum C2MG_MESSAGE_ID
	{
		c2mg_message_id = 900,

		c2mg_message,

		c2mg_message_end = 910,
	};

	struct C2MG_MESSAGE : FLEX_MESSAGE_HEADER
	{
		char szMessage[0];
	};
}
// tolua_end
#pragma pack(pop)

#endif  // _C2MG_MESSAGE_H_
