#include "stdafx.h"
#include "MMOHelperData.h"
#include "MMOFacade.h"
#include "Inc\MMOGameUIClasses.h"

using namespace ExternalMessage;

//////////////////////////////////////////////////////////////////////////
HelperData* HelperDataProcessor::CreateDataObject(INT templateID, bool& needAddToMap)
{
	needAddToMap = false;
	return NULL;
}

void HelperDataProcessor::DestroyDataObject(HelperData* obj)
{
	if (obj)
	{
		delete obj;
		obj = NULL;
	}
}

void HelperDataProcessor::ParseData(HelperData* obj, class CTabFile* dataRow, int rowIdx)
{
	HelperData data;
	
	data.Id = TReadDataValue_Int<HelperDataManager>(TEXT("ID"), dataRow, rowIdx);
	data.PanelName = TReadDataValue_FString<HelperDataManager>(TEXT("PanelName"), dataRow, rowIdx);
	data.BaseClass = TReadDataValue_Int<HelperDataManager>(TEXT("BaseClass"), dataRow, rowIdx);
	data.SubClass = TReadDataValue_Int<HelperDataManager>(TEXT("SubClass"), dataRow, rowIdx);
	
	MMOHelperData::getSingleton().AddHelperData(data);
}

void HelperDataProcessor::PostInitData()
{
}

//////////////////////////////////////////////////////////////////////////
MMOHelperData::MMOHelperData()
{
}

MMOHelperData::~MMOHelperData()
{
}

void MMOHelperData::Init()
{
	Clear();
	_LoadHelperData(TEXT("help.txt"));
}

void MMOHelperData::Shutdown()
{
	_UnloadHelperData();
	Clear();
}

void MMOHelperData::Clear()
{
}

UBOOL MMOHelperData::_LoadHelperData(const TCHAR* filePath)
{
	_HelperDataMap.clear();
	HelperDataManager::getSingleton().InitFromFile(filePath, true);
	return TRUE;
}

void MMOHelperData::_UnloadHelperData()
{
	_HelperDataMap.clear();
}

void MMOHelperData::AddHelperData(const HelperData& data)
{
	_HelperDataMap.insert(std::make_pair(data.PanelName, data));
}

UBOOL MMOHelperData::GetHelperData(const FString& name, HelperData& data)
{
	HelperDataMap::iterator iter = _HelperDataMap.find(name);
	if (iter != _HelperDataMap.end())
	{
		data = iter->second;
		return TRUE;
	}
	return FALSE;
}

HelperDataMap& MMOHelperData::GetHelperDataMap()
{
	return _HelperDataMap;
}