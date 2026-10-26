virtual void Init();
virtual void UnInit();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
void UpdateQueueTime(INT32 total, INT32 pos);
void ResetQueue();