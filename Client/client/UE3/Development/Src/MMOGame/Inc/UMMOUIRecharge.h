#ifndef _MMOUIRECHARGE_H_
#define _MMOUIRECHARGE_H_

virtual void Init();
void InitMc();
void OnNativeGameEvent( struct MMOGameEvent* evt );

virtual void PreOnShow(UBOOL show);

void UpdatePanel();

void InitRechargeInfo();
void UpdateMyYuanBao();

void CloseAllPopUpPanel();
void NotifyRechargeResult( INT result );
#endif