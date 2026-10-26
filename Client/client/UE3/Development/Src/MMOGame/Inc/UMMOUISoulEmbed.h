//
//FItemBagPos _ToEmbedEquip;
//const static INT MAX_EmbedSoul = 3;
//FItemBagPos _ToEmbedSoul[MAX_EmbedSoul];
//
//TMap< INT, INT > _EmbedEquipPropSoulAdd;
//TMap< INT, INT > _EmbedEquipPropBase;
//TMap< INT, INT > _ToEmbeSoulPropAdd;
////
//UGFxObject *_ToEmbedEquipMc;
//UGFxObject *_EmbedSoulMc[MAX_EmbedSoul];
//UGFxObject *_OriginalPropTf;
//UGFxObject *_ResultPropTf;
//UGFxObject *_TotalSoulPropTf;

virtual void Init();
void InitSoulEmbedMc();
void InitSoulLevelUpMc();
virtual void PreOnShow(UBOOL show);
void GrayAllInBagNoNeed( UBOOL isToGray );
void GrayAllInBagNoNeedForSoulEmbed( UBOOL isToGray );
void GrayAllInBagNoNeedForSoulUnEmbed( UBOOL isToGray );
void GrayAllInBagNoNeedForSoulLevelUp( UBOOL isToGray );
UBOOL IsNeedToGrayOnSoulEmbed( UItem *pItemInBag, const FClientItemInfo *pItemInfo );
UBOOL IsNeedToGrayOnSoulUnEmbed( UItem *pItemInBag, const FClientItemInfo *pItemInfo );
UBOOL IsNeedToGrayOnSoulLvUp( UItem *pItemInBag, const FClientItemInfo *pItemInfo );
void OnNativeGameEvent( struct MMOGameEvent* evt );
UBOOL IsEquipPuttedInCanOp( INT containerID, INT slotID );
