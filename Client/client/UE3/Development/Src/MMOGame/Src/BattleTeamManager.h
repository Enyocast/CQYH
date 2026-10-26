
#ifndef _BATTLETEAMMANAGER_H_
#define _BATTLETEAMMANAGER_H_

#include "MMOSingleton.h"
#include "net/message_handler.h"

struct BattleTeamMember
{
	INT ServerID;
	FString PlayerName;
	INT	ClassID;
	INT Sex;
	INT SingleScore;
	INT TeamScore;
	INT Level;
};

struct BattleTeamAchievement
{
	INT Score;
	INT Rank;
	INT Match;
	INT WinRate;
	INT Win;
};

struct MMOGameEvent_BattleTeam : public MMOGameEvent
{
public:
	enum EBattleTeamEventType
	{
		EBET_UpdateMemberList,
		EBET_InviteEnterTeam,
		EBET_TurnTab,
	};

	MMOGameEvent_BattleTeam(EBattleTeamEventType evtType)
		: EvtType(evtType)
		, roleID(0)
		, tab(0)
		, roleName(TEXT(""))
	{
	}

	virtual EGameEvent GetEventType() const
	{
		return GameEvent_BattleTeam;
	}

	EBattleTeamEventType EvtType;
	INT tab;
	INT roleID;
	FString roleName;
};



//class BattleTeamManager : public SingletonMeyers<BattleTeamManager>, public INativeGameEventHandler
//{
//public:
//
//	BattleTeamManager();
//	virtual ~BattleTeamManager();
//
//	void Init();
//	void Shutdown();
//
//	void TestAddNewMember( INT roleID , const FString& roleName );
//
//	void CreateMyBattleTeam( INT teamID );
//	void ClearMyTeam();
//	void LeaveBattleTeam( INT roleID );
//	void SetTeamInfo( M2C_ARENA_TEAM_INFO* msg );
//	void InviteEnterTeam( INT roleId , const FString& roleName );
//	void AcceptJoinBattleTeam( UGFxObject* mc );
//	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
//		
//	
//
//	const TArray<BattleTeamMember>& GetMemberList(){ return _MemberList;}
//	const BattleTeamAchievement* GetAchievementTable( INT size ){ if( size < 0 || size >= atptTotal ) { return NULL; } return &_AchievementTable[size]; }
//	BattleTeamMember* GetMemberByRoleId( INT roleId );
//
//	UBOOL HasTeam(){ return _HasTeam; }
//	INT	 GetTeamID() { return _TeamID;}
//	INT	 GetTeamLeadID() { return _TeamLeaderID;}
//	UBOOL IsTeamLeader();
//	UBOOL HasMember( INT serveID );
//	const FString& GetTeamName(){return _TeamName;}
//
//protected:
//
//	void NotifyBattleTeam();
//	
//	TArray<BattleTeamMember>	_MemberList;	
//	BattleTeamAchievement		_AchievementTable[atptTotal];
//
//	UBOOL	_HasTeam;
//	INT		_TeamLeaderID;
//	INT		_TeamID;
//	FString	_TeamName;
//	INT		_IconID;
//
//};

#endif