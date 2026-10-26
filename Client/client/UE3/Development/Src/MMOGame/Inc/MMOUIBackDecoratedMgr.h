#ifndef _UBACKDECORATEMANAGER_H_
#define _UBACKDECORATEMANAGER_H_

#include "MMOSingleton.h"

const static INT MAX_BACK_DECORATED_UPGRADE_LV = 5;
struct BackDecoratedMakeUpCfg
{
	INT _MakedItemID;

	INT _ConsumptionItemID;
	INT _ConsumptionItemCnt;

	UINT _MakeUpMnyCosts;

	BackDecoratedMakeUpCfg();
};

struct BackDecoratedUpgradeCfg
{
	INT _ToUpgradeItemID;
	INT _ToUpgradeItemLv;

	INT _ConsumptionItemID;
	INT _ConsumptionItemCnt;

	INT _SuccessRate;

	UINT _UpgradeMnyCosts;

	INT _UpgradedItemID;

	BackDecoratedUpgradeCfg();
};

typedef TMap< INT, BackDecoratedMakeUpCfg > BackDecoratedCfgContainer;
typedef TMap< INT, BackDecoratedUpgradeCfg > BackDecoratedUpgradeCfgContainer;

class MMOUIBackDecoratedMgr : public SingletonMeyers<MMOUIBackDecoratedMgr>, public INativeGameEventHandler
{
public:
	MMOUIBackDecoratedMgr();
	~MMOUIBackDecoratedMgr();
public:
	void Initialize();
	void Shutdown();
	void OnNativeGameEvent( struct MMOGameEvent* evt );

public:
	UBOOL ReadBackDecoratedMakeUpCfg();
	const BackDecoratedMakeUpCfg* FindBackDecoratedMakeUpCfg( INT makeUpItemID ){
		return _BackDecoratedCfgs.Find( makeUpItemID );
	}
	BackDecoratedMakeUpCfg* AddBackDecoratedMakeUpCfg( INT makeUpItemID ){
		return &_BackDecoratedCfgs.FindOrAdd( makeUpItemID );
	}

	const BackDecoratedUpgradeCfg* FindUpgradeCfg( INT upgradeItemID, INT itemLV ){
		return _BackDecoratedUpgradeCfgs.Find( upgradeItemID );
	}
	BackDecoratedUpgradeCfg* AddBackUpgradeCfg( INT upgradeItemID, INT itemLV ){
		return &_BackDecoratedUpgradeCfgs.FindOrAdd( upgradeItemID );
	}
	
private:
	BackDecoratedCfgContainer _BackDecoratedCfgs;
	BackDecoratedUpgradeCfgContainer _BackDecoratedUpgradeCfgs;
};

#endif
