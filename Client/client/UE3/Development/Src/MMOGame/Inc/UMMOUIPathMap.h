#ifndef _MMOPATHMAP_H_
#define _MMOPATHMAP_H_

virtual void Init();
void InitMc();

virtual void PreOnShow(UBOOL show);
UBOOL CreateMapMarkUIObject( struct FObjInMapUI *pMapMarkData );
//UGFxObject* GetMapMarkUIObjectContainer( INT type );
void DistoryRootMc( UGFxObject* &pMc );

virtual void UnInit();
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

#endif