#ifndef __MESSAGE_HANDLER_COMBAT_H__
#define __MESSAGE_HANDLER_COMBAT_H__


public:
//void SendRequestUseAbility(INT SlotId);
//void Send_RequestUseAbility(UINT32 TargetId, UINT16 AbilityId, UINT8 Level, FVector& Point, UINT8 byRotateToTarget=TRUE);
void Send_RequestUseAbility_Ex(UINT32 TargetId, UINT16 SpellId, UINT8 Level, FVector& Point, UINT8 byRotateToTarget=TRUE, UINT SerialID=0);
void Send_RequestSwitchSpell(UINT16 SpellId);
void SendRequestCancelAbility(INT SpellId);
void SendRequestReviveAbility( UINT16 AbilityId ,UINT32 dwTargetID,FVector& Point);
void Send_SelectFocus(  INT ServeId);
void Send_Revive(UINT8 byType );
void Send_EquipSpell( INT SlotId,INT SpellId );
void Send_EquipRune( INT inSlot, INT inRuneSlot);
void Send_ActivateRune( INT inSpellId, INT inRuneSlot);
void Send_SpellLevelUp( UINT16 skillID );
void Send_StartNormalPractice( INT byType, INT wSpellID);
void Send_StartFastPractice( INT byType,INT wSpellID );
void Send_StopPractice( INT wSpellID );
void Send_SpeedUpFastPractice( INT byType, INT wSpellID );

private:
M_DECL_PARSE_FUN(g2c_char_precast_spell);
M_DECL_PARSE_FUN(g2c_char_prepare_spell);
M_DECL_PARSE_FUN(g2c_char_cast_spell);
M_DECL_PARSE_FUN(g2c_char_break_cast);
M_DECL_PARSE_FUN(g2c_role_cast_over);
M_DECL_PARSE_FUN(g2c_char_ex_cast_spell);
M_DECL_PARSE_FUN(g2c_char_spell_effect);
M_DECL_PARSE_FUN(g2c_equip_spell);
M_DECL_PARSE_FUN(g2c_sync_spell_slot);
M_DECL_PARSE_FUN(g2c_add_cooldown);

M_DECL_PARSE_FUN(g2c_sync_spell_pts);
M_DECL_PARSE_FUN(g2c_sync_spell_book);
M_DECL_PARSE_FUN(g2c_role_learn_spell);
M_DECL_PARSE_FUN(g2c_role_remove_spell);

M_DECL_PARSE_FUN(g2c_role_learn_item_spell);
M_DECL_PARSE_FUN(g2c_role_remove_item_spell);

M_DECL_PARSE_FUN(g2c_char_select_focus);
M_DECL_PARSE_FUN(g2c_focus_info);
//M_DECL_PARSE_FUN(g2c_focus_hifreq_sync);

M_DECL_PARSE_FUN(g2c_new_aura);
M_DECL_PARSE_FUN(g2c_aura_change);
M_DECL_PARSE_FUN(g2c_del_aura);
M_DECL_PARSE_FUN(g2c_char_freeze);
M_DECL_PARSE_FUN(g2c_char_client_show_time);
M_DECL_PARSE_FUN(g2c_char_hard);
M_DECL_PARSE_FUN(g2c_char_revive);
M_DECL_PARSE_FUN(g2c_revive_info);

M_DECL_PARSE_FUN(g2c_char_die);
M_DECL_PARSE_FUN(g2c_missile_appear);
M_DECL_PARSE_FUN(g2c_missile_move);
M_DECL_PARSE_FUN(g2c_sync_missile_list);

M_DECL_PARSE_FUN(g2c_enter_combat);
M_DECL_PARSE_FUN(g2c_leave_combat);
M_DECL_PARSE_FUN(g2c_sync_combo_kill);

M_DECL_PARSE_FUN(g2c_equip_rune);

M_DECL_PARSE_FUN(g2c_sync_pk_mode);
M_DECL_PARSE_FUN(g2c_sync_faction);
M_DECL_PARSE_FUN(g2c_aura_effect);
M_DECL_PARSE_FUN(g2c_sync_aura_list);
M_DECL_PARSE_FUN(g2c_sync_aura_brief);
M_DECL_PARSE_FUN(g2c_sync_pet_level);
M_DECL_PARSE_FUN(g2c_unlock_spell_slot);
M_DECL_PARSE_FUN(g2c_leech_soul);
M_DECL_PARSE_FUN(g2c_start_practice);
M_DECL_PARSE_FUN(g2c_stop_practice);
M_DECL_PARSE_FUN(g2c_spell_progress_change);
M_DECL_PARSE_FUN(g2c_spell_level_up);
M_DECL_PARSE_FUN(g2c_sync_ability_pts);
M_DECL_PARSE_FUN(g2c_directly_hp_change_effect);
M_DECL_PARSE_FUN(g2c_combat_pose_switch);



#define M_INIT_MSGHANDLER_COMBAT \
MREG_PARSE_FUN(g2c_char_precast_spell);\
MREG_PARSE_FUN(g2c_char_prepare_spell);\
MREG_PARSE_FUN(g2c_char_cast_spell);	 \
MREG_PARSE_FUN(g2c_char_ex_cast_spell);	\
MREG_PARSE_FUN(g2c_char_spell_effect);	\
MREG_PARSE_FUN(g2c_add_cooldown);	\
MREG_PARSE_FUN(g2c_char_break_cast); \
MREG_PARSE_FUN(g2c_role_cast_over);	\
MREG_PARSE_FUN(g2c_equip_spell); \
MREG_PARSE_FUN(g2c_sync_spell_slot); \
MREG_PARSE_FUN(g2c_char_select_focus);	\
MREG_PARSE_FUN(g2c_focus_info);	 \
MREG_PARSE_FUN(g2c_new_aura); \
MREG_PARSE_FUN(g2c_del_aura); \
MREG_PARSE_FUN(g2c_aura_change);\
MREG_PARSE_FUN(g2c_char_freeze);\
MREG_PARSE_FUN(g2c_char_client_show_time);\
MREG_PARSE_FUN(g2c_char_hard);	\
MREG_PARSE_FUN(g2c_char_revive); \
MREG_PARSE_FUN(g2c_revive_info)\
MREG_PARSE_FUN(g2c_char_die); \
MREG_PARSE_FUN(g2c_missile_appear);  \
MREG_PARSE_FUN(g2c_sync_missile_list);	\
MREG_PARSE_FUN(g2c_missile_move);	\
MREG_PARSE_FUN(g2c_enter_combat); \
MREG_PARSE_FUN(g2c_sync_pk_mode); \
MREG_PARSE_FUN(g2c_sync_faction); \
MREG_PARSE_FUN(g2c_leave_combat); \
MREG_PARSE_FUN(g2c_equip_rune);\
MREG_PARSE_FUN(g2c_aura_effect);\
MREG_PARSE_FUN(g2c_sync_aura_list);\
MREG_PARSE_FUN(g2c_sync_aura_brief);\
MREG_PARSE_FUN(g2c_sync_pet_level);\
MREG_PARSE_FUN(g2c_unlock_spell_slot);\
MREG_PARSE_FUN(g2c_leech_soul);\
MREG_PARSE_FUN(g2c_spell_level_up);\
MREG_PARSE_FUN(g2c_directly_hp_change_effect);\
MREG_PARSE_FUN(g2c_combat_pose_switch);\
MREG_PARSE_FUN(g2c_sync_combo_kill);
	







#endif
