// *************************************************************************************
// 
// 	Copyright (c) 2007 XGames
// 
// 	All Rights Reserved 
// 
// 	Created by		:		Oscar.Ken
// 	Create Date		:		2007-08-24
// *************************************************************************************

//#include "StdAfx.h"
#include "RefObject.h"



	RefObject::RefObject(void)
		: _refCount(0)
	{
	}

	RefObject::~RefObject(void)
	{
	}

	FString RefObject::ToString() const
	{
		return TEXT("RefObject");
// 		const type_info* pTypeInfo = &typeid(*this);
// 		const char* pszClassName = pTypeInfo->name();
// 		FString str = FString::Printf(TEXT("[ %30s ] ToString() function not override!"), ANSI_TO_TCHAR(pszClassName));
// 		return str;
	}
