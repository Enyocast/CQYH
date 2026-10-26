
virtual void Init();
virtual void UnInit();
//virtual void PostOnShow(UBOOL v);

virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void AuctionBid( INT bidMoney );
//void AuctionGiveupCurItem();
void AuctionBidUp(INT bidMoney);
void AuctionBidDown(INT bidMoney);
//void UpdateFriendsList();
//void UpdateRecentsList();
//void UpdateGuildsList();