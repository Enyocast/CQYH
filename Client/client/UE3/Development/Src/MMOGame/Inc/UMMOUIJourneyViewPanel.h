#ifndef _UMMOUIJOURNEYVIEWPANEL_H_
#define _UMMOUIJOURNEYVIEWPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

public:
	void UpdateJourneyList();
	void UpdateJourneyInfo(INT journeyId);
	void SetCurJourneyId(INT journeyId);

protected:
	void _AddAwardObject(UGFxObject* arrayRewards, INT itemId, INT itemCount, INT& index);
#endif