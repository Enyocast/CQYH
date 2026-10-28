#ifndef _MM2MG_MESSAGE_H_
#define _MM2MG_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
namespace InternalMessage
{
	enum MM2MG_MESSAGE_ID
	{
		mm2mg_begin = mm2mg_message_begin,

		mm2mg_register_ack,
		mm2mg_server_info,
		mm2mg_all_ready,

		mm2mg_end = mm2mg_message_end
	};

	struct MM2MG_REGISTER_ACK : MESSAGE_HEADER
	{
		UINT32 dwMGSessionID;
	};

	struct MM2MG_SERVER_INFO : MESSAGE_HEADER
	{
		UINT32	dwLSAddr;
		UINT16	wLSPort;
	};

	struct MM2MG_ALL_READY : MESSAGE_HEADER
	{

	};
};
#pragma pack(pop)

#endif  // _MM2MG_MESSAGE_H_