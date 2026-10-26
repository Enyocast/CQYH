
#ifndef _MMOCOOLDOWNMANAGER_H_
#define _MMOCOOLDOWNMANAGER_H_

#include "MMOSingleton.h"
#include "MMOUtil.h"
#include "MMOGameEvent.h"

struct CoolDownData
{
	CoolDownData()
	{
		appMemzero( this , sizeof(CoolDownData) );
	}
	INT CDType;
	INT32 Id;
	INT32 CurValue;
	INT32 MaxValue;
};

class MMOCoolDownManager : public SingletonMeyers<MMOCoolDownManager>
{
public:

	MMOCoolDownManager();
	virtual ~MMOCoolDownManager();

	void Init();
	void Shutdown();

	void ClearAllCD();
	void TickCD( FLOAT time );
	void AddNewCD( INT InType, INT32 InId, INT32 InValue );

	CoolDownData* GetCDData( COOLDOWN_TYPE InType, INT32 InId );

protected:
	
	TArray<CoolDownData> CDList;
};

#endif