#ifndef _UMMOUIQUESTSTORYPANEL_H_
#define _UMMOUIQUESTSTORYPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

public:
	void UpdateCurQuestInfo(int questId);
	void UpdateQuestChapterList();
	void UpdateQuestStageList(UINT32 chapter);
	void UpdateQuestStageInfo(UINT32 chapter, UINT32 stage);
	
#endif