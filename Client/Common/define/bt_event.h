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
    evtAIInit = evtAIBegin,         ///< activated only one time when AI initilize
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
    evtSceneInit = evtSceneBegin,      ///< activated only one time when Scene initilize
    evtEnterScene,                     ///< activated when role enter scene 
    evtLeaveScene,                     ///< activated when role leave scene
    evtTouchVolume,                    ///< activated when volume be trggered
                                       ///< @param Refer volume touched
    evtSingleNpcDie,                   ///< activated when single npc die
                                       ///< @param Refer single npc
    evtMediumGroupDie,                 ///< activated when npcs in the specified medium group all die
                                       ///< @param Refer medium group
    evtLargeGroupDie,                  ///< activated when npcs in the specified large group all die
                                       ///< @param Refer large group
    evtRoleInteract,                   ///< activated when role interact 
    evtRoleDie,                        ///< activated when role die
	evtBossDie,						   ///< activated when boss die
    evtGuildWarEnd,                       ///< guild war begin when ms notify
    evtSceneEnd,

    evtTotal = evtSceneEnd
};

extern char const* const g_BTEventName[evtTotal];

#endif  // _BT_EVENT_H_