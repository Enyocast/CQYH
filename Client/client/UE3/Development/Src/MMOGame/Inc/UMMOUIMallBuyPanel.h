#ifndef _UMMOUIMALLBUYPANEL_H_
#define _UMMOUIMALLBUYPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);

public:
	void OnShowMallBuyPanel(INT nGoodsID);
	void ConfirmMallBuyHint();
	INT	 GetGoodsNum();
#endif