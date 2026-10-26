#ifndef _ACTIVITY_MANAGER_H_
#define _ACTIVITY_MANAGER_H_

#include "MMOGameEvent.h"
#include "common.h"
#include "MMOUtil.h"
#include <time.h>
#include "TeamManager.h"
#include "MMODataManager.h"

//活动类型
enum
{
	EActivityHot	 = 0,	
	EActivityOutHome = 1,
	EActivityCopy    = 2,

	ERewardType_Money    = 1,
	ERewardType_Exp      = 2,
	ERewardType_Treasure = 4,

};

enum EActivityState
{
	ENOStart,
	EWillStart,
	EStarting,
	EActivityOver,
};

// 完成度显示类型
enum EActivityCompleteType
{
	EACPT_None = 0,				// 无法知道是否参与
	EACPT_Quest,				// 任务完成，活动完成
	EACPT_Time,					// 时间结束，活动完成
	EACPT_SignIn,				// 每日签到，活动完成
	EACPT_Variable,				// 角色变量达到指定值，活动完成
};

// 活动系统变量
enum EActivityRoleVariable
{
	EARV_ID_1 = 193,			// 角色变量ID:公会祈祷次数
	EARV_ID_2 = 213,			// 角色变量ID:公会据点战状态
	EARV_ID_3 = 214,			// 角色变量ID:幽冥海进入次数
	EARV_ID_4 = 216,			// 角色变量ID:幽冥海上次进入时间
	EARV_ID_5 = 217,			// 角色变量ID:公会祈祷上次时间
	EARV_ID_6 = 218,			// 角色变量ID:九层妖塔上次进入时间
	EARV_ID_7 = 219,			// 角色变量ID:皇室宝库上次进入时间
	EARV_ID_8 = 220,			// 角色变量ID:经验武斗场上次进入时间
	EARV_ID_9 = 195,			// 角色变量ID:演武场进入次数
	EARV_ID_10 = 179,           // 角色变量ID:角色上次做公会行商时间
	EARV_ID_11 = 187,           // 角色变量ID:角色每日泡过温泉的时间
	EARV_ID_12 = 226,			// 角色变量ID:演武场每日计数时间
};

//活动时间
struct ActivityTime
{
	INT				nStartTime_year;
	INT				nStartTime_month;
	INT				nStartTime_day;
	INT				nStartTime_weekDay;
	INT				nStartTime_hour;
	INT				nStartTime_minute;
	INT				nEndTime_year;
	INT				nEndTime_month;
	INT				nEndTime_day;
	INT				nEndTime_weekDay;
	INT				nEndTime_hour;
	INT				nEndTime_minute;

	FString			sTimeStr;
	EActivityState  nState;
	time_t			startT;
	EActivityState	GetState();
	bool  CompareValue(const ActivityTime& rightVal)const
	{
		return rightVal.startT < startT;
	}
};

struct RewardBarItem
{
	INT nID;
	INT nVitality;			//累计活跃度
	INT nRewardItemID;
	INT nRewardItemCount;
	INT nBoxLevel;
};

//活动奖励
struct ActivityReward
{
	INT				nRewardType;			//1是金钱 2是经验 4是寻宝 金钱经验组合的是1+2等等1+4 2+4 1+2+4组合
	INT				nRewardVitality;		//活跃度奖励
	INT				nArrItemID[10];
};

//活动基本数据
struct ActivityData
{
	INT						nVipLevel;				//是否是VIP活动
	INT						nActivityID;			//活动ID
	INT						nLinkQuestType;			//关联任务类型
	INT						nLinkQuestID;			//关联任务ID
	INT						nCheckLevelMin;			//等级限制下限
	INT						nCheckLevelMax;			//等级限制上限
	INT						nHotStarNum;			//推荐星数
	INT						nPersonNumMin;			//参与人数下限
	INT						nPersonNumMax;			//参与人数上限
	INT						nHaveDoneTimes;			//已经完成的次数
	INT						nPerDayJoinNum;			//每天参与的次数
	INT                     nCompleteType;			//完成活动的类型
	INT                     nCompleteMap;			//完成活动的地图
	TArray<UINT32>			aTimeLimit;				//活动限制
	INT                     nGuildActivityType;		//工会活动类型
	INT                     nRoleVariable;			//活动角色变量

	INT						nActivityType;
	ActivityTime			nTimeInfo;
	ActivityReward			nRewardInfo;
		
	TArray<FString>			sNpcName;
	TArray<INT>				nAcceptNpcID;
	TArray<INT>				ndestMapID;

	FString					sLevelString;
	FString					sPersonString;
	FString					sActivityName;
	FString					sDecrible;

	ActivityData()
	{
		appMemzero(this, sizeof(ActivityData));
	}
};
//活动配置表读取
struct ActivityDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("Activity.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}

	static ActivityData* CreateDataObject(INT templateID, bool& needAddToMap);

	static void DestroyDataObject(ActivityData* obj);

	static void ParseData(ActivityData* obj, class CTabFile* dataRow, int rowIdx);


	static FString GetTemplateIDName()
	{
		return TEXT("activityID");
	}

	static FString FormatAsString(ActivityData* obj)
	{
		return "";
	}

	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(ActivityData* obj, TSet<FString>& outResList)
	{
		//_CollectReferencedResource(obj, outResList);
	}
#endif
};
typedef TDataManger< ActivityData, ActivityDataProcessor >   MMOActivityDataManager;

//活跃度奖励配置读取
struct ActivityRewardBarDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("activity_reward.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}

	static RewardBarItem* CreateDataObject(INT templateID, bool& needAddToMap);

	static void DestroyDataObject(RewardBarItem* obj);

	static void ParseData(RewardBarItem* obj, class CTabFile* dataRow, int rowIdx);


	static FString GetTemplateIDName()
	{
		return TEXT("ID");
	}

	static FString FormatAsString(RewardBarItem* obj)
	{
		return "";
	}

	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(RewardBarItem* obj, TSet<FString>& outResList)
	{
		//_CollectReferencedResource(obj, outResList);
	}
#endif
};
typedef TDataManger< RewardBarItem, ActivityRewardBarDataProcessor >   MMOActivityRewardBarDataManager;

//副本列表基本数据
struct FBActivityData
{
	INT						nFBID;					//活动ID
	INT						nFBType;
	INT						nCheckLevelMin;			//等级限制下限
	INT						nCheckLevelMax;			//等级限制上限
	INT						nPersonNumMin;			//参与人数下限
	INT						nPersonNumMax;			//参与人数上限
	INT						nHaveDoneTimes;			//已经完成的次数
	INT						nPerDayJoinNum;			//每天参与的次数
	INT						nAcceptNpcID;
	INT						ndestMapID;
	INT						nPosX;
	INT						nPosY;
	INT						nPosZ;
	INT						nFBCostActiveValue;		//副本消耗
	INT						nFBDifficulty;			//副本难度
	ActivityTime			nTimeInfo;
	ActivityReward			nRewardInfo;
	FString					sDifficultyString;
//		FString					sPosName;
	FString					sLevelString;
	FString					sPersonString;
	FString					sFBName;
	FString					sDecrible;

	FBActivityData()
	{
		appMemzero(this, sizeof(FBActivityData));
	}
};

//活动/副本目标表
struct ActivityTarget
{
	FString sName;     //名称
	INT sType;         //类型
	INT sDifficulty;   //难度
	INT sLevel;        //等级
	INT sBossCount;    //boss数量
	INT sConsume;      //消耗活力值
	INT sAchieve;      //获取的活跃度
	INT sRecommend;    //推荐人数
};

struct ActivityTeam
{
public:
	INT TeamId;
	INT LeaderId;
	FString Name;
	INT Level;
	INT PlayerCount;
	INT MaxPlayerCount;
	INT MemberId[MAX_TEAM_MEMBER_COUNT];

	ActivityTeam()
	{
		Clear();
	}

	~ActivityTeam()
	{
		Clear();
	}

	void Clear()
	{
			//memset(this, 0, sizeof(ActivityTeam));
		TeamId = 0;
		LeaderId = 0;
		Name = TEXT("");
		Level = 0;
		PlayerCount = 0;
		MaxPlayerCount = 0;
	}
};


struct ActivityTeamMember
{
	INT PlayerId;
	FString Name;
	INT Vitality;
	INT ActivityTimes;
	INT MaxActivityTimes;
	INT ClassId;
	INT Level;
};


// 活动配置表		
typedef std::list<ActivityData, M_UE3_STL_ALLOC(ActivityData) >		ActivityDataList;
typedef std::list<FBActivityData, M_UE3_STL_ALLOC(FBActivityData) > FBActivityDataList;
typedef std::list<RewardBarItem, M_UE3_STL_ALLOC(RewardBarItem) >	RewardBarDataList;

typedef std::list<ActivityTarget, M_UE3_STL_ALLOC(ActivityTarget) > ActivityTargetList;
typedef TArray<ActivityTeamMember> ActivityTeamMemberList;
typedef TArray<ActivityTeam> ActivityTeamList;
typedef std::map<INT, ActivityTeamMemberList, M_UE3_STL_ALLOC_MAP(INT, ActivityTeamMemberList) > TeamMemberListMap;
typedef std::map<INT, ActivityTeamList, M_UE3_STL_ALLOC_MAP(INT, ActivityTeamList) > ActivityTeamListMap;

typedef std::map<UINT16, INT32, M_UE3_STL_ALLOC_MAP(UINT16, INT32)> ActivityVariableMap;

// 活动事件
struct MMOGameEvent_Activity : public MMOGameEvent
{
public:
	enum EActivityEventType
	{
		EActivity_UpdateState,
		EActivity_UpdateActivityTeamList,
		EActivity_ForceRequireActivityTeam,
	};

	MMOGameEvent_Activity(EActivityEventType eventType, INT activityId = -1)
		: EventType(eventType)
		, nActivityID(activityId)
	{
	}

	virtual EGameEvent GetEventType() const
	{
		return GameEvent_Activity;
	}

	EActivityEventType  EventType;
	INT					nActivityID;
};

// 活动管理类
class ActivityManager : public SingletonMeyers<ActivityManager>, public INativeGameEventHandler
{
public:
	ActivityManager();
	virtual ~ActivityManager();

	enum EActivityHeadTypeSort
	{
		//活动的排序
		EActivitySortHead_Name,
		EActivitySortHead_Time,
		EActivitySortHead_PersonNum,
		EActivitySortHead_Reward,
		EActivitySortHead_State,
		EActivitySortHead_CompleteStatus,
		EActivitySortHead_Star,

		//副本的排序
		EFBSortHead_Level,
		EFBSortHead_CostActiveValue,

	};
	void Init();
	void Shutdown();
	void Clear();
	void Update(FLOAT deltaTime);

	// 活动状态更新事件
	virtual void				OnNativeGameEvent(struct MMOGameEvent* evt);
	// 活动数据
	void						AddActivityData(ActivityData& data);
	void						AddActivityRewardBarData(RewardBarItem& data);
	const ActivityData*			GetActivityData(INT activityId) const;
	const FBActivityData*		GetFBActivityData(INT FBId) const;
	const ActivityDataList&		GetActivityDataList() const;
	const ActivityDataList&		GetCompleteActivityDataList() const;
	const FBActivityDataList&	GetFBActivityDataList() const;
	const RewardBarItem*		GetRewardBarCondition(INT nIndex)const;
	const ActivityTeam*			GetRandTeamCurActivity() const;
	UBOOL						IsActivity(INT questId);
	INT							GetActivityVipLevel(INT questId);

	// 活动需要判断的属性
	INT							 GetActivityAcceptMaxTimes(INT activityId);
	INT							 GetMaxActiveValue();
	void						 FilterTodayActivity();

	// 获得当前活跃度
	INT32   GetActiveValue();
	INT 	GetRewardState(INT nIndex);
	INT		GetCurActivityId();
	INT		GetCurActivityTeamPage();
	INT		GetSelectedActivityTeam();
	INT		GetActivityFilterType();
	INT		GetActivityTipsTeamId();
	INT		GetActivityTeamLevel(INT nTeamId);
	ActivityTeam* GetActivityTeamById(INT TeamId);
	void	SetCurActivityId(INT nActivityId);
	void	SetCurActivityTeamPage(INT nPage);
	void	SetSelectedActivityTeam(INT nIndex);
	void	UpdateActivityTeamList(const char* buf);
	void	ClearActivityTeamList();

	void FilterActivityType(INT nActivityType,INT nRewardType);
	void SortActivityList(INT nType,INT nAdd);
	void SortTodayActivityList(INT nType,INT nAdd);
	void SetActivityList(UMMOGFXPlayer* gfxPlayer, UGFxObject* dataProvider);
	void SetActivityDetailInfo(UMMOGFXPlayer* gfxPlayer, UGFxObject* object, INT nActivityID);
	void SetActivityTeamMemberInfo(UMMOGFXPlayer* gfxPlayer, UGFxObject* object, INT nTeamID);
	void SetActivityTeamInfo(UMMOGFXPlayer* gfxPlayer, UGFxObject* object, INT nActivityID, INT nPage);
	void SetActivityInviteList(UMMOGFXPlayer* gfxPlayer, UGFxObject* object, INT nType, UBOOL bActivity);
	void SetFBDetailInfo(UMMOGFXPlayer* gfxPlayer, UGFxObject* object, INT nFBID);
	void SetQuitHintActivityList(UMMOGFXPlayer* gfxPlayer,UGFxObject* object);
	void SetRewardBarInfo(UMMOGFXPlayer* gfxPlayer,UGFxObject* object);

	void NotifyActivityVariableErvtActivity(INT32 nValue);
	void NotifyActivityVariableErvtActivityReward(INT32 nValue);
	void NotifyActivityVariableErvtQuestComNum(INT32 nValue);

	INT32 GetRewardBit() { return _RewardBit; }

protected:
	void _UnloadActivityData();
	void _LoadFBData();

	void SetActivityDataList(UMMOGFXPlayer* gfxPlayer, UGFxObject* dataProvider);
	void SetFBActivityDataList(UMMOGFXPlayer* gfxPlayer, UGFxObject* dataProvider);

	void ClearActivityDetailInfo(UMMOGFXPlayer* gfxPlayer, UGFxObject* object);
	void ClearFBDetailInfo(UMMOGFXPlayer* gfxPlayer, UGFxObject* object);
	void SortActivityDataList(INT nType,INT nAdd);
	void SortFBActivityDataList(INT nType,INT nAdd);
	static bool CompareAdd_StartTime(const ActivityData& leftData, const ActivityData& rightData);
	static bool CompareAdd_Reward(const ActivityData& leftData, const ActivityData& rightData);
	static bool CompareAdd_PersonNum(const ActivityData& leftData, const ActivityData& rightData);
	static bool CompareDec_StartTime(const ActivityData& leftData, const ActivityData& rightData);
	static bool CompareDec_Reward(const ActivityData& leftData, const ActivityData& rightData);
	static bool CompareDec_PersonNum(const ActivityData& leftData, const ActivityData& rightData);

	static bool CompareAdd_State(const ActivityData& leftData, const ActivityData& rightData);
	static bool CompareDec_State(const ActivityData& leftData, const ActivityData& rightData);
	static bool CompareAdd_CompleteState(const ActivityData& leftData, const ActivityData& rightData);
	static bool CompareDec_CompleteState(const ActivityData& leftData, const ActivityData& rightData);

	static bool CompareAdd_StarNum(const ActivityData& leftData, const ActivityData& rightData);
	static bool CompareDec_StarNum(const ActivityData& leftData, const ActivityData& rightData);

	static bool CompareAdd_Level(const ActivityData& leftData, const ActivityData& rightData);
	static bool CompareDec_Level(const ActivityData& leftData, const ActivityData& rightData);

	static bool FBCompareAdd_CostActiveValue(const FBActivityData& leftData, const FBActivityData& rightData);
	static bool FBCompareDec_CostActiveValue(const FBActivityData& leftData, const FBActivityData& rightData);
	
	static bool FBCompareAdd_Dificulty(const FBActivityData& leftData, const FBActivityData& rightData);
	static bool FBCompareDec_Dificulty(const FBActivityData& leftData, const FBActivityData& rightData);

	static bool FBCompareAdd_Level(const FBActivityData& leftData, const FBActivityData& rightData);
	static bool FBCompareDec_Level(const FBActivityData& leftData, const FBActivityData& rightData);

	static bool FBCompareAdd_PersonNum(const FBActivityData& leftData, const FBActivityData& rightData);
	static bool FBCompareDec_PersonNum(const FBActivityData& leftData, const FBActivityData& rightData);

	void _GetActivityStateString(EActivityState eState, FString& stateString);
	void _GetGuildActivityTimeString(UINT16 activityType, FString& timeString);
	void _GetGuildActivityStateString(UINT16 activityType, FString& stateString);
	void _ClearVariable();
	void _UpdateVariable(UINT8 varType, INT32 referId, UINT16 index, INT32 val);
	INT32 _GetVariableValue(UINT8 varType, UINT16 index);
	INT32 _GetVariableCompleteCount(UINT8 varType, UINT16 index);

protected:
	RewardBarDataList _RewardBarDataList;
	//whole activity datalist
	ActivityDataList	_ActivityDataList;
	FBActivityDataList  _FBDataList;
	//showing datalist
	ActivityDataList _ActivityCurShowDataList;
	//today quit hint activity
	ActivityDataList _QuitTodayActivityList;

	TeamMemberListMap  _TeamMemberListCache;
	//ActivityTeamListMap _ActivityTeamListCache;
	ActivityTeamList	_ActivityTeamListData;

	ActivityVariableMap _ActivityVariableMap;

	//活跃度
	INT32			 _ActiveValue;
	INT32			 _RewardQuestComNum;
	INT32			 _RewardBit;
	INT				 _CurShowType;
	INT				 _MaxActiveValue;

	INT				_CurActivityId;
	INT				_CurActivityTeamPage;
	INT				_CurActivityTeamIndex;
	INT				_CurActivityTipsTeamId;
};

#endif
