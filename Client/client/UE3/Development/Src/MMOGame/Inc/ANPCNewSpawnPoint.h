
virtual void Serialize(FArchive& Ar);
virtual UBOOL NeedsLoadForClient() const { return FALSE; } // oscar@snda 永远不在游戏中加载

#if WITH_EDITOR
virtual void CheckForErrors();
#endif