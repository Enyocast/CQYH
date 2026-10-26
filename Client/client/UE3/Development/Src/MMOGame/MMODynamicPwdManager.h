#ifndef _DYNAMICPWD_MANAGER_H_
#define _DYNAMICPWD_MANAGER_H_

#include "MMOSingleton.h"
#include "MMOGameEvent.h"
#include "MMOGameUIClasses.h"
#include "MMODataManager.h"
#include "MMOUtil.h"


class MMODynamicPwdManager : public SingletonMeyers<MMODynamicPwdManager>, public INativeGameEventHandler
{
public:
	MMODynamicPwdManager();
	virtual ~MMODynamicPwdManager();


	void Init();
	
	void NotifyShowDynamicPassword();

	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
};

#endif