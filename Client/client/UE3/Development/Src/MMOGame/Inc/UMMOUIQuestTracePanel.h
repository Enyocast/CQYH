#ifndef _UMMOUIQUESTTRACEPANEL_H_
#define _UMMOUIQUESTTRACEPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

public:
	void UpdatePosition();
	void UpdateQuestTraceList();
	void AddAcceptedQuest(INT questId);
	void RemoveAcceptedQuest(INT questId);
	void UpdateAcceptedQuest(INT questId);
	void UpdateAcceptedQuestTraceList();
	void UpdateAvailableQuestTraceList();

#endif