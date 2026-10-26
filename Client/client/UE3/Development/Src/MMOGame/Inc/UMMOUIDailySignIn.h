#ifndef _MMOUIDAILYSIGNIN_H_
#define _MMOUIDAILYSIGNIN_H_

virtual void Init();
void InitMc();
void OnNativeGameEvent( struct MMOGameEvent* evt );

virtual void PreOnShow(UBOOL show);

void UpdatePanel();
void InitDailySignInRewards();

void NotifyGetDailySignInRewardResult( INT signInDay );
#endif