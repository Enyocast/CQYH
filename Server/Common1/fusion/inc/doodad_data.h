#ifndef _DOODAD_DATA_H_
#define _DOODAD_DATA_H_

#include "string_def.h"
#include "data_manager.h"

struct ADVENTURE_DATA;

struct DOODAD_DATA
{
    INT32                       nTemplateID;
    char                        szName[MAX_DOODAD_NAME_LEN];
	INT32						nLevel;
    INT32                       nType;
    INT32                       nSubType;
	INT32						nBodyType;
	INT32                       nOperateDuration;
    INT32                       nMinOpenCount;
    INT32                       nMaxOpenCount;

    INT32                       nRequireItemID;
    BOOL                        bCostItem;
    INT32                       nRequireVarID;
    INT32                       nRequireVarValue;

    INT32                       nSpawnNpcID;
    INT32                       nSpawnNpcChance;
    INT32                       nAuraID;

	INT32						nLifeFrm;

    char                        szScriptName[COMMON_NAME_LEN];

    const ADVENTURE_DATA*       pAdventureData;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, DOODAD_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // _DOODAD_DATA_H_
