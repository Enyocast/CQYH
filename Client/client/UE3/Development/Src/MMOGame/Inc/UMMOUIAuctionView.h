
virtual void Init();
virtual void UnInit();

virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void Reset();

void SetupSellItem(INT srcContainerID, INT srcSlotID);

void ResetSellItemInfo();

void QuickSearchByBag(BYTE SlotType,BYTE ContainerID,INT SlotID);

FString GetMsgText(BYTE textType,INT dwAuctionID,INT price);
FString GetMsgTextContent(BYTE textType,INT dwAuctionID);

void Show_Auction_Msg(int dwAuctionID, int price,Auction_MsgType msgType,Auction_MsgTextType textType,INT itemId);

void ShowBagPanel();

void CreateDelegate(FString functionName,INT dwAuctionID,FString msgText,INT price,UBOOL isAddValue,FString msgTextContent = "",INT type = 0);

void SetSellTimeAndMoney();

void UpdateQueryItem();

