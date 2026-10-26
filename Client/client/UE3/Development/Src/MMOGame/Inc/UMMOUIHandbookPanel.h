#ifndef _UMMOUIHANDBOOKPANEL_H_
#define _UMMOUIHANDBOOKPANEL_H_

virtual void Init();
virtual void UnInit();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateHandbookClass(UINT32 handbookClass);
void UpdateHandbookClassDefaultInfo(UINT32 handbookClass);
void UpdateHandbookList(UINT32 type, UINT32 defaultIndex = 0, const FString& keyWord = TEXT(""));
void UpdateHandbookAchievementInfo(UINT32 type);
void UpdateHandbookInfo(UINT32 type, UINT32 index);
int GetCurClass();
int GetCurType();
int GetCurIndex();
void SetUsableOnly(UBOOL usableOnly);
void SetLastHandbook(UINT32 handbookClass, UINT32 type, UINT32 index);
int GetLastClass();
int GetLastType();
int GetLastIndex();

void _UpdateMonsterInfo(UINT32 type, UINT32 index);
void _UpdateNpcInfo(UINT32 type, UINT32 index);
void _UpdateMapInfo(UINT32 type, UINT32 index);
void _UpdateComposeInfo(UINT32 type, UINT32 index);
void _UpdateStoneInfo(UINT32 type, UINT32 index);
void _UpdateStoryInfo(UINT32 type, UINT32 index);
void _UpdateSuitInfo(UINT32 type, UINT32 index);
void _UpdateEquipInfo(UINT32 type, UINT32 index);
void _UpdateRuneInfo(UINT32 type, UINT32 index);
void _UpdateSpiritInfo(UINT32 type, UINT32 index);

UINT32 _ConvertHandbookTypeToUiType(UINT32 type);
UINT32 _ConvertHandbookTypeToClass(UINT32 type);
UINT32 _ConvertHandbookTypeToSelectIndex(UINT32 type);

void RotatePlayer(int dir);
void RotateNpc(int dir);

#endif