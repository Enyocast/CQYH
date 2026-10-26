
#include "MMOFacade.h"
#include "MMOGameClasses.h"
#include "LoadMapTipsManager.h"

LoadMapTipsManager::LoadMapTipsManager()
{
	nNextMapID = -1;
	vecMapTips.clear();
}
LoadMapTipsManager::~LoadMapTipsManager()
{

}

void LoadMapTipsManager::Init()
{
	vecMapTips.clear();
	LoadMapTipsDataManager::getSingleton().InitFromFile(TEXT("loadmaptips.txt"), true);
}
void LoadMapTipsManager::Shutdown()
{
	vecMapTips.clear();
}

void LoadMapTipsManager::AddTipsData(LoadMapTipsData& data)
{
	vecMapTips.push_back(data);
}

FString LoadMapTipsManager::RandomMapTips()
{
	const LoadMapTipsData* data = RandomData();
	if(data)
	{
		return data->strTips;
	}

	return TEXT("");
}

FString LoadMapTipsManager::RandomImage()
{
	const LoadMapTipsData* data = RandomData();
	if(data)
	{
		return data->Image;
	}

	return TEXT("");
}

INT LoadMapTipsManager::RandomNO(std::list<INT>&listRand) const
{
	if(listRand.empty())
		return -1;

	INT nTempValue = 0;
	std::list<INT>::iterator itr = listRand.begin();
	for (; itr != listRand.end();++itr)
	{
		nTempValue += vecMapTips[*itr].nWeight; 
	}

	INT nWeight = RandRange(0,nTempValue);

	nTempValue = 0;
	for (itr = listRand.begin(); itr != listRand.end();++itr)
	{
		nTempValue = *itr;
		nWeight -= vecMapTips[nTempValue].nWeight; 

		if(nWeight <= 0)
			break; 
	}
	return nTempValue;
}

void LoadMapTipsManager::SetNextMapID(INT nMapID)
{
	nNextMapID = nMapID;
}

void LoadMapTipsManager::SetNextMapName(FString mapName)
{
	FExportMap mapInfo = UGlobalMapInfo::GetSingleton()->FindMapInfoByName( mapName );
	SetNextMapID(mapInfo.ServerID);
}

const LoadMapTipsData* LoadMapTipsManager::RandomData() const
{
	if(vecMapTips.empty())
		return NULL;

	INT  nClassAll = -1;
	const AMMOPlayer* pkPlayer       =   MMOFacade::getSingleton().GetMainPlayer();

	if(pkPlayer == NULL || pkPlayer->ActorAttributes == NULL)
		return NULL;

	INT nLevel = pkPlayer->ActorAttributes->LevelAttributes.Level;
	INT nClass = pkPlayer->ActorAttributes->ClassType;
	std::list<INT> vecNOID;
	std::list<INT> vecDefaultNOID;
	BOOL bLevelFind = FALSE;
	BOOL bLevelDefFind = FALSE;

	VecLoadMapTipsData::const_iterator itr = vecMapTips.begin();
	for (INT nIndex = 0; itr != vecMapTips.end();++itr,++nIndex)
	{
		if(itr->nMapId == nNextMapID)
		{
			if(nLevel >= itr->nMinLevel && nLevel <= itr->nMaxLevel)
			{
				if(!bLevelFind)
				{
					vecNOID.clear();
					bLevelFind = TRUE;
				}
				if(nClass == itr->nClass || itr->nClass == nClassAll)
					vecNOID.push_back(nIndex);
			}
			else if(!bLevelFind)
			{
				if(nClass == itr->nClass || itr->nClass == nClassAll)
					vecNOID.push_back(nIndex);
			}
		}
		else if (itr->nMapId == 0/* && vecNOID.empty()*/)
		{
			if(nLevel >= itr->nMinLevel && nLevel <= itr->nMaxLevel)
			{
				if(!bLevelDefFind)
				{
					vecDefaultNOID.clear();
					bLevelDefFind = TRUE;
				}
				if(nClass == itr->nClass || itr->nClass == nClassAll)
					vecDefaultNOID.push_back(nIndex);
			}
			else if(!bLevelDefFind)
			{
				if(nClass == itr->nClass || itr->nClass == nClassAll)
					vecDefaultNOID.push_back(nIndex);
			}
		}
	}

	INT nRand = RandomNO(vecNOID);
	if(nRand >= 0)
		return &vecMapTips[nRand];

	nRand = RandomNO(vecDefaultNOID);
	if(nRand >= 0)
		return &vecMapTips[nRand];
	return NULL;
}

LoadMapTipsData* LoadMapTipsDataProcessor::CreateDataObject(INT templateID, bool& needAddToMap)
{
	needAddToMap = false;
	return NULL;
}

void LoadMapTipsDataProcessor::DestroyDataObject(LoadMapTipsData* obj)
{

}

void LoadMapTipsDataProcessor::ParseData(LoadMapTipsData* obj, class CTabFile* dataRow, int rowIdx)
{
	LoadMapTipsData data;
	data.nID							= TReadDataValue_Int<LoadMapTipsDataManager>(TEXT("NO"), dataRow, rowIdx);	
	if(data.nID == 0)
		return;
	data.nMapId							= TReadDataValue_Int<LoadMapTipsDataManager>(TEXT("mapID"), dataRow, rowIdx);
	data.nClass							= TReadDataValue_Int<LoadMapTipsDataManager>(TEXT("class"), dataRow, rowIdx);
	data.nMinLevel						= TReadDataValue_Int<LoadMapTipsDataManager>(TEXT("minLevel"), dataRow, rowIdx);
	data.nMaxLevel						= TReadDataValue_Int<LoadMapTipsDataManager>(TEXT("maxLevel"), dataRow, rowIdx);
	data.nWeight						= TReadDataValue_Int<LoadMapTipsDataManager>(TEXT("weight"), dataRow, rowIdx);
	data.strTips						= TReadDataValue_FString<LoadMapTipsDataManager>(TEXT("tips"), dataRow, rowIdx);
	data.Image						= TReadDataValue_FString<LoadMapTipsDataManager>(TEXT("Image"), dataRow, rowIdx);

	LoadMapTipsManager::getSingleton().AddTipsData(data);
}

void LoadMapTipsDataProcessor::PostInitData()
{
}
