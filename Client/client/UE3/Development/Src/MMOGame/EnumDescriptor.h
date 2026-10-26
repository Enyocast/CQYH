#ifndef __ENUMDESCRIPTOR_H__
#define __ENUMDESCRIPTOR_H__

#include "MMOUtil.h"

class EnumDescriptor
{
public:
	EnumDescriptor(const FString& IniSectionName);
	virtual ~EnumDescriptor(void);

	FString FindValue(INT EnumKey, bool UseLocalize=true) const;
	FString FindValue(const FString& Key, bool UseLocalize=true) const;

protected:

	typedef std::map<INT, FString, M_UE3_STL_ALLOC_MAP(INT, FString) > Enum2StrMap;
	typedef std::map<FString, FString, ComparFString, STLAllocator< std::pair<FString, FString>, UE3STLAllocatorPolicy> > StringMap;

	Enum2StrMap _enum2StrMap;
	StringMap _enumMaps;
	FString _sectionName;
};

#define M_AddEnum(s) _enum2StrMap.insert(std::make_pair(s,  TEXT(#s)));_enumMaps.insert(std::make_pair(TEXT(#s), TEXT(#s)));

#endif