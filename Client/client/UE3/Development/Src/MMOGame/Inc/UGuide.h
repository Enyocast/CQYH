#ifndef _UGUIDE_H_
#define _UGUIDE_H_

public:
	virtual void GetDynamicListValues(const DynamicListInfo& ListInfo, TArray<FString>& Values);
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
	virtual void PostLoad();

#if WITH_EDITOR
	virtual FString GetDetailedDescription( INT InIndex )
	{
		return TEXT("");
	}
#endif

#endif