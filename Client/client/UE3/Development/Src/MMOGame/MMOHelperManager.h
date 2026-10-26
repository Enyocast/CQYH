#ifndef _MMOHELPERMANAGER_H_
#define _MMOHELPERMANAGER_H_

#include "MMOSingleton.h"
#include "MMOGameEvent.h"
#include "MMOUtil.h"
#include "MMOHelperData.h"
#include <queue>

class MMOHelperManager : public SingletonMeyers<MMOHelperManager>, public INativeGameEventHandler
{
public:
	MMOHelperManager();
	virtual ~MMOHelperManager();

	void Init();
	void Shutdown();
	void Clear();
	void Update(FLOAT deltaTime);

	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

	void OnShowPlayer(FLOAT duration);
	void OnHidePlayer();

protected:
	FLOAT _CurPlayerShowProgress;
	INT _CurPlayerShowTime;
};

#endif