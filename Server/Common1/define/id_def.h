#ifndef _ID_DEF_H_
#define _ID_DEF_H_

/// @file id_def.h
/// lua package file id_def.pkg

// tolua_begin

#define INVALID_OBJECT_ID	(0)             ///< @line
#define OBJECT_TYPE_MASK    (0xF0000000)
#define OBJECT_ID_MASK      (0x0FFFFFFF)
#define MAX_OBJECT_ID       (0x0FFFFFFF)

/// @enum OBJECT_TYPE
enum OBJECT_TYPE
{
	otInvalid = -1,

	otRole,             ///< @line
	otNpc,              ///< @line
	otHero,             ///< @line
	otDoodad,           ///< @line
	otMissile,          ///< @line
	otDrop,             ///< @line
	otGuild,            ///< @line
    otTeam,             ///< @line
	otBattleTeam,       ///< @line
    otChannel,          ///< @line
	otTrumpet,

	otTotal
};

inline UINT32 MakeObjectID(UINT32 dwType, UINT32 dwIndex)
{
	return ((dwIndex & OBJECT_ID_MASK) | (dwType << 28));
}

inline INT32 GetTypeFromID(UINT32 dwObjID)
{
    return (dwObjID >> 28);
}

inline INT32 GetIndexFromID(UINT32 dwObjID)
{
    return (dwObjID & OBJECT_ID_MASK);
}

// tolua_end

inline UINT64 MakeSceneObjID(INT16 nSceneTempID, INT32 nSceneID)
{
	UINT64 nResultSceneID = 0;
	nResultSceneID = (((UINT64)nSceneTempID) << 32) | nSceneID;

	return nResultSceneID;
}

//#define MAKE_SCENE_OBJ_ID(__group_id__, __scene_template_id__, __scene_id__)  ((__group_id__ << 56) | (__scene_template_id__ << 32) | (__scene_id__))

#endif	// _ID_DEF_H_