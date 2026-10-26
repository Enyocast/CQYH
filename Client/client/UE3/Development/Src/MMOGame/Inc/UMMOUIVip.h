#ifndef _MMOUIVIP_H_
#define _MMOUIVIP_H_

virtual void Init();
void InitMc();
void OnNativeGameEvent( struct MMOGameEvent* evt );

virtual void PreOnShow(UBOOL show);

void InitBuyVipInfo();

void UpdatePanel();
void UpdateList();
void UpdateCurVipInfo();
void UpdateMyYuanBao();
#endif