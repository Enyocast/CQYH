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
    UINT32                  dwTag;
    UINT32                  dwVersion;
    INT32                   nMaxZoneX;
    INT32                   nMaxZoneY;
    UINT32                  dwZoneCount;
    char                    szVolumnScript[MAX_VOLUME_COUNT][MAX_EMBEDDED_SCRIPT_LEN];
    INT32                   nMaxVolumeTriggerCount[MAX_VOLUME_COUNT];
};


#endif  // _SCENE_PHYX_FILE_DEF_H_