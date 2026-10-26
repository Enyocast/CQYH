#ifndef _MMOGUIDEDATA_H_
#define _MMOGUIDEDATA_H_

#include "MMOSingleton.h"
#include <map>
#include <vector>
#include <queue>
#include "UnString.h"
#include "guild_def.h"
#include "MMOFacade.h"
#include "MMODataManager.h"
#include "MMOJourneyData.h"

enum
{
	MAX_GUIDE_COUNT = 128,
	MAX_TARGET_COMPONENT_COUNT = 5,
	MAX_PLAYER_CLASS_COUNT = 5
};

// 引导数据
struct GuideData
{
	UINT32 Id;												// 引导id
	UBOOL Enable;											// 开启
	UINT32 Type;											// 显示类型
	FString Desc;											// 引导描述
	EGuideEventType ActivateType;							// 激活事件
	EGuideEventType DeactiveType;							// 终止事件

	UINT32 LevelReq;										// 等级需求
	UINT32 GuideReq;										// 引导需求
	UINT32 QuestReq;										// 任务需求
	UINT32 ItemReq[5];										// 道具需求
	UINT32 SkillReq[5];										// 技能需求
	UINT32 ItemQuaReq;										// 道具品质需求
	UINT32 NpcReq;											// 对话的NPC
	EDOODAD_TYPE DoodadTypeReq;								// Doodad类型
	EPlayerClass ClassReq;									// 职业需求

	FString Picture[MAX_PLAYER_CLASS_COUNT];				// 图片说明

	FString Sound;											// 语音名称
	FString SoundIcon;										// 语音图标

	FString TargetWindowName;								// 关联窗口名称
	FString TargetComponentName[MAX_TARGET_COMPONENT_COUNT];// 关联组件名称
	FVector2D Offset;										// 相对于关联组件偏移
	UBOOL IsBoxed;											// 是否有边框特效
	FVector2D BoxOffset;									// 边框特效的偏移
	FVector2D BoxSize;										// 边框特效的大小
	EGuideBoxType BoxType;									// 边框特效的类型
	EGuideArrowTipsType ArrowTipsType;						// 箭头说明文字类型
	UBOOL TraceBagSlot;										// 是否追踪背包格子
	UBOOL TraceMenuBar;										// 是否追踪MenuBar
	ETraceMenuBarType TraceMenuBarType;						// 追踪MenuBar类型
	UINT32 TraceMenuType;									// 追踪MenuType
	UINT32 TraceMenuChildType;								// 追踪MenuChildType
	UBOOL TraceJourney;
	UINT32 TraceJourneyType;

	GuideData()
	{
		Id = 0;
		Type = EGDT_Null;
		Desc = TEXT("");
		Enable = FALSE;
		ActivateType = EGUET_Null;
		DeactiveType = EGUET_Null;

		LevelReq = 0;	
		GuideReq = 0;		
		QuestReq = 0;
		for (INT i = 0; i < MAX_PLAYER_CLASS_COUNT; ++ i)
		{
			ItemReq[i] = 0;
			SkillReq[i] = 0;
		}
		ItemQuaReq = 0;					
		NpcReq = 0;			
		DoodadTypeReq = E_dt_Invalid;
		ClassReq = EPCT_None;

		for (INT i = 0; i < MAX_PLAYER_CLASS_COUNT; ++ i)
		{
			Picture[i] = TEXT("");
		}						
		Sound = TEXT("");
		SoundIcon = TEXT("");

		TargetWindowName = TEXT("0");
		for (INT i = 0; i < MAX_TARGET_COMPONENT_COUNT; ++ i)
		{
			TargetComponentName[i] = TEXT("");
		}

		Offset = FVector2D(0, 0);
		IsBoxed = FALSE;								
		BoxOffset = FVector2D(0, 0);							
		BoxSize = FVector2D(0, 0);
		BoxType = EGBT_Null;
		ArrowTipsType = EGATT_Null;

		TraceBagSlot = FALSE;
		TraceMenuBar = FALSE;
		TraceMenuBarType = ETMBT_Right;
		TraceMenuType = EMenuType_Bag;
		TraceMenuChildType = EMenuType_Child_Bag;

		TraceJourney = FALSE;
		TraceJourneyType = JT_TOTAL;
	}
};

struct GuideDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("guide.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}

	static GuideData* CreateDataObject(INT templateID, bool& needAddToMap);
	static void DestroyDataObject(GuideData* obj);
	static void ParseData(GuideData* obj, class CTabFile* dataRow, int rowIdx);

	static FString GetTemplateIDName()
	{
		return TEXT("GuideId");
	}

	static FString FormatAsString(GuideData* obj)
	{
		return "";
	}

	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(GuideData* obj, TSet<FString>& outResList);
#endif
};

typedef TDataManger<GuideData, GuideDataProcessor> GuideDataManager;


enum GuideState
{
	GS_Unactivated = 0,
	GS_Activated,
	GS_Complete
};

typedef std::map<UINT32, GuideData, M_UE3_STL_ALLOC_MAP(UINT32, GuideData)> GuideDataMap;
typedef std::map<UINT32, GuideState, M_UE3_STL_ALLOC_MAP(UINT32, GuideState)> GuideStateMap;
typedef std::list<UINT32, M_UE3_STL_ALLOC(UINT32)> GuideList;
typedef std::map<UINT32, GuideList, M_UE3_STL_ALLOC_MAP(UINT32, GuideList)> GuideEventMap;

class MMOGuideData : public SingletonMeyers<MMOGuideData>
{
public:
	MMOGuideData();
	virtual ~MMOGuideData();

	void Init();
	void Shutdown();
	void Clear();
	void CollectReferencedResourceFromUpk(TSet<FString>& outResList);

	UBOOL LoadGuideData(const TCHAR* filePath);
	UBOOL LoadGuideDataFromUpk();
	void UnloadGuideData();

	void AddGuideData(const GuideData& data);
	UBOOL GetGuideData(UINT32 id, GuideData& data);
	GuideDataMap& GetGuideDataMap();

	UBOOL IsGuideEnable(UINT32 id);
	void ClearGuideState();
	GuideStateMap& GetGuideStateMap();
	GuideState GetGuideState(UINT32 id);
	void UpdateGuideState(UINT32 id, GuideState state);

	GuideEventMap& GetActivateGuideEventMap();
	GuideEventMap& GetDeactiveGuideEventMap();

protected:

	GuideDataMap _GuideDataMap;
	GuideStateMap _GuideStateMap;
	GuideEventMap _ActivateGuideEventMap;
	GuideEventMap _DeactiveGuideEventMap;
};

#endif