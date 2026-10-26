#ifndef _GUIDEOPTION_MANAGER_H_
#define _GUIDEOPTION_MANAGER_H_

#include "MMOSingleton.h"
#include "MMOGameEvent.h"
#include "MMOGameUIClasses.h"
#include "MMOUtil.h"
#include "MMOFacade.h"

class MMOGuideOptionManager : public SingletonMeyers<MMOGuideOptionManager>, public INativeGameEventHandler
{
public:
	MMOGuideOptionManager();
	virtual ~MMOGuideOptionManager();

	void Init();
	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
	
	void OnEnterScene();
	void SetGameControlType(GAME_CONTROL_TYPE type);
};

#endif