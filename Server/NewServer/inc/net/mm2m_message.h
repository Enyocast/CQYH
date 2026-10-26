#ifndef _MM2M_MESSAGE_H_
#define _MM2M_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
	enum MM2M_MESSAGE_ID
	{
		mm2m_begin = mm2m_message_begin,
		
		mm2m_register,
		mm2m_ready,
		mm2m_close_ack,
		
		mm2m_end = mm2m_message_end
	};

	struct MM2M_REGISTER : MESSAGE_HEADER
	{
		DWORD			dwAddr;
		WORD			wPort;
	};

	struct MM2M_READY : MESSAGE_HEADER
	{

	};

	struct MM2M_CLOSE_ACK : MESSAGE_HEADER
	{

	};

};
// tolua_end
#pragma pack(pop)

#endif  // _MM2M_MESSAGE_H_