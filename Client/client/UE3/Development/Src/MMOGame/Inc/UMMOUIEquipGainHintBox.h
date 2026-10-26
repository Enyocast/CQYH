#ifndef _MMOEQUIPGAINHINTBOX_H_
#define _MMOEQUIPGAINHINTBOX_H_

virtual void Init();
void InitMc();

virtual void PreOnShow(UBOOL show);

//virtual void UnInit();
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
void AddNewEquipGain( INT conID, INT slotID );
void ShowContent( INT conID, INT slotID );

#endif