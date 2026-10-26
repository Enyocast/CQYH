public:

	//virtual void GetDynamicListValues(const DynamicListInfo& ListInfo, TArray<FString>& Values);
	UBOOL IsMoney() const;

	virtual FString GetDetailedDescription( INT InIndex )
	{
		return eventGetDetailedDescription(InIndex);
	}
	//bool DataToExcel(TArray<FString>& Row);
	virtual void GetDynamicListValues(const DynamicListInfo& ListInfo, TArray<FString>& Values);
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

	virtual FString GetLargeIconName(bool isMale,int actorClass);

	class UTexture2D* GetDisplayIcon();
	class UTexture2D* GetDisplayLargeIcon();
	class UTexture2D* GetDisplayLargeIconFemale();

	class UStaticMesh* GetDropMesh();

	class UMMOAbility* GetToUseAbility();

#if WITH_EDITOR
	virtual void CheckForErrors();
	virtual void CollectReferencedResource(TSet<FString>& outResList);
#endif