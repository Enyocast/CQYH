public:


	virtual FString GetDetailedDescription( INT InIndex );
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

#if WITH_EDITOR
	virtual void CheckForErrors();
	virtual void CollectReferencedResource(TSet<FString>& outResList);
#endif