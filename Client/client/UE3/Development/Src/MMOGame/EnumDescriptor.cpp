#include "stdafx.h"
#include "EnumDescriptor.h"


EnumDescriptor::EnumDescriptor(const FString& IniSectionName)
	: _sectionName(IniSectionName)
{
}
//------------------------------------------------------------------------
EnumDescriptor::~EnumDescriptor(void)
{
}
//------------------------------------------------------------------------
FString EnumDescriptor::FindValue( INT EnumKey, bool UseLocalize/*=true*/ ) const
{
	Enum2StrMap::const_iterator it = _enum2StrMap.find(EnumKey);
	if(it != _enum2StrMap.end())
	{
		return FindValue(it->second, UseLocalize);
	}

	return FString::Printf(TEXT("Enum[%s][%d]not found"), *_sectionName, EnumKey);
}
//------------------------------------------------------------------------
FString EnumDescriptor::FindValue( const FString& Key, bool UseLocalize ) const
{
	StringMap::const_iterator it = _enumMaps.find(Key);
	if(it != _enumMaps.end())
	{
		FString val = it->second;
		if(UseLocalize)
		{
			FString lval;
			if(GConfig->GetString(*_sectionName, *val, lval, GGameIni))
			{
				return lval;
			}
		}
	}

	return Key;
}
