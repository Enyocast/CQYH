#ifndef _UMMOUIMALLPANEL_H_
#define _UMMOUIMALLPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);

public:
	void UpdateMallGoodsPanel();
	void UpdateMallHomePanel();

	void UpdateMallHomeHotList();
	void UpdateMallHomeShowList();
	void UpdateGoldMoney(INT nMoney);
	void UpdateNoticeBuy();
	void AddNewNotice(const FString& str);

	void SetGoodsItemIcon(UItem* pkItem,INT nIndex,INT nNum);
	void SetHotItemIcon(UItem* pkItem,INT nIndex,INT nNum);

	INT  GetCurGoodsID();

#endif