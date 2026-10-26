#ifndef _UBATTLEMANAGER_H_
#define _UBATTLEMANAGER_H_

#include "MMOSingleton.h"
#include "MMOGameEvent.h"
#include "MMOGameUIClasses.h"

namespace ExternalMessage
{
    struct G2C_SYNC_COMBAT_STAT;
}

#define RANDOM_BATTLE_ID 0
static UINT MAX_SEND_QUERY_PLAYER_INFO_CNT = 15;
enum eBattlePlayerState
{
	EBPS_OFFLINE,
	EBPS_ALIVE,
	EBPS_DEAD,
};

enum eBattleState
{
	EBTLS_NONE,
	EBTLS_QUEUEING,
	EBTLS_INQUIRING_ENTER,
	EBTLS_BEGINING,
	EBTLS_FIGHTING,
	EBTLS_ENDING
};

//战场个人得分
struct FBattlePlayerScore
{	//个人战场获得的分数，分数含义根据不同战场而不同
	INT	_Sum;

	INT _Kills;
	INT _BeKilled;

	INT _Damages;
	INT _Heals;
};

//战场个人奖励
struct FBattlePlayerAwards
{
	INT _Points;
};

//战场玩家
struct FBattlePlayer
{
	INT			_ID;

	INT			_Sex;
	INT			_ClassID;
	INT			_Lv;

	FBattlePlayerScore	_Score;
	FBattlePlayerAwards _Awards;

	FString		_ServerName;
	FString		_PlayerName;

	eBattlePlayerState	_State;
	bool				_IsLeader;
	//0为己方
	BYTE				_BtlTeamID;
};

//class MMOBattleManager : public Singleton<MMOBattleManager>
class MMOBattleManager : public SingletonMeyers<MMOBattleManager>, public INativeGameEventHandler
{
public:
	MMOBattleManager(void);
	virtual ~MMOBattleManager(void);

	//void Init( UMMOBattleTemplate* pBattle );
	void Init();
	void Shutdown();
	void ResetRandomBattleData();
	void TestAddData();

public:
	typedef TMap< INT, FBattlePlayer > BattlePlayerMap;
	typedef BattlePlayerMap::TIterator BattlePlayerIterator;

public:
	void RandomJoinBattle();
	//void TeamJoinBattle( INT battleID );
	//void SingleJoinBattle( INT battleID );
	void JoinSingleBattle( INT battleID );
	//void QuickJoinBattle( UINT battleID );
	void LeaveWaitingBattle();
	void ConfirmJoinBattle( UBOOL isAgree );

public:
	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
	void NotifyPlayerBaseInfo( UINT32 roleID );
	void NotifyJoinedBattle();
	void NotifyLeaveBattle();
	void NotifyEnterBattle( INT battleID );
	void NotifyBattleEnd( UBOOL isDogFall, INT winTeamID );
	void ParseBattleCombatDatas( ExternalMessage::G2C_SYNC_COMBAT_STAT* serverMsg, UINT dataCnt );

public:
	void ResetJoinedBattleData();
	void ResetEnteredBattle();

	void ClearBattlePlayer(){ _BattlePlayerList.Empty(); }
	void DelPlayer( INT playerID );
	FBattlePlayer *GetOrAddPlayer( INT playerID ){
		return &_BattlePlayerList.FindOrAdd( playerID );
	}
	const FBattlePlayer *GetPlayer( INT playerID );
	BattlePlayerIterator BeginIterateBattlePlayer();

	void SortedPlayersByPointsInTeam();
	void SortedPlayersByScore();
	void SortedPlayersByKills();
	void SortedPlayersByBeKilled();

	TMap< UINT, UBOOL > &GetRoleIncompleteList(){
		return _RoleInfoIncompleteList;
	}
	//战场信息
	//void AddBattleTemplate( FBattleTemplate* battle );
	//void ClearBattleTemplates();
	INT GetBattleTemplateCnt();
	FBattleTemplate* FindBattleTemplateBy( INT battleID );
	FBattleTemplate* GetBattleTemplateIn( INT idx );
	INT GetBattleIdxByID( INT battleID );
	//FBattleTemplate* CurBattleTemplate( INT battleID );

	FBattleTemplate* GetRandomBattle(){ return &_BattlesInfo->RandomBattle; }
	INT GetRandomCur(){ return _RandomBattlesList.Num(); }
	INT GetRandomMin(){ return _BattlesInfo->RandomBattleMinSlt; }
	INT GetRandomMax(){ return _BattlesInfo->RandomBattleMaxSlt; }
	INT GetRandomMinLv(){ return _BattlesInfo->RandomBattleMinLv; }

	eBattlePlayerState CvtToBattleState( INT iState );
	
	INT GetCurBattleSidesCnt();
	//战场状态
	eBattleState GetCurBattleState(){ return _BattleState; }
	UBOOL IsWaiting(){ return (_BattleState == EBTLS_QUEUEING) ? TRUE : FALSE; }
	void SetWaiting( UBOOL isW ){ _BattleState = ( (isW == TRUE) ? EBTLS_QUEUEING : _BattleState ); }
	UBOOL IsInBattle();
	UBOOL IsBattleEnding(){ return (_BattleState == EBTLS_ENDING) ? TRUE : FALSE; }
	void SetBattleState( eBattleState state ){ _BattleState = state; }
	//战场得分
	void SetBattleTeamScore( INT btlTeamID, INT score ){
			_BattleTeamScore.FindOrAdd( btlTeamID ) = score;
	}
	INT GetBattleTeamScore( INT btlTeamID ){
		if( _BattleTeamScore.Find( btlTeamID ) != NULL )
			return _BattleTeamScore.FindOrAdd( btlTeamID );
		return -1;
	}
	//
	const FBattlePlayer *GetMyBattleScoreInfo();
	//
	INT GetWinTeamID();

	//当前正加入的战场
	INT GetJoinedBattleID(){ return _JoinedBattleID; }
	void SetJoinedBattleID( INT id ){ _JoinedBattleID = id; }
	//当然已进入的战场
	FExportMap *GetEnteredBattleMapData();
	FBattleTemplate* GetEnteredBattle();
	void SetEnteredBattleID( INT id ){ _EnteredBattleID = id; }

	void ToggleRandomBattles( INT id, UBOOL isChoosed );
	//加入时间
	_SYSTEMTIME GetJoinedBattleTime(){
		return _JoinLocalTime;
	}
	//开始时间
	INT GetTimeSinceBattleBegin();
	UINT32 GetBattleStartTime(){ return _BattleStartUtcTime; }
	void SetBattleStartTime( UINT32 startTime, int modifySec ){ _BattleStartUtcTime = startTime + modifySec; }
	//
	UBOOL IsBattleBegin(){ return _IsBattleBegin; }
	void SetBattleBegin( UBOOL is ){ _IsBattleBegin = is; }
private:
	//信息还不完整的玩家ID
	TMap< UINT, UBOOL > _RoleInfoIncompleteList;
	TMap< UINT, UBOOL > _RoleInfoIncompleteListUnSended;
	//战场人员
	//std::map< INT, FBattlePlayer > BattlePlayerList;
	BattlePlayerMap _BattlePlayerList;

	//战场信息
	UMMOBattleTemplate *_BattlesInfo;
	//能使用的战场
	TArray< UINT > _ActivedBattles;

	//申请加入的战场ID,申请时0表示随机战场
	INT _PrepareJoinedBtlID;
	//所有随机战场列表
	typedef TMap< INT, INT > RandomBattleMap;
	RandomBattleMap  _RandomBattlesList;
	//当前战场ID(已申请)
	INT _JoinedBattleID;
	//当前战场ID(已在的)
	INT _EnteredBattleID;
	//是否等待加入战场中
	eBattleState _BattleState;
	//加入战场队列的时间
	_SYSTEMTIME _JoinLocalTime;
	//战场开始时间
	UINT32 _BattleStartUtcTime;
	UBOOL _IsBattleBegin;
	//战场分数统计
	//static const INT MAX_BATTLE_TEAM = 3;
	TMap<INT,INT> _BattleTeamScore;
	//胜利的队伍
	INT _WinTeamID;
	//战场结果
	UBOOL _IsDogfall;
};


#endif