
//#include "MMOPlayerInfoManager.h"

virtual void Init();
//virtual void UnInit();

virtual void PostOnShow(UBOOL v);

void InitPlayerRoleId( INT roleId );
void UpdatePlayerInfo();
void UpdateEquipInfo();
void UpdateBaseInfo();
void UpdateSpellInfo();
void UpdateRefineInfo();
void UpdateSpriteInfo();
void UpdateHeavenBloodPanel();
void InitRecover();

UMMOAbility* FindLearnedSkill( TArray<UMMOAbility*>& skillList , INT skillId );

virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
