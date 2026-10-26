
virtual void Init();
virtual void UnInit();
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
private:
	void ConfirmMallBuyHint();
	void ConfirmMallGiveFriendHint();
	INT	 GetGoodsNum();