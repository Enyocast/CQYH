
#ifndef _MMO_HEAVEN_MANAGER__H_
#define _MMO_HEAVEN_MANAGER__H_

#include "MMOSingleton.h"
#include "MMODataManager.h"
#include "common.h"
#include "role_db_def.h"
#include "spirit_def.h"

	//一个气物品
	struct GasItem
	{
		INT					nUniqueID;		//客户端用的唯一ID
		INT					nSlotIndex;		//位置索引	
		INT					nContainerID;	//所在容器ID
		INT					nTempID;		//关联的气模板
		INT					nCurExp;		//当前的经验
		GasItem()
		{
			appMemzero(this, sizeof(GasItem));
		}
	};

	//气槽
	struct GasSlot
	{
		INT					 nUniqueID;		//关联的气唯一ID
		INT					 nLocked;		//锁定中
		INT					 nDisable;		//未开启不可用
		INT					 nTagID;
		GasSlot()
		{
			nUniqueID = 0;
			nLocked = 0;
			nDisable = 0;
			nTagID   = -1;
		}
	};

	//血槽
	struct BloodSlot
	{
		INT						 nPage;
		INT						 nIndex;
		INT						 nValue;
		INT						 nState;
		FString					 sName;
		BloodSlot()
		{
			appMemzero(this, sizeof(BloodSlot));
		}
	};
	//-----------------------------配置------------------
	//境界等级属性配置
	struct HeavenLevelConfig
	{
		INT						 nLevel;			//当前境界等级
		INT						 nAddExp;			//增加多少经验
		INT						 nAddHeavenPts;		//增加多少修炼点
		INT						 nSoulCost;			//消耗多少魂
		INT						 nNeedTime;			//转化需要时间
		INT						 VIPOfflineDiscount1;	//Vip离线转化折扣
		INT						 VIPOfflineDiscount2;	//Vip离线转化折扣
		INT						 VIPOfflineDiscount3;	//Vip离线转化折扣

		INT						 VipOnlineChangeDiscount1;	//Vip在线转化折扣
		INT						 VipOnlineChangeDiscount2;	//Vip在线转化折扣
		INT						 VipOnlineChangeDiscount3;	//Vip在线转化折扣
		INT						 nNeedMoney;		//买转化需要多少钱
		INT						 nMaxExp;			//下级的经验
		INT						 nExp2PtsRate;		//转化效率
		INT						 nAtriNodeID1;		//属性
		INT						 nAtriNodeID2;
		INT						 nDailyExp2PtsMaxCount;//当天转化最大次数
		HeavenLevelConfig()
		{
			appMemzero(this, sizeof(HeavenLevelConfig));
		}
	};

	//气模板属性配置
	struct HeavenGasItemConfig
	{
		INT						nID;
		INT						nLevel;				//气等级
		INT						nQuality;			//品质
		INT						nExp;				//经验
		INT						nNextLevelID;		//下级ID
		INT						nAtriNodeID1;
		INT						nAtriNodeID2;
		INT						nExchangeCost;		//兑换气需要的万法之气数量
		INT						nGroupID;
		INT						nNextLevelExp;
		INT						nJob;
		INT						nCanExchange;
		FString					name;
		FString					Icon0;
		FString					Icon1;
		HeavenGasItemConfig()
		{
			appMemzero(this, sizeof(HeavenGasItemConfig));
		}
	};

	//血模板属性配置
	struct HeavenBloodConfig
	{
		INT						nPage;				//血脉类型
		INT						nSlot;				//槽
		INT						nLevel;				//等级 0-10
		INT						nHeavenPtsCost;		//消耗修炼点
		INT						nRate;				//成功几率
		INT						nLevelLimit;		//等级限制	
		INT						nPageLevelLimit;	//页的境界等级限制
		INT						nAttValue1;
		INT						nAttValue2;
		HeavenBloodConfig()
		{
			appMemzero(this, sizeof(HeavenBloodConfig));
		}
	};
	//------------------------------------------------------------------

	struct HeavenTitleTool
	{
		INT						GetStartNum(INT nLevel);
		INT						GetLevelTitleIndex(INT nLevel);
		INT						GetStarTitleIndex(INT nLevel);
		FString					GetLevelTitle(INT nLevel);
		FString					GetStarTitle(INT nLevel);
		FString					GetLevel(INT nLevel);
		FString					_IndexGetLevelTitle(INT nIndex);
		FString					_IndexGetStarTitle(INT nIndex);
		HeavenTitleTool();
	private:
		TArray<FString>			levelTitle;
		TArray<FString>			starTitle;
	};

	struct SlotOpenTaxData
	{
		INT nSlotID;
		INT	nHeavenLevel;
		INT nMoney;
		SlotOpenTaxData()
		{
			appMemzero(this,sizeof(SlotOpenTaxData));
		}
	};
	enum HeavenConvertType
	{
		HeavenConvertType_OnLineConvert = 0,
		HeavenConvertType_JustConvert,
		HeavenConvertType_OutLineConvert,
	};
	enum HeavenGasOperateType
	{
		HeavenGasOperateType_Invalid = 0,
		HeavenGasOperateType_Practise,
		HeavenGasOperateType_Merge,
		HeavenGasOperateType_Exchange,
	};
	//境界事件通知
	struct MMOGameEvent_Heaven : public MMOGameEvent
	{
	public:
		enum EHeavenEventType
		{
			EHeavenEvent_SynData,
			EHeavenEvent_UpdateGasItem,
			EHeavenEvent_UpdateGasSlot,
			EHeavenEvent_UpdateLevel,
			EHeavenEvent_UpdateExp,
			EHeavenEvent_PractisePhrase,
			EHeavenEvent_BloodStateInit,
			EHeavenEvent_TargetSlotState,
			EHeavenEvent_LogInfo,
			EHeavenEvent_UpdateNeedTime,
			EHeavenEvent_BloodStateUpdate,
			EHeavenEvent_BloodStateOpen,
			EHeavenEvent_PractiseAnimation,
			EHeavenEvent_MergeAnimation,
		};

		MMOGameEvent_Heaven(EHeavenEventType eventType)
			: EventType(eventType)
		{
		}

		virtual EGameEvent GetEventType() const
		{
			return GameEvent_Heaven;
		}

		EHeavenEventType	EventType;
		INT					SlotID;
		INT					SlotContainerID;
		INT					nValue;
	};


	struct HeavenLevelDataProcessor
	{
		static const TCHAR* GetName()
		{
			return TEXT("spirit.txt");
		}

		static INT ParseID(const FString& idStr)
		{
			return appAtoi(*idStr);
		}

		static HeavenLevelConfig* CreateDataObject(INT templateID, bool& needAddToMap);

		static void DestroyDataObject(HeavenLevelConfig* obj);

		static void ParseData(HeavenLevelConfig* obj, class CTabFile* dataRow, int rowIdx);

		static FString GetTemplateIDName()
		{
			return TEXT("Level");
		}
		
		static FString FormatAsString(HeavenLevelConfig* obj)
		{
			return "HeavenLevelConfig";
		}

		static void PostInitData();

#if WITH_EDITOR
		static void CollectReferencedResourceFromDataTable(HeavenLevelConfig* obj, TSet<FString>& outResList)
		{
			//_CollectReferencedResource(obj, outResList);
		}
#endif
	};

	typedef TDataManger< HeavenLevelConfig, HeavenLevelDataProcessor > MMOHeavenLevelDataManager;

	struct HeavenGasItemDataProcessor
	{
		static const TCHAR* GetName()
		{
			return TEXT("air.txt");
		}

		static INT ParseID(const FString& idStr)
		{
			return appAtoi(*idStr);
		}

		static HeavenGasItemConfig* CreateDataObject(INT templateID, bool& needAddToMap);

		static void DestroyDataObject(HeavenGasItemConfig* obj);

		static void ParseData(HeavenGasItemConfig* obj, class CTabFile* dataRow, int rowIdx);

		static FString GetTemplateIDName()
		{
			return TEXT("ID");
		}

		static FString FormatAsString(HeavenGasItemConfig* obj)
		{
			return obj->name;
		}

		static void PostInitData();

#if WITH_EDITOR
		static void CollectReferencedResourceFromDataTable(HeavenGasItemConfig* obj, TSet<FString>& outResList)
		{
			//_CollectReferencedResource(obj, outResList);
		}
#endif
	};

	typedef TDataManger< HeavenGasItemConfig, HeavenGasItemDataProcessor >   MMOHeavenGasItemDataManager;

	struct HeavenBloodDataProcessor
	{
		static const TCHAR* GetName()
		{
			return TEXT("blood.txt");
		}

		static INT ParseID(const FString& idStr)
		{
			return appAtoi(*idStr);
		}

		static HeavenBloodConfig* CreateDataObject(INT templateID, bool& needAddToMap);

		static void DestroyDataObject(HeavenBloodConfig* obj);

		static void ParseData(HeavenBloodConfig* obj, class CTabFile* dataRow, int rowIdx);

		static FString GetTemplateIDName()
		{
			return TEXT("Page");
		}

		static FString FormatAsString(HeavenBloodConfig* obj)
		{
			return "HeavenBloodConfig";
		}

		static void PostInitData();

#if WITH_EDITOR
		static void CollectReferencedResourceFromDataTable(HeavenBloodConfig* obj, TSet<FString>& outResList)
		{
			//_CollectReferencedResource(obj, outResList);
		}
#endif
	};

	typedef TDataManger< HeavenBloodConfig, HeavenBloodDataProcessor > MMOHeavenBloodDataManager;

	struct HeavenJustConvertData
	{
		INT nID;
		INT nTimesCount;
		INT nCostDiscount;
	};
	struct HeavenJustConvertProcessor
	{
		static const TCHAR* GetName()
		{
			return TEXT("spirit_change.txt");
		}

		static INT ParseID(const FString& idStr)
		{
			return appAtoi(*idStr);
		}

		static HeavenJustConvertData* CreateDataObject(INT templateID, bool& needAddToMap);

		static void DestroyDataObject(HeavenJustConvertData* obj);

		static void ParseData(HeavenJustConvertData* obj, class CTabFile* dataRow, int rowIdx);

		static FString GetTemplateIDName()
		{
			return TEXT("Index");
		}

		static FString FormatAsString(HeavenJustConvertData* obj)
		{
			return "HeavenJustConvertData";
		}

		static void PostInitData();

#if WITH_EDITOR
		static void CollectReferencedResourceFromDataTable(HeavenJustConvertData* obj, TSet<FString>& outResList)
		{
			//_CollectReferencedResource(obj, outResList);
		}
#endif
	};

	typedef TDataManger< HeavenJustConvertData, HeavenJustConvertProcessor > MMOHeavenJustConvertManager;

	//列表
	typedef std::list<HeavenBloodConfig,	M_UE3_STL_ALLOC(HeavenBloodConfig) >		HeavenBloodDataList;
	typedef std::list<GasItem,				M_UE3_STL_ALLOC(GasItem) >					GasItemList;
	typedef std::list<HeavenJustConvertData,M_UE3_STL_ALLOC(HeavenJustConvertData) >	HeavenConvertList;
	typedef std::list<INT,					M_UE3_STL_ALLOC(INT) >						HeavenAttList;
	typedef std::map<INT, HeavenGasItemConfig*, M_UE3_STL_ALLOC_MAP(INT, HeavenGasItemConfig*) >	HeavenGasTemplateMap;
	typedef std::map<INT, HeavenLevelConfig*, M_UE3_STL_ALLOC_MAP(INT, HeavenLevelConfig*) >		HeavenLevelDataMap;

	//境界管理类
	class MMOHeavenManager : public SingletonMeyers<MMOHeavenManager>, public INativeGameEventHandler
	{
	public:

		MMOHeavenManager();
		virtual ~MMOHeavenManager(){}

		void							Init();
		void							Shutdown();
		void							Clear();
	
		virtual void					OnNativeGameEvent(struct MMOGameEvent* evt);
		void							Update(FLOAT deltaTime);
		const HeavenGasTemplateMap&     GetGasItemDataMap();
		HeavenAttList&					GetHeavenAttributeList();
		const TArray<FString>&			GetConverterLog();
		const GasItem*					GetGasItemBySlot(INT nContainerID, INT nSlotIndex);
		const HeavenGasItemConfig*		GetGasTemplate(INT nTempID);
		const HeavenLevelConfig*		GetHeavenCurLevelData();
		const HeavenLevelConfig*		GetHeavenLevelData(INT nLevel);
		const HeavenBloodConfig*		GetHeavenBloodData(INT nPage,INT nSlot,INT nLevel);
		const GasSlot*					GetTargetSlot()const;
		const BloodSlot*				GetBloodSlot(INT nPage,INT nIndex)const;
		INT								GetStarNum(INT nLevel);
		INT								GetStarTitleIndex(INT nLevel);
		INT								GetLevelTitleIndex(INT nLevel);
		FString							GetLevelTitle(INT nLevel);
		FString							GetLevelString(INT nLevel);
		FString							GetStarTitle(INT nLevel);
		void							GetHeavenTips(FString& tips,INT nLevel);
		void							GetHeavenGasItemTips(FString& tips,INT nContainerID,INT nSlotID);
		void							GetHeavenBloodTips(FString&tips,INT nPage,INT nSlot);
		void							GetHeavenGasTipsByGasID(FString& tips,INT nGasID,INT nCurExp = -1);
		INT								GetEquipContainerSize(){return arrSlotGasEquip.Num();};
		INT								GetBagContainerSize(){return arrSlotGasBag.Num();};
		INT								GetBankContainerSize(){return arrSlotGasBank.Num();};
		void							ChangeTargetGasItem(INT nSrcSlot);
		INT 							GetNeedTime();
		UINT32							GetTodayConvertTimes();
		UINT32							GetTodayConvertMaxTimes();
		INT								GetNeedMoneyOpenSlot(INT nContainerID, INT nSlotIndex);
		INT								GetNeedMoneyConvert();
		void							ClearTargetSlot();
		INT								GetBtnPractiseState(INT nIndex);
		void							GetEquipGasPowerDescrible(FString& strPower);
		const SlotOpenTaxData*			GetSlotEquipTax(INT nIndex) const;
		INT								GetEquipGasPower();
		BOOL							GetBloodLockState(INT nPage);
		INT								GetGasPowerByID(INT nGasID);
		INT								GetCanEquipSlotID();
		INT								GetNextLevelExp();
		INT                             GetNextLevelPts();
		//server notify
		void							NotifyMoneyChange(INT nMoneyType,INT nMoney,INT nOldMoney);
		void							NotifyLevelChange(INT nLevel);
		void							NotifyUpdateHeavenData(const ROLE_DB_SPIRIT_DATA* pkData);
		void							NotifyUpdateHeavenExp(INT nExp);
		void							NotifyUpdateHeavenLevel(INT nLevel);
		void							NotifyUpdatePractiseBtnIndex(INT nIndex);
		void							NotifyUpdateGasChange(INT nExp,INT nGasID,INT nContainerID,INT nSlotIndex);
		void							NotifyOpenGasSlot(INT nContainerID,INT nSlotIndex);
		void							NotifyUpdateBloodState(INT nPage,INT nIndex, INT nNum);
		void							ParseHeavenError(INT32 errorId, INT32 param1, INT32 param2, FString& errorStr);
		void							NotifyGameStateChange();
		void							NotifyBloodOpen(INT nPage);

		//客户端发送消息预判
		BOOL							CheckGasBagFull();
		BOOL							CheckSoultoConvert();
		BOOL							CheckMoneytoOpenSlot(INT nContainerID, INT nSlotID);
		BOOL							CheckXiuLiantoPractise(INT nIndex);
		BOOL							CheckGasMoneytoExchange(INT nGasID);
		BOOL							CheckLeveltoOpenSlot(INT nContainerID, INT nSlotID);
		BOOL							CheckHeavenLeveltoEquipSlot(INT nContainerID, INT nSlotID);
		BOOL							CheckHavePurpleGasBag();
		BOOL							GenerateHeavenMergeGasHint(FString& hint);
		void							SetConvertType(INT nType);
		INT								GetConvertType();	
		FString							GetConvertStr();	
		void							SetGasOperateType(INT nType);
		INT								GetGasOperateType(){return nGasOperateType;}
		GasItem*						GetItemBySlot(INT nContainerID,INT nSlotID);
		void 							GenerateGasTipsByNodeID(FString& tips,INT nNondeID1,INT nNodeID2,bool bRow = true);
		void							AddGasItemTemplateData(INT nKey,HeavenGasItemConfig* data);
		void							AddHeavenLevelData(INT nKey,HeavenLevelConfig* data);
		void							AddHeavenBloodData(HeavenBloodConfig& data);
		void							AddHeavenConvertData(HeavenJustConvertData& data);
		void							SetLastOffLineTime(UINT32 dwTime);
		BOOL							GetGasSkillArr(FString& tips,INT nID);
	private:
		GasItem*						GetItemByID(INT nID);
		GasSlot*						GetSlotByIndex(INT nContainerID,INT nSlotID);
		BloodSlot*						GetBloodSlotByIndex(INT nPage, INT nIndex);
		HeavenLevelConfig*				GetHeavenLevelDataIn(INT nLevel);
		HeavenGasItemConfig*			GetGasTemplateConfig(INT nTempID);
		void							AddNewGas(GasItem& data);
		void							DelGasItem(INT nUniqueID);
		INT								GenerateUniqueID();
		void							CheckSendOutLineConverter(INT nLevel);
		void							UpdateCheckSendNormalConverter();
		void							RefreshTargetItem();
		INT								GetGasExpLevelUp(HeavenGasItemConfig*pkGas,INT nExp);
		void							LoadHeavenData();
		BOOL							LoadOpenSlotCondition(const TCHAR* filePath);
		void							CheckSoulValue();
		void							CheckLevelValue();
		void							CheckSetNeedTime(BOOL bForce = FALSE);
		void							ShowNewGasHint(INT nGasID);
		INT								GetJustConvertDiscount();
		void							GerateLogInfo(INT nExp,INT nSpell);
	private:
		TArray<FString>					 converterLogLookUp;	
		//血海槽
		TArray<BloodSlot>				 arrSlotBlood;
		//气包裹 装备栏 仓库槽
		TArray<GasSlot>					 arrSlotGasBag;
		TArray<GasSlot>					 arrSlotGasBank;
		TArray<GasSlot>					 arrSlotGasEquip;
		TArray<SlotOpenTaxData>			 arrSlotTax;
		//合成目标槽
		GasSlot*						 pkTargetGasSlot;
		//玩家所有气物品
		GasItemList						 myGasItemList;
		//模板数据
		HeavenGasTemplateMap			 gasItemTemplateMap;
		HeavenLevelDataMap				 heavenLevelDataMap;
		HeavenBloodDataList				 heavenBloodDataList;
		UINT32							 dwLastOfflineTime;		// 上次下线时间
		UINT32							 dwLastExp2PtsTime;		// 上次转化时间
		INT32							 nDailyExp2PtsTime;		// 今天转化次数
		INT								 nCostMoneyAll;
		INT								 nCurHeavenExp;
		time_t							 tNowTime;
		INT								 nNowNeedTime;
		INT								 gasPractiseState;
		HeavenTitleTool					 heavenTitleTool;
		INT								 nBloodState[MAX_BLOODSEA_PAGE];
		//生成气唯一ID内部用
		INT								 curMaxID;
		INT								 nHeavenLevel;
		BOOL							 bSoulLimited;
		BOOL							 bLevelLimited;
		BOOL							 bServerWaiting;
		INT								 nCurConvertType;
		INT							     nGasOperateType;
		INT							     nTempGasOperateType;
		//属性列值
		HeavenAttList					 heavenAttList;
		HeavenConvertList				 heavenConvertList;
	public:
		const static INT				 oneKeyPracticeLevel = 10;			
	};
#endif