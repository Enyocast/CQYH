
virtual void Init();
virtual void UnInit();

virtual void PostOnShow(UBOOL v);

class UGFxObject* CreateDisplayDetailOptionList();
void ApplyAdvanceSettingByUI(class UGFxObject* datList);
void InitSystemSettingToUI(class UGFxObject* dat,class FSystemSetting* pkSystem,INT nLevel);
void ApplyEffectLevelVideoData();