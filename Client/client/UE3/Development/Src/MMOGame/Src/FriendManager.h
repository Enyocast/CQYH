
#ifndef _FriendManager_H_
#define _FriendManager_H_

#include "MMOSingleton.h"
#include "MMOGameUIClasses.h"

struct MMOFriendMember
{
	MMOFriendMember(EEventParm)
	{
		appMemzero(this, sizeof(MMOFriendMember));
	}
	MMOFriendMember()
	{
		//appMemzero(this, sizeof(MMOFriendMember));
		RoleId = 0;
		Lv = 0;
		ClassId = 0;
		Sex = 0;
		Online = 0;
		nIntimacy = 0;
		SceneTempID = -1;
	}
	INT RoleId;
	INT Lv;
	FString ActorName;
	INT ClassId;	
	INT Sex;
	INT Online;
	FString Location;
	FString Sign;
	FString AbbName;//名字缩写
	INT32 nIntimacy; //好友度
	UINT8 SceneTempID;
};

struct MMOFriendGroup
{
	TArray<MMOFriendMember> FriendList;
	FString GroupName;
	UBOOL IsDefault;
};

struct MMOKillInfo
{
	INT Time;
	INT RoleId;
	UBOOL Killed;
	FString ShowText;
};

#define FriendGroupNum 10
#define AttentionGroupId 10
#define DefaultFriendGroupId 0
#define BlackGroupId 2000
#define EnemyGroupId 3000
#define NearGroupId 1000

class FriendManager : public SingletonMeyers<FriendManager>, public INativeGameEventHandler
{
public:

	FriendManager();
	virtual ~FriendManager(){Shutdown();}

	void Init();
	void Shutdown();

	
	
	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
	TArray<MMOFriendMember> EnemyList;
	
	TArray<MMOFriendMember> NearContactList;

	void ClearAll();

	INT GetFriendGroupId ( INT roleId );
	MMOFriendMember GetFriendInfoByRoleId( INT roleId );	
	MMOFriendMember* GetFriendGroupMember( INT groupId , INT pos );//用指针，避免找不到
	MMOFriendMember* GetFriendGroupMemberById( INT groupId , INT id );//用指针，避免找不到
	MMOFriendMember* GetNearContact( INT pos );//用指针，避免找不到
	MMOFriendMember* GetBlacklistMember( INT pos );
	MMOFriendMember* GetEnemylistMember( INT pos );
	MMOFriendMember* GetBlackMemberByRoleId( INT roleId );
	MMOFriendMember* GetEnemyMemberByRoleId( INT roleId );
	MMOFriendMember* GetNearMemberByRoleId( INT roleId );
	
	MMOFriendGroup* GetFriendGroup( INT groupId );
	INT GetFriendGroupNum(){ return FriendGroupList.Num(); }
	INT GetFriendNumInGroup( INT groupId );//一组里的好友数
	INT GetTotalFriendNum( );//一一共的好友数
	INT GetOnlineFriendNumInGroup( INT groupId );//一组里的在线好友数
	INT GetEmptyFriendGroupId();

	void ChangeFriendGroup(INT RoleId,INT GroupId);
	void RequestAddAttention( INT RoleId , const FString& TargetName );
	void RequestDelAttention( INT RoleId );

	void AddNewFriend( INT roleId , FString friendName , INT groupId );
	void PushToFriendGroup( INT groupId , MMOFriendMember member );
	void AddNewEnemy(MMOFriendMember& member);

	UBOOL IsMyFriend( INT roleId );
	UBOOL IsMyAttention( INT roleId );
	UBOOL InMyBlackList( INT roleId );
	UBOOL InMyEnemyList( INT roleId );

	MMOFriendMember* GetAttentionInfo(INT roleId);
	MMOFriendMember* GetMyFriendInfo(INT roleId);
	
	void NotifyNewContact( INT roleId );
	
	void MoveGroupPlayerToGroup( INT fromGroupId  , INT toGroupId );//改变一组人的组
	void MovePlayerToGroup( INT roleId , INT fromGroupId  , INT toGroupId ); //改变组 
	void DeleteAttention( INT roleId ); //取消关注

	void SaveNearContact();
	void LoadNearContact();

	void RemoveEnemy( INT roleId );
	MMOFriendMember* GetSearchList(){ return SearchList; }
	MMOFriendMember* GetSearchFriend( INT pos );
	void ClearSearchList();

	void AddedAttentionBy(INT RoleId,const FString& RoleName);
	void AddFriendOk( UGFxObject* mc );

	void AddBlackList( MMOFriendMember member );
	INT GetBlackNum();
	TArray<MMOFriendMember>& GetBlackList();

	void SortFriendGroup( INT groupId );
	void SortAllFriend();

	void DeleteFriendGroup( INT groupId );

	//添加杀人信息
	void AddKillInfoList( UBOOL iamKiller , INT killerRoleID , INT victimRoleID );
	//添加掉落信息
	void AddKilledDropItem( UItem* titem , FClientItemInfo* clientItem );
	TArray<MMOKillInfo>& GetKillInfoList() { return KillInfoList; }
	void SaveKillInfoData();
	void LoadKillInfoData();

	void TickTime( FLOAT deltaTime );

	//摆摊需求
	void  UpdateFriendMemberInfo(MMOFriendMember &FriendInfo,INT nRoleID);

	//商城需要一个全部好友数据接口
	const TArray<MMOFriendGroup>& GetAllFriendList()const;

	//最近联系人里删除
	void removeFromNerContactList(int roleId);
	void UpdateNerContactListMember(MMOFriendMember* mem);

	//好友度发生变化
	void UpdateFriendIntimacy(UINT32 roleId,INT32 nIntimacy);

	INT GetPlayerIntimacy(UINT32 roldId);
	INT GetNeedIntimacyValue(){return nTradeNeedIntimacyValue;}
	BOOL CheckIntimacy(UINT32 roleId);

protected:

	TArray<MMOFriendGroup> FriendGroupList;
	TArray<MMOFriendMember> BlackList;

	MMOFriendMember SearchList[UCONST_MaxSearchPanelItem];
	TArray<MMOKillInfo> KillInfoList;

	TArray<MMOKillInfo> KillInfoListBuff;

	FString _GetCurTimeString();
	void _GetCurMapString( FString& mapString , FString& mapIcon );
	
	UBOOL startTick;
	FLOAT startTime;

	FString killTime;

	INT nTradeNeedIntimacyValue;
};



#endif