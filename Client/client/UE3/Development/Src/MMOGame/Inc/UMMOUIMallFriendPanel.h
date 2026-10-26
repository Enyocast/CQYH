#ifndef _UMMOUIMALLFRIENDPANEL_H_
#define _UMMOUIMALLFRIENDPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);

public:
	void OnShowFriendPanel(INT nGoodsID, INT nNum);
	void ConfirmMallGiveFriendHint();
#endif