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
    UINT32    dwTag;        // 文件标识（固定为'phyx'）
    UINT32    dwVersion;    // 文件版本号
    INT32     nMaxZoneX;    // 场景X方向最大区域数
    INT32     nMaxZoneY;    // 场景Y方向最大区域数
    UINT32    dwZoneCount;  // 总区域数量
    char      szVolumnScript[MAX_VOLUME_COUNT][MAX_EMBEDDED_SCRIPT_LEN];    // 体积触发脚本
    INT32     nMaxVolumeTriggerCount[MAX_VOLUME_COUNT];    // 最大体积触发次数
};


#endif  // _SCENE_PHYX_FILE_DEF_H_