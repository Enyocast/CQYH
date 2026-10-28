#ifndef _B2M_MESSAGE_H_
#define _B2M_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
namespace InternalMessage
{
	enum B2M_MESSAGE_ID
	{
		b2m_begin = b2m_message_begin,

		b2m_register,
		b2m_ready,
		b2m_close_ack,

		b2m_end = b2m_message_end
	};

	struct B2M_REGISTER : MESSAGE_HEADER
	{
		UINT32  dwAddr;
		UINT16  wPort;
	};

	struct B2M_CLOSE_ACK : MESSAGE_HEADER
	{

	};

	struct B2M_READY : MESSAGE_HEADER
	{

	};

};
#pragma pack(pop)

#endif  // _B2M_MESSAGE_H_