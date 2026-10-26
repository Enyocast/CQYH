#ifndef _MS_SCENE_DATA_H_
#define _MS_SCENE_DATA_H_

#include "string_def.h"
#include "scene_def.h"
#include "data_manager.h"

struct MS_SCENE_DATA
{
	INT32	nSceneID;
    INT32   nLevel;
	INT32	nType;
    INT32   nMinPlayerLevel;
    INT32   nMaxPlayerLevel;
	TCHAR	szConfigName[PATH_LEN];
    INT32   nInitLineCount;
	INT32	nMaxRoleCount;

	INT32	nSideCount;
	INT32	nBattleType;
	INT32	nMinRoleLimitPerSide;
	INT32	nMaxRoleLimitPerSide;

	static BOOL HasName(void)	{ return FALSE; }

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, MS_SCENE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif	// _MS_SCENE_DATA_H_