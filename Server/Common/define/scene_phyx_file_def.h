#ifndef _SCENE_PHYX_FILE_DEF_H_
#define _SCENE_PHYX_FILE_DEF_H_

#include "string_def.h"
#include "scene_def.h"

#define SCENE_PHYX_FILE_EXT_NAME     "phx"
#define SCENE_PHYX_FILE_TAG          'phyx'
#define SCENE_PHYX_FILE_VERSION      (10)

#pragma warning(disable:4200)

struct SCENE_PHYX_HEADER
{
    UINT32    dwTag;        // File signature (fixed to 'phyx')
    UINT32    dwVersion;    // File version
    INT32     nMaxZoneX;    // Maximum number of scene zones along X
    INT32     nMaxZoneY;    // Maximum number of scene zones along Y
    UINT32    dwZoneCount;  // Total zone count
    char      szVolumnScript[MAX_VOLUME_COUNT][MAX_EMBEDDED_SCRIPT_LEN];    // Volume trigger scripts
    INT32     nMaxVolumeTriggerCount[MAX_VOLUME_COUNT];    // Maximum trigger count per volume
};


#endif  // _SCENE_PHYX_FILE_DEF_H_