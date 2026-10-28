#ifndef _CHAT_DEF_H_
#define _CHAT_DEF_H_

#include "id_def.h"
#include "scene_def.h"

/// @file chat_def.h
/// lua package file chat_def.pkg

#define MAX_CHAT_MESSAGE_LEN	(512)
#define CHAT_SYSTEM_ID          (0)

/// @enum CHAT_CHANNEL_TYPE 
enum CHAT_CHANNEL_TYPE
{
	cctInvalid = otChannel << 28,

    cctScreen,                  ///< screen channel
	cctScene,                   ///< scene channel
    cctGroup,                   ///< group channel
	cctServer,	                ///< server channel (including several groups)

	cctTotal
};

enum CHAT_LOCATION_TYPE
{
	cltInvalid,

	cltNormal,
	cltLighting,
	cltTvShow,
	cltUrl,
	cltDialog,
	cltTrumpet,		//喇叭道具
	cltGMTrumpet,

	cltTotal,
};

#endif  //_CHAT_DEF_H_