#ifndef _B2C_MESSAGE_H_
#define _B2C_MESSAGE_H_

#include "external_message_header.h"

#pragma pack(push, 1)
namespace ExternalMessage
{
	enum B2C_MESSAGE_ID
	{
		b2c_message_begin = 0,

		b2c_query_gate_ack,

		b2c_message_end = 8,
	};

	struct B2C_QUERY_GATE_ACK : MESSAGE_HEADER
	{
		UINT32				dwAddr;
		UINT16              wPort;
		//char                  yuming[20];
	};

};
#pragma pack(pop)

#endif  // _C2B_MESSAGE_H_