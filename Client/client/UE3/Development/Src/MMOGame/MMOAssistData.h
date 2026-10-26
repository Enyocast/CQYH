#ifndef _MMOASSISTDATA_H_
#define _MMOASSISTDATA_H_

#include "MMOSingleton.h"
#include <map>
#include <vector>
#include "UnString.h"
#include "MMOFacade.h"
#include "MMODataManager.h"

enum
{
	DEFAULT_PRACTISE_TIME = 4,		// 秒
	MIN_PRACTISE_TIME = 1,			// 秒
	DEFAULT_PROTECT_TIME = 2,		// 秒
	MIN_PROTECT_TIME = 1,			// 秒
	DEFAULT_PROTECT_VALUE = 10,		// #20091
};

// 掉落数据
enum EAssistDropType
{
	EADT_ALL = 0,
	EADT_OTHER,
	EADT_DRUG,
	EADT_CLOTHING,
	EADT_WEAPON,
	EADT_ACCESSORY,
	EADT_MAX
};

struct AssistDropData
{
	UINT32 Id;
	UINT32 ItemClass;
	UBOOL Valuable;
	UBOOL AutoPick;
	UBOOL Visible;
	UINT32 Group;
};

struct AssistDropInfo
{
	UINT32 Id;
	UBOOL Valuable;
	UBOOL AutoPick;
	UBOOL Visible;
};

struct AssistDropDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("AssistDrop.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}

	static AssistDropData* CreateDataObject(INT templateID, bool& needAddToMap);
	static void DestroyDataObject(AssistDropData* obj);
	static void ParseData(AssistDropData* obj, class CTabFile* dataRow, int rowIdx);

	static FString GetTemplateIDName()
	{
		return TEXT("ID");
	}

	static FString FormatAsString(AssistDropData* obj)
	{
		return "";
	}

	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(AssistDropData* obj, TSet<FString>& outResList)
	{
		//_CollectReferencedResource(obj, outResList);
	}
#endif
};

typedef TDataManger<AssistDropData, AssistDropDataProcessor> AssistDropDataManager;
typedef std::map<UINT32, AssistDropData, M_UE3_STL_ALLOC_MAP(UINT32, AssistDropData)> AssistDropDataMap;
typedef std::map<UINT32, AssistDropInfo, M_UE3_STL_ALLOC_MAP(UINT32, AssistDropInfo)> AssistDropInfoMap;

// 保护道具
enum EAssistItemType
{
	EAIT_SLOW_HP = 0,		// 缓回药:HP
	EAIT_SLOW_MP,			// 缓回药:MP
	EAIT_SLOW_HPMP,			// 缓回药:HP&MP
	EAIT_FAST_HP,			// 瞬回药:HP
	EAIT_FAST_MP,			// 瞬回药:MP
	EAIT_FAST_HPMP,			// 瞬回药:HP&MP
	EAIT_PROTECT_HP,		// 保护道具:HP
	EAIT_PROTECT_MP,		// 保护道具:MP
	EAIT_PROTECT_HPMP,		// 保护道具:HP&MP
	EAIT_MAX
};

enum EProtectType
{
	EPT_SLOW_HP = 0,		// 体力药
	EPT_SLOW_MP,			// 魔法药
	EPT_FAST_HP1,			// 瞬回药:HP1
	EPT_FAST_MP1,			// 瞬回药:MP1
	EPT_FAST_HP2,			// 瞬回药:HP2
	EPT_FAST_MP2,			// 瞬回药:MP2
	EPT_PROTECT_HP,			// 保护道具:HP
	EPT_PROTECT_MP,			// 保护道具:MP
	EPT_TOTAL
};

struct AssistItemData
{
	UINT32 ItemId;
	UINT8 ItemType;
	UINT8 Sort;
};

struct AssistItemInfo
{
	UINT8 ProtectType;
	UINT32 ItemId;
	UBOOL Enable;
	UINT16 Value;
	UINT8 Time;

	AssistItemInfo()
	{
		ProtectType = EPT_TOTAL;
		ItemId = 0;
		Enable = FALSE;
		Value = 0;
		Time = DEFAULT_PROTECT_TIME;
	}
};

struct AssistItemDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("AssistItem.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}

	static AssistItemData* CreateDataObject(INT templateID, bool& needAddToMap);
	static void DestroyDataObject(AssistItemData* obj);
	static void ParseData(AssistItemData* obj, class CTabFile* dataRow, int rowIdx);

	static FString GetTemplateIDName()
	{
		return TEXT("ItemId");
	}

	static FString FormatAsString(AssistItemData* obj)
	{
		return "";
	}

	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(AssistItemData* obj, TSet<FString>& outResList)
	{
		//_CollectReferencedResource(obj, outResList);
	}
#endif
};

typedef TDataManger<AssistItemData, AssistItemDataProcessor> AssistItemDataManager;
typedef std::map<UINT32, AssistItemData, M_UE3_STL_ALLOC_MAP(UINT32, AssistItemData)> AssistItemDataMap;
typedef std::list<AssistItemData, M_UE3_STL_ALLOC(AssistItemData)> AssistItemDataList;

class MMOAssistData : public SingletonMeyers<MMOAssistData>
{
public:
	MMOAssistData();
	virtual ~MMOAssistData();

	void Init();
	void Shutdown();
	void Clear();

	// 掉落
	void AddAssistDropData(const AssistDropData& data);
	AssistDropDataMap& GetAssistDropDataMap();
	UBOOL GetAssistDropData(UINT32 id, AssistDropData& data);
	void AddAssistDropInfo(const AssistDropInfo& info);
	AssistDropInfoMap& GetAssistDropInfoMap();
	void UpdateAssistDropInfo(UINT32 id, UBOOL valuable, UBOOL autoPick, UBOOL visible);
	void UpdateAssistDropInfoDefault();
	UBOOL IsDropValuable(UINT32 id);
	UBOOL IsDropAutoPick(UINT32 id);
	UBOOL IsDropVisible(UINT32 id);

	// 保护
	void AddAssistItemData(const AssistItemData& data);
	AssistItemDataMap& GetAssistItemDataMap();
	UBOOL GetAssistItemData(UINT32 id, AssistItemData& data);
	UBOOL GetAssistItemInfo(UINT8 protectType, AssistItemInfo& info);
	void UpdateAssistItemInfo(UINT8 protectType, const AssistItemInfo& info);
	void UpdateAssistItemInfoDefault();
	AssistItemDataList& GetAssistItemSlowHpList();
	AssistItemDataList& GetAssistItemSlowMpList();

	UINT32 GetAssistItemIdByIndex(UINT8 protectType, UINT8 index);
	UINT8 GetAssistItemIndexById(UINT8 protectType, UINT32 itemId);

protected:
	UBOOL _LoadAssistDropData(const TCHAR* filePath);
	void _UnloadAssistDropData();

	UBOOL _LoadAssistItemData(const TCHAR* filePath);
	void _UnloadAssistItemData();

	AssistDropDataMap _AssistDropDataMap;
	AssistDropInfoMap _AssistDropInfoMap;

	AssistItemDataMap _AssistItemDataMap;
	AssistItemInfo _AssistItemInfo[EPT_TOTAL];
	AssistItemDataList _AssistItemSlowHpList;
	AssistItemDataList _AssistItemSlowMpList;
};

#endif