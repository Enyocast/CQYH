#ifndef ns_message_h__
#define ns_message_h__

#include "internal_message_header.h"

#define NS_MESSAGE_VERSION	(1)

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
	enum NS_MESSAGE_ID
	{
		ns_begin = ns_message_begin,

		// in msg
		x2n_new_name,

		// out msg
		n2x_new_name_result,

		x2n_message_version,

		ns_end = ns_message_end
	};

	struct X2N_MESSAGE_VERSION : MESSAGE_HEADER
	{
		UINT8	byVersion;
	};

	struct X2N_NEW_NAME : MESSAGE_HEADER
	{
		UINT8	byType;
		UINT32	dwSessionID;
		char	szName[COMMON_NAME_LEN];
        char    UserData[USER_DATA_LEN];
	};

	struct N2X_NEW_NAME_RESULT : MESSAGE_HEADER
	{
		UINT32	dwSessionID;
		INT32	nErrorCode;
		UINT8	byType;
		UINT32	dwID;
		char	szName[COMMON_NAME_LEN];
        char    UserData[USER_DATA_LEN];
	};
};

// tolua_end

#pragma pack(pop)

#endif // ns_message_h__
