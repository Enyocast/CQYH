#ifndef _M2MM_MESSAGE_H_
#define _M2MM_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
	enum M2MM_MESSAGE_ID
	{
		m2mm_begin = m2mm_message_begin,

		m2mm_register_ack,

		m2mm_end = m2mm_message_end
	};

	struct M2MM_REGISTER_ACK : MESSAGE_HEADER
	{

	};

};
// tolua_end
#pragma pack(pop)

#endif  // _M2MM_MESSAGE_H_