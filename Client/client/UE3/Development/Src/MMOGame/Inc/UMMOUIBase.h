
virtual void Init();
virtual void UnInit();

void DeleteEventAdapter();

// 注意：Show函数中IsVisible变量不会发生变化，只要SetVisible中变化
// 因此，SetVisible如果有派生接口，必须调回UIBase的基类接口
virtual void Show(UBOOL V, INT displayPriority = -1);
virtual void SetVisible(UBOOL bValue = TRUE);

void MoveCenterToScreenCenter( INT offsetX, INT offsetY);
virtual void PreOnShow(UBOOL v);
virtual void PostOnShow(UBOOL v);

virtual void UnitWidget(); // TODO: remove this

virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

virtual void SetItemSlotCD( UGFxObject* itemSlot , INT curCD , INT maxCD );
virtual void StopItemSlotCD( UGFxObject* itemSlot );

virtual void SetShowWithOutTarget(UBOOL bValue = TRUE);