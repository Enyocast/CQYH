#ifndef _UMMOUIQUESTPANEL_H_
#define _UMMOUIQUESTPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

public:
	void UpdateQuestList();
	void UpdateQuestDetail();

protected:
	void _UpdateQuestSubListByMap(UINT32 mapId, UGFxObject* questArray, INT& index);
	void _UpdateQuestSubListByType(EQUEST_TYPE questType, UGFxObject* questArray, INT& index);
	
#endif