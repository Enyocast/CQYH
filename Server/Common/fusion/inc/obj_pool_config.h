#ifndef _OBJ_POOL_CONFIG_H_
#define _OBJ_POOL_CONFIG_H_

// tolua_begin
#pragma pack(push, 8)

struct OBJ_POOL_CONFIG
{
    INT32	    nSceneCount;
    INT32	    nRegionCount;

    INT32	    nRoleCount;
    INT32	    nNpcCount;
    INT32	    nDoodadCount;

    INT32	    nMissileCount;
    INT32	    nSpellInstanceCount;
    INT32       nSpellSetCount;
    INT32	    nAuraInstanceCount;
    INT32	    nBulletCount;
    INT32	    nRuneCount;
    INT32       nExtraModifierNodeCount;
    INT32       nThreadNodeCount;
    INT32       nBTCtxCount;
    INT32       nBTNodeCount;
    INT32       nAITemplateCount;
	INT32		nBlockCount;

    INT32       nVolumeCount;
    INT32       nDropCount;
    INT32       nTeamCount;
    INT32       nArenaTeamCount;
    INT32       nItemCount;
    INT32       nSignalCount;

    INT32       nMasterTeacherPoolCount;
    INT32       nMasterStudentPoolCount;
};

extern OBJ_POOL_CONFIG g_ObjPoolConfig;

#pragma pack(pop)
// tolua_end

#endif  // _OBJ_POOL_CONFIG_H_