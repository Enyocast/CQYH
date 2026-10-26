virtual void Init();
virtual void UnInit();

void CloseAllPopUpPanel();

void TryPopupQuest(INT newCompleteQuestID);

// add by zhangrui05@snda.com
void TryPopupQuestWithoutNpc(INT questId);
void TryPopupQuestOver(INT questId);
void PlayDialogNpcSound(UBOOL bClose);

//直接升级装备的武器
void ConfirmLeveUpWeaponCurrentEquipped();
void ConfirmLeveUpWeaponHighLevel( UBOOL isMessageBoxCall = FALSE );
void ConfirmTakeBackCurLeveUpWeaponRtNow();

virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
virtual void SetVisible(UBOOL bValue = TRUE);
