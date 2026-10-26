#ifndef _CER_MESSAGE_H_
#define _CER_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
    enum CER_MESSAGE_ID
    {
        cer_begin = cer_message_begin,

        cer_sync_certification,

        cer_end = cer_message_end
    };

    struct CER_SYNC_CERTIFICATION : MESSAGE_HEADER
    {
        UINT8 byKey;
        char szMathTable[0];
    };

};
// tolua_end
#pragma pack(pop)

#endif  // _CER_MESSAGE_H_