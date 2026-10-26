#ifndef _O2M_MESSAGE_H_
#define _O2M_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
	enum O2M_MESSAGE_ID
	{
		o2m_begin = o2m_message_begin,

		o2m_register,
		o2m_ready,
		o2m_close_ack,

		o2m_end = o2m_message_end
	};

	struct O2M_REGISTER : MESSAGE_HEADER
	{
		UINT32  dwAddr;
		UINT16  wPort;
	};

	struct O2M_CLOSE_ACK : MESSAGE_HEADER
	{

	};

	struct O2M_READY : MESSAGE_HEADER
	{

	};

};
// tolua_end
#pragma pack(pop)

#endif  // _O2M_MESSAGE_H_