
enum DataType
{
	DT_FriendNear,
	DT_FriendList,
	DT_BlackList,
	DT_EnemyList,

};

virtual void Init();
virtual void UnInit();

virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateSearchList( TArray< struct MMOFriendMember>& searchList );
void FillInSearchPanel();
void SetFriendItemValue( INT groupId , INT pos , struct MMOFriendMember* member );
void SetEnemyItemValue( INT pos , struct MMOFriendMember* member );
void SetBlackItemValue( INT pos , struct MMOFriendMember* member );

void FriendOverItem( INT groupId , INT index );
void SearchFocusChange( UBOOL in , FString text );
void UpdateKillInfo();
void UpdateTime(FLOAT dt);

void UpdateDateList(DataType type,int groupId = 0);

void UpdateAllFriend();


