#include "stdafx.h"
#include "MMOItemDataManager.h"
#include "MMOFacade.h"
#include "MMOFreeTipsDataManager.h"

FFreeTipsData* FreeTipsDataProcessor::CreateDataObject(INT templateID, bool& needAddToMap)
{
	FFreeTipsData *pFreeTips = new FFreeTipsData();
	return  pFreeTips;
}

void FreeTipsDataProcessor::DestroyDataObject(FFreeTipsData* obj)
{
	if(obj)
	{
		delete obj;
		obj = NULL;
	}
}

void FreeTipsDataProcessor::ParseData( FFreeTipsData* obj, class CTabFile* dataRow, int rowIdx )
{
	if(obj){
		obj->ID		= TReadDataValue_Int<MMOFreeTipsDataManager>(TEXT("ID"), dataRow, rowIdx);
		obj->MovieName	= TReadDataValue_FString<MMOFreeTipsDataManager>(TEXT("MovieName"), dataRow, rowIdx);
		obj->PanelName	= TReadDataValue_FString<MMOFreeTipsDataManager>(TEXT("PanelName"), dataRow, rowIdx);
		obj->ValueName	= TReadDataValue_FString<MMOFreeTipsDataManager>(TEXT("ValueName"), dataRow, rowIdx);
		obj->ScriptTxt	= TReadDataValue_FString<MMOFreeTipsDataManager>(TEXT("ScriptTxt"), dataRow, rowIdx);
	}
}

void FreeTipsDataProcessor::PostInitData()
{
	//MMOItemDataManager& itemMgr = MMOItemDataManager::getSingleton();
	//MMOItemDataManager::DataTypeMap::const_iterator it = itemMgr._dataMap.begin();
	//for (; it != itemMgr._dataMap.end(); ++it)
	//{
	//	MMOFacade::getSingleton().AddItemTemplate(it->first, it->second);
	//}
}


