#ifndef _o2g_MESSAGE_H_
#define _o2g_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
namespace InternalMessage
{
	enum O2G_MESSAGE_ID
	{
		o2g_begin = o2g_message_begin,

		o2g_register_ack,

		o2g_end = o2g_message_end
	};

	struct O2G_REGISTER_ACK : MESSAGE_HEADER
	{
	};
};
#pragma pack(pop)

#endif  // _o2g_MESSAGE_H_