
virtual void Init();
virtual void UnInit();

virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

//===============================
void RefreshSkillBar();

//===============================
//根据职业设置技能栏形态
void UpdateCurBarShowType();

void RefreshLoopEffict();
void UpdateBloodTextVisible();

//===============================
void CheckSlotEnableState( INT slotIdx, UBOOL isForceCheck = FALSE );

void UpdateItemEnableState();
void CheckItemEnableState( INT slotIdx, UBOOL isForceCheck = FALSE );

void UpdateAbilityEnableState();
void CheckAbilityEnableState( INT slotIdx, UBOOL isForceCheck = FALSE );
void CoverAllSlotUpdateTypeAndUpdate();

//===============================
void InitMc();
void InitItemBarItemForNewComing();

//===============================
void ClearAllSkillSlotData();
void ClearSkillListPanel();

//===============================
void HintForDraggingSkill( UMMOAbility *dragSkill );
void CloseHintForDraggingSkill();
void HintForDraggingItem( INT fromSlotPanelType, INT itemSlotID );
void CloseHintForDraggingItem();
void CloseHintForAllDragging();

//===============================
void ResetAllSkillSlots();
void UpdateSkillSlot( INT slotCmdKey );

void UpdateItemSlotForItemDeleted( INT itemTemplateID );
void ResetAllItemsByIDs();
void OnItemSwapped( INT srcConIdx, INT srcSlotIdx, INT dstConIdx, INT dstSlotIdx );
//===============================
void SwapBarSlotData( INT slotIdx1, INT slotIdx2 );
UBOOL SetBarSlot( INT slotIdx, SkillBarSlotType slotType, INT templeteID );

UBOOL SetBarSlotToNoData( INT slotIdx, UBOOL isInitialize = FALSE );
UBOOL SetBarSlotToSkillData( INT slotIdx, UINT uniqueSkillID );
UBOOL SetBarSlotToItemData( INT slotIdx, INT itemPosID );
UBOOL SetBarSlotToMountData( INT slotIdx, INT mountID );

void ClearAllSlotOfItem( INT itemTemplateID );
void ClearAllSlotOfSkill( INT uniqueSkillID, INT exceptSlotIdx = -1 );

//===============================
class UMMOAbility *GetSkillBarSlotSkill( INT slotIdx );
void SetSlotDisableState( INT &slotState, INT type, UBOOL isToSet );

UBOOL IsSlotUpdateType( INT type );
void SetSlotUpdateType( INT type );
void UnsetSlotUpdateType( INT type );
void ResetSlotUpdateType();
void SetAllSlotUpdateType();

//===============================
UBOOL DoSlotAction( INT slotIdx, UBOOL isReleased );
void InitSkillBarSlotHotKey();

//===============================
UBOOL TryToEquipOnSkill( INT toSetBarSlotIdx, INT uniqueSkillID );
UBOOL UnequipSkill( INT uniqueSkillID, INT exceptIdx = -1 );
UBOOL UnequipAllSkills( INT skillID, UBOOL isClient = FALSE );

void MarkSlotDirty( INT idx );
void ClearnSlotDirty( INT idx );
UBOOL IsSlotDirty( INT idx );
void SwapBarSlotDataRaw( INT slotIdx1, INT slotIdx2 );

void RefreshSkillBarByServerData( INT32* addr, INT size );
void Send_BarSlotData();

//===============================
void SetAbilityCDInSlot( INT slotCmdKey, INT abilityTemplateID, INT leftMiniSec, INT maxMiniSec );
void UpdateAbilityCDInSlot( UMMOAbility* inAbility, INT forceUpdateSlotCmdKey = -1 );

void SetItemCDInSlot( INT slotIdx );
void UpdateAllItemSlotCDByItemUse( INT type, INT cdID );

//===============================
void CheckSlotLoopEffect( INT slotIdx );
void StopAllLoopEffect( INT slotIdx );

void RefreshAllSkillSlotLoopEffect( INT certainSkillID );

//===============================
INT GetSkillBarSlotIdx( INT eCommandKey );
ECommandKey GetSkillBarSlotCmdKey( INT slotIdx );

FSlotContainer &SkillBarSlotData( INT idx );

INT GetSkillBarSlotDisableState( INT idx );
void SetSkillBarSlotDisableState( INT idx, INT toSetState );

UGFxObject *SkillBarSlotMc( INT idx );

//===============================
INT GetPlayerExp_Extra();
UMaterialInstance* GetMPBallMaterila() const;

void SendOpenPack(INT itemId);