#include "stdafx.h"
#include "GfxDataObjectUtil.h"

UGFxObject* GfxDataObjectUtil::CreateStringArray( class UGFxMoviePlayer* gfxPlayer, const TArray<FString> strList )
{
	UGFxObject* arr = gfxPlayer->CreateArray();
	if (!arr)
	{
		return NULL;
	}

	for (INT i = 0; i < strList.Num(); ++i)
	{
		arr->SetElementString(i, strList(i));
	}

	return arr;
}

FString GfxDataObjectUtil::CreateComboListString( const TArray<FString> strList )
{
	FString str;
	
	for (INT i = 0; i < strList.Num(); ++i)
	{
		str += strList(i);

		if(i < strList.Num() - 1)
		{
			str += TEXT("=");
		}
	}

	return str;
}
