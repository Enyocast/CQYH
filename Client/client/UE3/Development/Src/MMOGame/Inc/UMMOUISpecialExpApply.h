#ifndef _MMOUISPECIALEXPAPPLY_H_
#define _MMOUISPECIALEXPAPPLY_H_

virtual void Init();
void InitMc();
void OnNativeGameEvent( struct MMOGameEvent* evt );

virtual void PreOnShow(UBOOL show);

void UpdatePanel();
void UpdateFee();

void TryRechargeGameTime();
void TryToGetCurAllSpecialExp( INT accessableExp, INT totalExp );
void CloseAllPopupMsgBox();

#endif