#ifndef _GFXDATAOBJECTUTIL_H_
#define _GFXDATAOBJECTUTIL_H_

class GfxDataObjectUtil
{
public:

	static UGFxObject* CreateStringArray(class UGFxMoviePlayer* gfxPlayer, const TArray<FString> strList);
	static FString CreateComboListString(const TArray<FString> strList);
	
};

#endif