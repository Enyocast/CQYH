#ifndef _MG2MM_MESSAGE_H_
#define _MG2MM_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
	enum MG2MM_MESSAGE_ID
	{
		mg2mm_begin = mg2mm_message_begin,

		mg2mm_register,
		mg2mm_ready,
		mg2mm_close_ack,

		mg2mm_end = mg2mm_message_end
	};

	struct MG2MM_REGISTER : MESSAGE_HEADER
	{
		UINT8	byExternalCount;
		UINT32  dwExternalAddr[MAX_EXTERNAL_IP_COUNT];
		UINT16  wExternalPort[MAX_EXTERNAL_IP_COUNT];
	};

	struct MG2MM_READY : MESSAGE_HEADER
	{

	};

	struct MG2MM_CLOSE_ACK : MESSAGE_HEADER
	{

	};

};
// tolua_end
#pragma pack(pop)

#endif  // _MG2MM_MESSAGE_H_