#ifndef _BT_EVENT_H_
#define _BT_EVENT_H_

/// @file bt_event.h 
/// @brief Behavior Tree Event List

#define LOAD_BEHAVIOR_TREE      "load_behavior_tree"

enum BT_EVENT_TYPE
{
    evtInvalid,

    /************************************************************************/
    /* AI                                                                   */
    /************************************************************************/
    evtAIBegin,
    
	evtAIInit = evtAIBegin,         ///< activated only one time when AI initializing
    evtAIIdle,                      ///< activated in every frame when AI in idle state
    evtAIFight,                     ///< activated in every frame when AI in fight state
    evtAIDie,                       ///< activated when AI owner die
    evtAIRevive,                    ///< activated when AI owner revive
    evtAIInteract,                  ///< activated when AI owner be set to interact with role
    
	evtAIEnd,


    /************************************************************************/
    /* Scene                                                                */
    /************************************************************************/
    evtSceneBegin,

    evtSceneInit = evtSceneBegin,		///< activated only one time when scene initializing
    evtEnterScene,						///< activated when role enter scene 
    evtLeaveScene,						///< activated when role leave scene
    evtTouchVolume,						///< activated when volume be triggered
										///< @param Refer volume touched
	evtSingleNpcDie,					///< activated when single npc die
										///< @param Refer single npc
	evtMediumGroupDie,					///< activated when npc in the specified medium group all die
										///< @param Refer medium group
	evtLargeGroupDie,					///< activated when npc in the specified large group all die
										///< @param Refer large group
	evtRoleInteract,					///< activated when role interact 
	evtRoleDie,							///< activated when role die
	evtBossDie,							///< activated when boss die
    evtGuildWarBegin,                   ///< activated when guild war begin
    evtGuildWarEnd,						///< activated when guild war end

	evtSabacBeforeStart,				///< activated before sabac start 10 min
	evtSabacStart,						///< activated when sabac start
	evtSabacOccupied,					///< activated when sabac occupied
	evtSabacBeforeEnd,					///< activated before sabac end 10 min
	evtSabacEnd,						///< activated when sabac end

    evtGuildBuildingUpdate,             ///< activated when replace guild building npc
                                        ///< @param refer scene variable
    evtGuildBuildingUpgrade,            ///< activated when guild building upgrade
                                        ///< @param refer scene variable
    evtGuildBuildingDel,                ///< activated when guild building be deleted
                                        ///< @param refer scene variable

	evtSceneEnd,

    evtTotal = evtSceneEnd
};

extern char const* const g_BTEventName[evtTotal];

#endif  // _BT_EVENT_H_