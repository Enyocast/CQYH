#ifndef _MMOSYSTEMACTIVATEMANAGER_H_
#define _MMOSYSTEMACTIVATEMANAGER_H_

#include "MMOSingleton.h"
#include <map>
#include <vector>
#include <queue>

// 开启系统
enum EActivateSystemType
{
	EAST_Guild,					// 公会
	EAST_Schedule,				// 活动
	EAST_GoldStore,				// 金币交易行
	EAST_LingXing,				// 灵性
	EAST_LongWei,				// 龙卫心法
	EAST_NormalQuest,			// 普通任务
	EAST_QiXi,					// 气息
	EAST_Mall,					// 商城
	EAST_Repute,				// 声望
	EAST_MasterStudent,			// 师徒
	EAST_Enhance,				// 体格强化				
	EAST_Riding,				// 坐骑			
	EAST_Handbook,				// 百晓生
	EAST_Tatol
};

class MMOSystemActivateManager : public SingletonMeyers<MMOSystemActivateManager>, public INativeGameEventHandler
{
public:
	MMOSystemActivateManager();
	virtual ~MMOSystemActivateManager();

	void Init();
	void Shutdown();
	void Clear();
	void Update(FLOAT deltaTime);

	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

	// 新功能开启
	INT GetNextSystemType();
	INT GetChildMenuType(INT systemType);
	UBOOL GetSystemInfo(INT systemType, FString& icon, FString& name);

	void NotifyPlayerLevelChange(INT curLevel);

protected:
	void _PushNewSystem(INT systemType);
	void _ActivateSystem(UINT32 level);

	typedef std::map<INT,INT> ActivateSystemLevelMap;
	ActivateSystemLevelMap _ActivateSystemLevelMap;

	typedef std::set<INT> ActivateSystemSet;
	ActivateSystemSet _ActivateSystemSet;

	typedef std::queue<INT> ActivateSystemQueue;
	ActivateSystemQueue _ActivateSystemQueue;
};

#endif