#include "stdafx.h"
//#include "MMOGameClasses.h"
#include "MMOUtil.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(AMMOServerPoint)

void AMMOServerPoint::SetUniqueID(INT id)
{
	ServerUniqueID = id;
}

INT AMMOServerPoint::GetUniqueID()
{
	return ServerUniqueID;
}

void AMMOServerPoint::InitUniqueID()
{
	const int MaxSize = 4096;
	bool UniqueIDs[MaxSize];
	memset(UniqueIDs, false, sizeof(UniqueIDs));
	for(TObjectIterator<AMMOServerPoint> it; it; ++it)
	{
		if((*it)->ServerUniqueID > 0 && (*it)->ServerUniqueID < MaxSize)
		{			
			if ( UniqueIDs[(*it)->ServerUniqueID] )
				(*it)->ServerUniqueID = -1;// to re-arrange
			else
				UniqueIDs[(*it)->ServerUniqueID] = true;
		}
	}

	int nLastIndex = 1;
	for(TObjectIterator<AMMOServerPoint> it; it; ++it)
	{
		if((*it)->ServerUniqueID <= 0 )
		{
			int i = nLastIndex;
			for(; i < MaxSize; ++i)
			{
				if(!UniqueIDs[i])
				{
					(*it)->ServerUniqueID = i;
					UniqueIDs[i] = true;

					nLastIndex = i+1;

					break;
				}
			}
			if ( i >= MaxSize )
			{
				appErrorf( TEXT("Too Much AMMOServerPoint! name: %s"), *((*it)->GetName()) );
			}
		}
	}
}