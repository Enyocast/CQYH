#ifndef _UMMOUIASSISTPANEL_H_
#define _UMMOUIASSISTPANEL_H_

virtual void Init();
virtual void UnInit();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateAssistSkillData();

void UpdateAssistDropClassList();
void UpdateAssistDropList(UINT32 itemClass);

void UpdateAssistItemData();
void UpdateAssistItemList();

void UpdateAssistGameData();
void UpdateAssistDisplayData(class UGFxObject* object);
void UpdateAssistInputData(class UGFxObject* object, UBOOL mdfConfig, INT modfGCTType);
void ModifyAssistInputData(UBOOL mdfConfig, INT modfGCTType);
void ShowKeyWarning(UBOOL bShow);

void UpdateAssistHelp();

#endif