#ifndef _NPC_DEF_H_
#define _NPC_DEF_H_

/// @file npc_def.h
/// lua package file npc_def.pkg

// tolua_begin

#define MAX_NPC_ID              (10000)
#define MAX_NPC_FORCE_ID		(64)
#define INVALID_FORCE_ID		(-1)

#define MAX_NPC_LEVEL           (60)
#define MIN_NPC_RADIUS			(64)
#define MAX_LEVEL_DIFF          (15)

#define MAX_PET_LEVEL           (7)
#define CASTER_WASHOUT_TIME    (30)        // √Î
#define TARGET_WASHOUT_TIME    (6)         // √Î


enum NPC_STATE
{
	npcInvalid = 0,

	npcSpawn,
	npcAlive,
	npcCorpse,
	npcRespawn,
	npcRevive,

	npcTotal
};

/// @enum NPC_QUALITY
enum NPC_QUALITY
{
	nqInvalid,

	nqNormal1,        	///< 1, @line
	nqNormal2,        	///< 2, @line
	nqNormal3,        	///< 3, @line
	nqNormal4,        	///< 4, @line
	nqNormal5,        	///< 5, @line
	nqElite,			///< 6, @line
	nqRare,				///< 7, @line
	nqBoss,				///< 8, @line

	nqTotal,
};

enum NPC_TRANSFORM_STATE
{
	npctInvalid = 0,
	npctNpc,
	npctPet,

	npctTotal,
};

/// @enum PET_TYPE
enum PET_TYPE
{
	petInvalid,



	petTotal
};

enum PET_BORN_TYPE
{
	petBornInvalid,

	petBornHoly,
	petBornSkeleton,
	petBornByMage,

	petBornTotal,
};

/// @enum PET_STATE
enum PET_STATE
{
	psInvalid,
	psIdle,
	psFight,
	psTotal
};


enum PET_AI_VARIABLES
{
	PET_AIV_MAGE_PET_SPELL_ID = 0,
    PET_AIV_FIGHT_STATE_INDEX = 1,
	PET_AI_CONTROL = 3,
    PET_AI_IS_EXTRA_WALK = 4,
    PET_AI_MAGE_CHASE_THRESHOLD = 5,
    PET_AI_MAGE_PREFER_DISTANCE = 6,
    PET_AI_GO_HOME = 7,
};

// tolua_end

#endif  // _NPC_DEF_H_