public:

	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent);

#if WITH_EDITOR
	virtual void CheckForErrors();
#endif


	virtual FString GetLargeIconName(bool isMale,int actorClass);