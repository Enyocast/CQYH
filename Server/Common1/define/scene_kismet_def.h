#ifndef _SCENE_KISMET_DEF_H_
#define _SCENE_KISMET_DEF_H_

enum KISMET_OBJECT_TYPE
{
    kotSequenceBegin = 0,
	kotSequenceObject = kotSequenceBegin,
	kotSequence,
	kotDataMember,
	kotDataMemberVarLink,
	kotSequenceOp,
	kotSequenceCondition,
	kotSequenceEvent,
	kotSequenceAction,
	kotSequenceVariable,
	kotSequenceVariableInt,
	kotSequenceVariableBool,
	kotSequenceVariableObject,
	kotSequenceVariableTable,
    kotSequenceEnd,

    kotEventBegin,
	kotSeqEvent_PlayerTouchVolume = kotEventBegin,
	kotSeqEvent_NPCGroupDie,
    kotSeqEvent_NpcDie,
    kotSeqEvent_Door,
	kotSeqEvent_BTEvent,
    kotEventEnd,

    kotActionBegin,
	kotSeqAct_ActiveSpawnGroup = kotActionBegin,    // 0:Spawn
    kotSeqAct_SpawnSingleNpc,                       // 0:Spawn
    kotSeqAct_Door,                                 // 0:Open, 1:Close, 2:Toggle
	kotSeqAct_BTNode,								// refer to 
    kotActionEnd,

    kotObjectBegin,
    kotSpawnGroup = kotObjectBegin,
	kotTriggerVolume,
    kotSingleNpc,
    kotDoor,
    kotObjectEnd,
};

enum KIS_EVENT_POINT
{
    kepInvalid = -1,
    kepBegin = 0,

    // kotSeqEvent_PlayerTouchVolume
    kepTouchVolumn = kepBegin,
    kepUntouchVolumn,

    // kotSeqEvent_NPCGroupDie
    keAllDead = kepBegin,

    // kotSeqEvent_NpcDie
    keNpcDie = kepBegin,

    // kotSeqEvent_Door
    keDoorOpen = kepBegin,
    keDoorClose,
    keDoorToggle,
};


#endif  // _SCENE_SPAWN_DEF_H_
