#ifndef _M2B_MESSAGE_H_
#define _M2B_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
namespace InternalMessage
{
	enum M2B_MESSAGE_ID
	{
		m2b_begin = m2b_message_begin,

		m2b_register_ack,

		m2b_end = m2b_message_end
	};

	struct M2B_REGISTER_ACK : MESSAGE_HEADER
	{

	};
};
#pragma pack(pop)

#endif  // _M2B_MESSAGE_H_