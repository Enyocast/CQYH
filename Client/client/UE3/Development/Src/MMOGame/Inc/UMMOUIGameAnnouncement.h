#ifndef _MMOGAMEANNOUNCEMENT_H_
#define _MMOGAMEANNOUNCEMENT_H_

virtual void Init();
//void InitMc();

virtual void PreOnShow(UBOOL show);

//virtual void UnInit();
//virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void InitContent();
void UpdateContent( INT textIdx );

#endif