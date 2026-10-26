#ifndef _MMOQUESTDATA_H_
#define _MMOQUESTDATA_H_

#include "MMOGameEvent.h"
#include "common.h"
#include "role_db_def.h"
#include "MMOUtil.h"
#include "MMODataManager.h"

// 公用
enum
{
	INVALID_QUEST_VAR_ID = -1,
	MAX_CIRCLE_AWARD_ITEM_COUNT = 4,
	MAX_STORY_QUEST_CHAPTER_NUM = 50,
	MAX_STORY_QUEST_STAGE_PER_CHAPTER_NUM = 50,
	REWARD_QUEST_NPC_ID = 6456,
	QUEST_GRID_QUERY_TIME = 2,
	MAX_QUEST_DOODAD_COUNT = 32,
	QUEST_CD_TIME = 2,
	QUEST_UPDATE_TIME = 1
};

enum EQestState
{
	EQS_Null = -1,
	EQS_Accept = 0,
	EQS_Available = 1,
	EQS_Completed = 2
};

// 任务数据
struct QuestDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("quest.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}
	static FString FormatAsString(UQuest* obj)
	{
		return "";
	}
	static FString GetTemplateIDName()
	{
		return TEXT("QuestTempID");
	}
	static UQuest* CreateDataObject(INT templateID, bool& needAddToMap);
	static void DestroyDataObject(UQuest* obj);
	static void ParseData(UQuest* obj, class CTabFile* dataRow, int rowIdx);
	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(UQuest* obj, TSet<FString>& outResList)
	{
		//_CollectReferencedResource(obj, outResList);
	}
#endif
};

typedef TDataManger<UQuest, QuestDataProcessor> QuestDataManager;

typedef std::map<INT, class UQuest*, M_UE3_STL_ALLOC_MAP(INT, class UQuest*)> QuestDataMap;	
typedef std::list<class UQuest*, M_UE3_STL_ALLOC(class UQuest*)> QuestDataList;					

// 任务Npc
struct QuestNpcInfo
{
	QuestDataMap StartQuestList;
	QuestDataMap EndQuestList;
};

// 已接任务
class AcceptedQuestData
{
public:
	UINT32 Id;
	UINT32 AcceptTime;
	UINT32 LeftTime;
	UINT8 KillNpcCount[MAX_CONDITION_PER_QUEST];
	UINT8 KillDoodadCount[MAX_CONDITION_PER_QUEST];
	UINT8 KillPlayerCount[CHECK_KILL_PLAYER_CONDITION];
	INT32 RoleVariable[MAX_ROLE_VARIABLE_COUNT];
	INT32 QuestVariable[MAX_VARIABLE_PER_QUEST];
	INT32 ClientVariable[MAX_CLIENT_VARIABLE_COUNT];
	UINT8 Level;

	UBOOL IsTraced;
	UBOOL IsExpanded;
	UBOOL IsNewQuest;
	UBOOL IsFailed;

	AcceptedQuestData();
	AcceptedQuestData(const ROLE_DB_QUEST_DATA::ROLE_DB_ACCEPTED_QUEST& src);

	AcceptedQuestData& operator =(const ROLE_DB_QUEST_DATA::ROLE_DB_ACCEPTED_QUEST& src);

	void _Init();
	void _Assign(const ROLE_DB_QUEST_DATA::ROLE_DB_ACCEPTED_QUEST &src);
};

// 任务奖励
struct QuestAwardItemInfo
{
	UItem* ItemTemplate;
	INT Count;
	INT Index; // 原始配置时的下标
};

typedef std::map<INT, QuestNpcInfo, M_UE3_STL_ALLOC_MAP(INT, QuestNpcInfo)> QuestNpcInfoMap;					// 任务NPC
typedef std::map<INT, AcceptedQuestData, M_UE3_STL_ALLOC_MAP(INT, AcceptedQuestData)> AcceptedQuestDataMap;		// 已接任务
typedef std::map<INT, class UQuest*, M_UE3_STL_ALLOC_MAP(INT, class UQuest*)> AvailableQuestDataMap;			// 可接任务

typedef std::list<INT, M_UE3_STL_ALLOC(INT) > QuestTraceList;													// 任务追踪

typedef std::vector<QuestAwardItemInfo, M_UE3_STL_ALLOC(QuestAwardItemInfo)> QuestAwardItemInfoList;			// 任务奖励

// 环任务数据
struct CircleQuestData
{
	INT CircleId;									// 环号
	INT	CircleGroup;								// 环组
	INT	CircleRoundMax;								// 每日环任务最多可做多少轮
	INT	CircleSize;									// 当前环任务包还的任务数
	INT ResetTime;									// 重置时间
	INT Level;										// 玩家等级
	INT	CircleRound;								// 环任务的轮号
	INT RewardId[MAX_QUEST_PER_CIRCLE];				// 奖励组索引
};

struct CircleQuestDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("circle_quest.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}
	static FString FormatAsString(CircleQuestData* obj)
	{
		return "";
	}
	static FString GetTemplateIDName()
	{
		return TEXT("CircleID");
	}
	static CircleQuestData* CreateDataObject(INT templateID, bool& needAddToMap);
	static void DestroyDataObject(CircleQuestData* obj);
	static void ParseData(CircleQuestData* obj, class CTabFile* dataRow, int rowIdx);
	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(CircleQuestData* obj, TSet<FString>& outResList)
	{
		//_CollectReferencedResource(obj, outResList);
	}
#endif
};

typedef TDataManger<CircleQuestData, CircleQuestDataProcessor> CircleQuestDataManager;

// 一个环任务的奖励是由：环号，玩家等级，玩家当前完成的环任务序号，三个要素决定的
// 环任务奖励数据
struct CircleQuestRewardData
{
	INT RewardId;
	INT MoneyType;
	INT Money;
	INT Exp;
	INT BuffId;
	INT BuffLevel;
	INT Soul;
	INT Title;
	INT ReputationForceId;
	INT Reputation;
	INT AwardItemId[MAX_CIRCLE_AWARD_ITEM_COUNT];
	INT AwardItemCount[MAX_CIRCLE_AWARD_ITEM_COUNT];
	UBOOL NeedSelectAwardItem;
	INT SelectableAwardItemId[MAX_SELECTABLE_REWARD_COUNT];
	INT SelectableAwardItemCount[MAX_SELECTABLE_REWARD_COUNT];
	INT GuildContribute;
	INT MoneyTypeEx;
	INT MoneyEx;
};

struct CircleQuestRewardDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("quest_reward.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}
	static FString FormatAsString(CircleQuestRewardData* obj)
	{
		return "";
	}
	static FString GetTemplateIDName()
	{
		return TEXT("GroupID");
	}
	static CircleQuestRewardData* CreateDataObject(INT templateID, bool& needAddToMap);
	static void DestroyDataObject(CircleQuestRewardData* obj);
	static void ParseData(CircleQuestRewardData* obj, class CTabFile* dataRow, int rowIdx);
	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(CircleQuestRewardData* obj, TSet<FString>& outResList)
	{
		//_CollectReferencedResource(obj, outResList);
	}
#endif
};

typedef TDataManger<CircleQuestRewardData, CircleQuestRewardDataProcessor> CircleQuestRewardDataManager;

struct CircleQuestInfo
{
	INT CircleId;
	INT CircleIndex;
	INT CircleRound;
	INT QuestId;
	INT CompleteQuestTime;
		
	CircleQuestInfo () 
		: CircleId(0)
		, CircleIndex(0)
		, CircleRound(0)
		, QuestId(INVALID_QUEST_ID)
		, CompleteQuestTime(0)
	{}
};

typedef std::map<INT, CircleQuestData, M_UE3_STL_ALLOC_MAP(INT, CircleQuestData)> CircleQuestDataMap;						// 环任务数据
typedef std::map<INT, CircleQuestRewardData, M_UE3_STL_ALLOC_MAP(INT, CircleQuestRewardData)> CircleQuestRewardDataMap;		// 环任务奖励数据
typedef std::map<INT, CircleQuestInfo, M_UE3_STL_ALLOC_MAP(INT, CircleQuestInfo)> CircleQuestInfoMap;						// 环任务完成信息

// 悬赏任务
struct RewardQuestInfo
{
	UINT32 QuestId;
	EQestState QuestState;

	RewardQuestInfo () 
		: QuestId(INVALID_QUEST_ID)
		, QuestState(EQS_Null)
	{}
};

typedef std::list<RewardQuestInfo, M_UE3_STL_ALLOC(RewardQuestInfo) > RewardQuestList;										// 悬赏任务列表

// 悬赏任务花费
struct RewardQuestCostData
{
	INT Time;
	INT Cost;

	RewardQuestCostData() 
		: Time(0)
		, Cost(0)
	{}
};

struct RewardQuestCostDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("reward_quest_money_cost.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}
	static FString FormatAsString(RewardQuestCostData* obj)
	{
		return "";
	}
	static FString GetTemplateIDName()
	{
		return TEXT("Time");
	}
	static RewardQuestCostData* CreateDataObject(INT templateID, bool& needAddToMap);
	static void DestroyDataObject(RewardQuestCostData* obj);
	static void ParseData(RewardQuestCostData* obj, class CTabFile* dataRow, int rowIdx);
	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(RewardQuestCostData* obj, TSet<FString>& outResList)
	{
		//_CollectReferencedResource(obj, outResList);
	}
#endif
};

typedef TDataManger<RewardQuestCostData, RewardQuestCostDataProcessor> RewardQuestCostDataManager;
typedef std::map<INT, RewardQuestCostData, M_UE3_STL_ALLOC_MAP(INT, RewardQuestCostData)> RewardQuestCostDataMap;

// 剧情任务
struct StoryQuestData
{
	UINT32 Chapter;
	UINT32 Stage;
	FString ChapterName;
	FString ChapterDesc;
	FString ChapterIcon;
	FString StageName;
	FString StageDesc;

	StoryQuestData () 
		: Chapter(0)
		, Stage(0)
		, ChapterName(TEXT(""))
		, ChapterDesc(TEXT(""))
		, ChapterIcon(TEXT(""))
		, StageName(TEXT(""))
		, StageDesc(TEXT(""))
	{}
};

struct StoryQuestDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("quest_story.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}
	static FString FormatAsString(StoryQuestData* obj)
	{
		return "";
	}
	static FString GetTemplateIDName()
	{
		return TEXT("Chapter");
	}
	static StoryQuestData* CreateDataObject(INT templateID, bool& needAddToMap);
	static void DestroyDataObject(StoryQuestData* obj);
	static void ParseData(StoryQuestData* obj, class CTabFile* dataRow, int rowIdx);
	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(StoryQuestData* obj, TSet<FString>& outResList)
	{
		//_CollectReferencedResource(obj, outResList);
	}
#endif
};

typedef TDataManger<StoryQuestData, StoryQuestDataProcessor> StoryQuestDataManager;

#define MAKE_STORY_QUEST_KEY(chapter, stage) ((chapter << 16) | stage)
typedef std::map<UINT32, StoryQuestData, M_UE3_STL_ALLOC_MAP(UINT32, StoryQuestData)> StoryQuestDataMap;

typedef std::list<UINT32, M_UE3_STL_ALLOC(UINT32) > StoryQuestChapterList;
typedef std::list<UINT32, M_UE3_STL_ALLOC(UINT32) > StoryQuestStageList;
typedef std::map<UINT32, StoryQuestStageList, M_UE3_STL_ALLOC_MAP(UINT32, StoryQuestStageList)> StoryQuestChapterStageMap;

// 任务地图
typedef std::map<UINT32, QuestDataList, M_UE3_STL_ALLOC_MAP(UINT32, QuestDataList)> QuestMapDataMap;

// 回收任务
struct QuestRecycleData
{
	INT ItemLevel;
	INT ItemColor;
	FString ItemSubType;
	INT VarIndex;
};

struct QuestRecycleDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("quest_recycle.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}
	static FString FormatAsString(QuestRecycleData* obj)
	{
		return "";
	}
	static FString GetTemplateIDName()
	{
		return TEXT("ItemLevel");
	}
	static QuestRecycleData* CreateDataObject(INT templateID, bool& needAddToMap);
	static void DestroyDataObject(QuestRecycleData* obj);
	static void ParseData(QuestRecycleData* obj, class CTabFile* dataRow, int rowIdx);
	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(QuestRecycleData* obj, TSet<FString>& outResList)
	{
		//_CollectReferencedResource(obj, outResList);
	}
#endif
};

typedef TDataManger<QuestRecycleData, QuestRecycleDataProcessor> QuestRecycleDataManager;
typedef std::vector<QuestRecycleData, M_UE3_STL_ALLOC(QuestRecycleData)> QuestRecycleDataList;

// 杀怪任务：
// 怪物->已接任务映射	
typedef std::map<UINT32, QuestTraceList, M_UE3_STL_ALLOC_MAP(UINT32, QuestTraceList)> MonsterAcceptedQuestsMap;

// 紧急任务信息：用来记录紧急任务的CD时间，判断当前紧急任务是否可接
struct EmergencyQuestCoolDownInfo
{
	INT QuestId;
	INT CoolDown;
};

typedef std::map<INT, EmergencyQuestCoolDownInfo, M_UE3_STL_ALLOC_MAP(INT, EmergencyQuestCoolDownInfo)> EmergencyQuestCoolDownMap;

// 任务掉落
typedef std::set<INT> DoodadDropSet;
struct QuestDoodadData
{
	INT QuestId;
	DoodadDropSet DoodadDrops;

	QuestDoodadData() 
	{
		QuestId = INVALID_QUEST_ID;
		DoodadDrops.clear();
	}
};

struct QuestDoodadDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("quest_doodad.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}
	static FString FormatAsString(QuestDoodadData* obj)
	{
		return "";
	}
	static FString GetTemplateIDName()
	{
		return TEXT("QuestId");
	}
	static QuestDoodadData* CreateDataObject(INT templateID, bool& needAddToMap);
	static void DestroyDataObject(QuestDoodadData* obj);
	static void ParseData(QuestDoodadData* obj, class CTabFile* dataRow, int rowIdx);
	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(QuestDoodadData* obj, TSet<FString>& outResList)
	{
		//_CollectReferencedResource(obj, outResList);
	}
#endif
};

typedef TDataManger<QuestDoodadData, QuestDoodadDataProcessor> QuestDoodadDataManager;
typedef std::map<INT, QuestDoodadData, M_UE3_STL_ALLOC_MAP(INT, QuestDoodadData)> QuestDoodadDataMap;

// 引导任务按位枚举
enum GuideQuestType
{
	GQT_Invalid = 0,
	GQT_Friend,						// 添加好友，完成任务
	GQT_Mail,						// 发送邮件，完成任务
	GQT_Master,						// 拜师，完成任务
	GQT_Soul,						// 魂转修炼点，完成任务
	GQT_UpgradeSkill,				// 技能升级，完成任务
	GQT_Posy,						// 符文镶嵌，完成任务
	GQT_Guild,						// 创建公会，完成任务
	GQT_Team,						// 组队，完成任务
	GQT_EmbedEquip,					// 灵石镶嵌，完成任务
	GQT_PickEquip,					// 灵石摘取，完成任务
	GQT_Strong,						// 体格强化，完成任务
	GQT_Heaven,						// 装备气海，完成任务
	GQT_Appraisal,					// 鉴定装备，完成任务
	GQT_Battlefield,				// 进入竞技场，完成任务
	GQT_Extendbag,					// 扩展包裹，完成任务
	GQT_Mount,						// 装备坐骑，完成任务
	GQT_Chat,						// 发送聊天，完成任务
	GQT_UpgradeEquip,				// 装备升级，完成任务
	GQT_UseSkill,					// 使用技能，完成任务
	GQT_LearnSkill,					// 学习技能，完成任务
	GQT_GetItem,					// 获得道具，完成任务
	GQT_EquipItem,					// 装备道具，完成任务
	GQT_Compose,					// 合成道具，完成任务
	GQT_Decompose,					// 分解道具，完成任务

	GQT_EquipRemake,				// 装备重铸，完成任务
	GQT_BookRemake,					// 技能书重铸，完成任务
	GQT_Booster,					// 佣兵，完成任务
	GQT_Exercise,					// 历练，完成任务
};

// 建立怪物组->怪物表映射
typedef std::list<INT, M_UE3_STL_ALLOC(INT) > MonsterList;
typedef std::map<INT, MonsterList, M_UE3_STL_ALLOC_MAP(INT, MonsterList)> MonsterGroupMap;

class MMOQuestData : public SingletonMeyers<MMOQuestData>
{
public:
	MMOQuestData();
	virtual ~MMOQuestData();

	void Init();
	void Shutdown();
	void Clear();

	// 任务数据
	void LoadQuestDataFromUpk();
	void AddQuestData(UQuest* data);
	const class UQuest* GetQuestData(INT questId) const;
	const QuestDataMap& GetQuestDataMap() const;
	void UpdateQuestList(ROLE_DB_QUEST_DATA* questData);
	EQestState GetQuestState(INT questId);

	// 任务操作
	void AcceptQuest(INT questId);
	void AbandonQuest(INT questId);
	void CompleteQuest(INT questId);

	// 任务NPC
	EQuestHUDStatus IsNpcHasMyQuest(INT npcId, TArray<INT>* completeList,
		TArray<INT>* uncompleteList, 
		TArray<INT>* availableList);

	// 可接任务
	TArray<UQuest*> GetAvailableQuestsByType(EQUEST_TYPE type);
	INT GetAvailableQuestCount();
	bool IsQuestAvailable(INT questId);

	// 已接任务
	const AcceptedQuestDataMap& GetAcceptedQuests() const;
	TArray<UQuest*> GetAcceptedQuestsByType(EQUEST_TYPE type = E_qt_MAX);
	AcceptedQuestDataMap& GetAcceptedQuests();
	UBOOL IsQuestAccepted(INT questId) const;
	const AcceptedQuestData* GetAcceptedQuestData(INT questId) const;
	AcceptedQuestData* GetAcceptedQuestData(INT questId);

	// 完成任务		
	TArray<UQuest*> GetCompassableQuestsByType(EQUEST_TYPE type);
	TArray<UQuest*> GetCompletedQuestsByType(EQUEST_TYPE type);
	UBOOL IsQuestCompassable(INT questId) const;
	UBOOL IsQuestCompleted(INT questId) const;
	UINT32 GetCompletedQuestCount(INT questId) const;
	UINT32 GetCompletedQuestMaxCount(INT questId) const;
	INT GetCompletedQuestCount() const;
	UINT32 GetQuestCompletedDate(INT questId, 
		INT32& Year, 
		INT32& Month, 
		INT32& Day, 
		INT32& DayOfWeek, 
		INT32& Hour, 
		INT32& Min, 
		INT32& seconds) const;

	// 任务完成条件
	void UpdateQuestReachLevel(INT curLevel);
	void UpdateQuestNpcKillCount(INT questId, UINT16 index, INT val);
	void UpdateQuestDoodadKillCount(INT questId, UINT16 index, INT val);
	void UpdateQuestPlayerKillCount(INT questId, UINT16 index, INT val);
	void UpdateQuestVariable(INT questId, UINT16 index, INT val);
	void UpdateAllClientVariable(INT32 clientVariable[MAX_CLIENT_VARIABLE_COUNT]);
	void UpdateClientVariable(UINT16 index, INT val, INT classVal = 0);
	void UpdateRoleVariable(UINT16 index, INT val);
	void UpdateQuestTime(INT timeCount);

	// 任务追踪
	const QuestTraceList& GetAcceptedQuestTraceList();
	const QuestTraceList& GetAvailableQuestTraceList();
	UBOOL HasConditions(INT questId);
	void TraceAllQuest(bool traceOn);
	void TraceQuest(INT questId, bool traceOn);

	// 任务奖励
	void GetAwardItemList(INT questId, QuestAwardItemInfoList& list);
	void GetSelectableAwardItemList(INT questId, QuestAwardItemInfoList& list);
	INT GetSelectableAwardItemCount(INT questId);
	INT GetDefaultSelectableAwardItemIndex(INT questId);

	// 环任务相关
	UBOOL GetCircleQuestData(INT circleId, INT playerLevel, CircleQuestData& data);
	UBOOL GetCircleQuestRewardData(INT circleId, INT circleIndex, INT playerLevel, 
		CircleQuestRewardData& reward);
	UBOOL GetCircleQuestInfo(INT circleId, CircleQuestInfo& info) const;
	void SetNextCircleQuest(INT questId, INT circleId);
	UBOOL HasCircleQuest();
	void AddCircleQuestData(const CircleQuestData& data);
	void AddCircleQuestRewardData(const CircleQuestRewardData& data);

	// 悬赏任务
	const RewardQuestList& GetRewardQuestList() const;
	void SetRewardQuestCostCount(INT count);
	INT GetRewardQuestCostCount() { return _RewardQuestCostCount; }
	INT GetRewardQuestAvailableLimit() {return _RewardQuestFreeCount + _RewardQuestCostCount;}
	void UpdateRewardQuestList(const INT32 (&rewardQuestId)[MAX_REWARD_QUEST_COUNT_PER_ROLE]);
	INT GetAcceptedRewardQuestCount();
	INT GetTopLevelRewardQuestCount();
	INT GetRewardQuestCost(INT time);
	void AddRewardQuestCostData(const RewardQuestCostData& data);

	// 剧情任务
	UBOOL GetStoryQuestData(UINT32 chapter, UINT32 stage, StoryQuestData& data);
	const StoryQuestChapterStageMap& GetStoryQuestChapterStageMap();
	const QuestMapDataMap& GetQuestMapDataMap();
	const StoryQuestChapterList& GetStoryQuestChapterList();
	void AddStoryQuestData(const StoryQuestData& data);
	UBOOL IsStoryQuestPast(INT chapter, INT stage);

	// 道具回收
	void AddQuestRecycle(const QuestRecycleData& questRecycle);
	const QuestRecycleDataList& GetQuestRecycleList() { return _QuestRecycleDataList; }
	UBOOL IsQuestRecycle(INT questId);

	// 紧急任务
	void AddEmergencyQuestCoolDown(INT questId, INT coolDown);
	void UpdateEmergencyQuestCoolDown(INT deltaTime);
	INT GetEmergencyQuestCoolDown(INT questId) const;
	INT GetEmergencyQuestCompleteCount() { return _EmergencyQuestCompleteCount; }
	UBOOL IsEmegencyQuestAllCompleteToday();
	void AbandonAllEmergencyQuest();

	// 任务掉落
#if !SHIPPING_PC_GAME
	void GenerateQuestDoodadDropData(const TCHAR* filePath);
#endif
	void AddQuestDoodadData(const QuestDoodadData& data);
	const QuestDoodadDataMap& GetQuestDoodadDataMap() { return _QuestDoodadDataMap; }
	UBOOL IsAcceptedQuestDoodad(INT doodadDropId);

	// 杀怪任务
	UBOOL GetNormalQuestListByMonsterBeTraced(INT monsterId, QuestTraceList& questList);
	UBOOL GetEmergencyQuestListByMonsterBeTraced(INT monsterId, QuestTraceList& questList);
	UBOOL IsSingleMonsterQuest(INT questId);
	void ClearMonsterGroupData();
	void AddMonsterGroupData(INT groupId, INT monsterId);
	UBOOL GetGroupMonsterList(INT groupId, MonsterList& list);

	// 等级触发任务
	const QuestDataList& GetLevelTriggerQuestList() const;

	// 设置任务失败
	void SetQuestFailed(INT questId);

	// 
	QuestTraceList& GetReAcceptQuestList() { return _ReAcceptQuestList; }

protected:
	UBOOL _CheckQuestData();
	UBOOL _LoadQuestData(const TCHAR* filePath);
	void _UnloadQuestData();

	UBOOL _LoadCircleQuestData(const TCHAR* filePath);
	void _UnloadCircleQuestData();

	UBOOL _LoadCircleQuestRewardData(const TCHAR* filePath);
	void _UnloadCircleQuestRewardData();

	UBOOL _LoadStoryQuestData(const TCHAR* filePath);
	void _UnloadStoryQuestData();

	UBOOL _LoadQuestRecyle(const TCHAR* filePath);
	void _UnloadQuestRecyle();

	UBOOL _LoadRewardQuestCostData(const TCHAR* filePath);
	void _UnloadRewardQuestCostData();

	UBOOL _LoadQuestDoodadData(const TCHAR* filePath);
	void _UnloadQuestDoodadData();

	QuestNpcInfo* _GetOrAddQuestNpcInfo(INT npcId);
	void _InitQuestUtilData();

	void _AddAcceptedQuest(const ROLE_DB_QUEST_DATA::ROLE_DB_ACCEPTED_QUEST& questData, bool isNewQuest);
	void _RemoveAcceptedQuest(INT questId);
	
	// 可接任务限制检查
	UBOOL _CheckAvailableQuestLimit_Job(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_Sex(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_Master(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_Disciple(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_Husband(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_Wife(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_GuildLeader(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_GuildMember(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_PreQuest(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_Level(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_Reputation(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_Money(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_Date(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_Time(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_Item(const UQuest* quest, AMMOPlayer* mainPlayer) const;
	UBOOL _CheckAvailableQuestLimit_Team(const UQuest* quest, AMMOPlayer* mainPlayer) const;

	// 完成任务条件检查
	UBOOL _CheckCompleteQuestCondition_Time(const UQuest* quest, const AcceptedQuestData* data) const;
	UBOOL _CheckCompleteQuestCondition_KillMonster(const UQuest* quest, const AcceptedQuestData* data) const;
	UBOOL _CheckCompleteQuestCondition_Item(const UQuest* quest, const AcceptedQuestData* data) const;
	UBOOL _CheckCompleteQuestCondition_TalkNPC(const UQuest* quest, const AcceptedQuestData* data) const;
	UBOOL _CheckCompleteQuestCondition_Explor(const UQuest* quest, const AcceptedQuestData* data) const;
	UBOOL _CheckCompleteQuestCondition_Level(const UQuest* quest, const AcceptedQuestData* data) const;
	UBOOL _CheckCompleteQuestCondition_Variable(const UQuest* quest, const AcceptedQuestData* data) const;
	UBOOL _CheckCompleteQuestCondition_Reputation(const UQuest* quest, const AcceptedQuestData* data) const;
	UBOOL _CheckCompleteQuestCondition_Buff(const UQuest* quest, const AcceptedQuestData* data) const;
	UBOOL _CheckCompleteQuestCondition_Doodad(const UQuest* quest, const AcceptedQuestData* data) const;
	UBOOL _CheckCompleteQuestCondition_KillPlayer(const UQuest* quest, const AcceptedQuestData* data) const;

	// 道具奖励
	bool _IsItemForMe(EPlayerClass job, EGenderType gender, const UItem* item);

	// 剧情任务
	void _AddStoryQuestChapterStage(UINT32 chapter, UINT32 stage);
	void _AddStoryQuestPastChapter(UINT32 chapter);

	// 杀怪任务
	void _AddMonsterAcceptedQuest(INT monsterId, INT questId);
	void _RemoveMonsterAcceptedQuest(INT monsterId, INT questId);

	void _UpdateAcceptedQuestVariable();

protected:
	QuestDataMap _QuestDataMap;

	UINT8 _NormalQuest[MAX_NORMAL_QUEST_COUNT / 8];
	UINT8 _RepeatQuest[MAX_REPEAT_QUEST_COUNT];
	UINT32 _RepeatQuestScanTime;

	AcceptedQuestDataMap _AcceptedQuestDataMap;

	QuestTraceList _AcceptedQuestTraceList;
	QuestTraceList _AvailableQuestTraceList;

	QuestNpcInfoMap _QuestNpcInfoMap;

	CircleQuestDataMap _CircleQuestDataMap;
	CircleQuestRewardDataMap _CircleQuestRewardDataMap;
	CircleQuestInfoMap _CircleQuestInfoMap;

	// 悬赏任务
	RewardQuestList _RewardQuestList;
	INT _RewardQuestFreeCount;
	INT _RewardQuestCostCount;
	RewardQuestCostDataMap _RewardQuestCostDataMap;

	// 剧情任务
	StoryQuestDataMap _StoryQuestDataMap;
	StoryQuestChapterStageMap _StoryQuestChapterStageMap;
	StoryQuestChapterList _StoryQuestPastChapterList;

	// 任务地图
	QuestMapDataMap _QuestMapDataMap;

	// 任务回收
	QuestRecycleDataList _QuestRecycleDataList;

	// 紧急任务
	EmergencyQuestCoolDownMap _EmergencyQuestCoolDownMap;				// 已接紧急任务信息		

	// 杀怪任务
	MonsterAcceptedQuestsMap _MonsterAcceptedNormalMap;
	MonsterAcceptedQuestsMap _MonsterAcceptedEmergencyMap;

	// 任务掉落
	QuestDoodadDataMap _QuestDoodadDataMap;

	// 等级达到触发任务
	QuestDataList _LevelTriggerQuestList;

	// 紧急任务
	INT _EmergencyQuestCompleteCount;

	MonsterGroupMap _MonsterGroupMap;

	// 需要重新接取的主线任务
	QuestTraceList _ReAcceptQuestList;
};

#endif
