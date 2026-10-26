#ifndef _MG2C_MESSAGE_H_
#define _MG2C_MESSAGE_H_

#include "external_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace ExternalMessage
{
	enum MG2C_MESSAGE_ID
	{
		m2c_message_begin = 900,


		m2c_message_end = 1000,
	};

};
// tolua_end
#pragma pack(pop)

#endif  // _MG2C_MESSAGE_H_
