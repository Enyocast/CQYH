#ifndef _EXTERNAL_MESSAGE_HEADER_
#define _EXTERNAL_MESSAGE_HEADER_

#include "common.h"

#pragma pack(push, 1)

#ifdef WIN32
    #pragma warning(disable:4200)
    #pragma warning(disable:4815)
#endif  // WIN32

// tolua_begin
#define EXTERNAL_MESSAGE_MAJOR_VERSION	(2)
#define EXTERNAL_MESSAGE_MINOR_VERSION	(2)

namespace ExternalMessage
{
    struct MESSAGE_HEADER
    {
        UINT16  wMsg;
    };

    struct FLEX_MESSAGE_HEADER : MESSAGE_HEADER
    {
        UINT16  wSize;
    };

    enum
    {
        max_message_count = 1024,
        flex_message_size = -1,
    };
};
// tolua_end
#pragma pack(pop)

#endif  // _EXTERNAL_MESSAGE_HEADER_