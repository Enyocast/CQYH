#ifndef _UMMOUIHELPERPLAYERPANEL_H_
#define _UMMOUIHELPERPLAYERPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);

void ShowPlayerPanel(const FString& headIcon, USoundCue* sound);
void UpdateHelperSoundData(UBOOL isPlaying);

void StopCurSound();

#endif