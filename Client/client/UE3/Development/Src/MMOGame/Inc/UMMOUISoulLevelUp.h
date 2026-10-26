//
//FItemBagPos _ToLvUpSoul;
//FItemBagPos _HelpLvUpSoulItem;
//const static INT MAX_SacrificeSoul = 5;
//FItemBagPos _SacrificeSoul[MAX_SacrificeSoul];
//
//TMap< INT, INT > _EmbedEquipPropSoulAdd;
//TMap< INT, INT > _EmbedEquipPropBase;
//TMap< INT, INT > _ToEmbeSoulPropAdd;
//
//UGFxObject *_ToLvUpSoulMc;
//UGFxObject *_SacrificeSoulMc[MAX_SacrificeSoul];
//UGFxObject *_SuccessRitoTf;
//UGFxObject *_CurLevelSoulPropTf;
//UGFxObject *_NextLevelSoulPropTf;

virtual void Init();
void InitSoulLevelUpMc();
virtual void PreOnShow(UBOOL show);
void OnNativeGameEvent( struct MMOGameEvent* evt );