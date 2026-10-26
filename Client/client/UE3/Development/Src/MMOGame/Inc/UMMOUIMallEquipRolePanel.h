#ifndef _UMMOUIMALLEQUIPROLEPANEL_H_
#define _UMMOUIMALLEQUIPROLEPANEL_H_

virtual void Init();
virtual void UnInit();
virtual void PostOnShow(UBOOL v);

public:
	void OnShowMallEquipPanel(INT nGoodsID);
	void OnUpdateTurn(BYTE turn);
	void OnUpdateRoleEquip(INT nGoodsID);
#endif