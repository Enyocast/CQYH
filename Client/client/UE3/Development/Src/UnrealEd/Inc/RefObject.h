// *************************************************************************************
// 
// 	Copyright (c) 2007 XGames
// 
// 	All Rights Reserved 
// 
// 	Created by		:		Oscar.Ken
// 	Create Date		:		2007-08-24
// *************************************************************************************

#pragma once
#include "SmartPtr.h"

class _CoreExport RefObject
{
public:

	RefObject();
	virtual ~RefObject();

	void AddRef()
	{
#if OGE_MULTI_THREADING
		XInterLockedIncrement(&_refCount);
#else
		++_refCount;
#endif
	}

	void Release()
	{
#if OGE_MULTI_THREADING
		XInterLockedDecrement(&_refCount);
#else
		--_refCount;
#endif
		if(_refCount == 0)
		{
			OGRE_DELETE this;
		}
	}

	virtual FString ToString() const;
	long GetReferenceCount() const throw(){ return _refCount; }

protected:

	long	_refCount;
};

SmartPointer(RefObject);

