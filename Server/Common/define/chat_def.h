#ifndef _CHAT_DEF_H_
#define _CHAT_DEF_H_

#include "id_def.h"
#include "scene_def.h"

/// @file chat_def.h
/// lua package file chat_def.pkg

#define MAX_CHAT_MESSAGE_LEN	(256)
#define CHAT_SYSTEM_ID          (0)

/// @enum CHAT_CHANNEL_TYPE 
enum CHAT_CHANNEL_TYPE
{
	cctInvalid = otChannel << 28,

    cctScreen,                  ///< screen channel 90000001
	cctScene,                   ///< scene channel  90000002
    cctGroup,                   ///< group channel  90000003
	cctServer,	                ///< server channel (including several groups) 90000004

	cctTotal
};

enum CHAT_LOCATION_TYPE
{
	cltInvalid,

	cltNormal,		// Yellow system text in the chat window
	cltLighting,	// Scrolling announcement
	cltTvShow,		// Yellow text centered at the top of the screen
	cltUrl,			// Yellow system text in the chat window
	cltDialog,      // Yellow system text in the chat window
	cltTrumpet,		// Trumpet item
	cltGMTrumpet,   // Yellow system text in the chat window

	cltTotal,
};

#endif  //_CHAT_DEF_H_