#include "stdafx.h"
#include "spirit_data.h"
#include "attribute_def.h"
#include "attribute_data.h"
#include "string_def.h"

BOOL SPIRIT_DATA::ReadLine(INT32& rnID, const char*& rpcszName, SPIRIT_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();
	READ_INT("Level", nLevel);
	READ_INT("AddExp", nAddExp);
	READ_INT("AddSpiritPts", nAddSpiritPts);
	READ_INT("Power", nPower);	
	READ_INT("Exp2PtsCDTime", dwDailyChangeCDTime);
	READ_INT("MoneyCostOneShot", nMoneyCostOneShot);
	READ_INT("NextLevelExp", nNextLevelExp);
	READ_INT("SoulCost", nSoulCost);
	READ_INT("DailyExp2PtsMoneyCost", nDailyExp2PtsMoneyCost);
	READ_INT("DailyExp2PtsMaxCount", nDailyExp2PtsMaxCount);
	READ_INT("BroadcastStringID", nBroadcastStringID);

	for (INT32 nIndex = vlLevel1; nIndex < vlTotal; nIndex++)
	{
		char szVip[COMMON_NAME_LEN];
		memset(szVip, 0, sizeof(szVip));

		snprintf(szVip, COMMON_NAME_LEN, "VipOnlineChangeDiscountLevel%d",nIndex);
		READ_INT(szVip, nVipOnlineChangeDiscount[nIndex-vlLevel1]);
	}

	for (INT32 nIndex = vlLevel1; nIndex < vlTotal; nIndex++)
	{
		char szVip[COMMON_NAME_LEN];
		memset(szVip, 0, sizeof(szVip));

		snprintf(szVip, COMMON_NAME_LEN, "VipOfflineChangeDiscountLevel%d",nIndex);
		READ_INT(szVip, nOfflineChangeDiscount[nIndex-vlLevel1]);
	}

	for (INT32 nIndex = 0; nIndex < MAX_SPIRIT_NODE_PER_LEVEL; nIndex++)
	{
		char szNodeID[COMMON_NAME_LEN];
		memset(szNodeID, 0, sizeof(szNodeID));

		snprintf(szNodeID, COMMON_NAME_LEN, "AttrTemplateNodeID%d",nIndex+1);
		READ_INT(szNodeID, nAttrTemplateNodeID[nIndex]);

		if (pData->nAttrTemplateNodeID[nIndex])
		{
			const ATTRIBUTE_DATA* attr_data = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(pData->nAttrTemplateNodeID[nIndex]);
			LOG_PROCESS_ERROR(attr_data);

			pData->nAttrNodeID[nIndex] = attr_data->m_nNodeID;
		}
	}

	READ_END(nLevel);
}

BOOL SPIRIT_CHANGE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, SPIRIT_CHANGE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("Index", nIndex);
	READ_INT("DailyChangeTime", nDailyChangeTime);
	READ_INT("MoneyCostDiscount", nMoneyCostDiscount);

	READ_END(nIndex);

}

BOOL AIR_LEVEL_DATA::ReadLine(INT32& rnID, const char*& rpcszName, AIR_LEVEL_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("Level", nLevel);
	READ_INT("PtsCost", nPtsCost);
	READ_INT("NextLevelRate", nNextLevelRate);
	READ_INT("DropMoneyCount", nDropMoneyCount);
	READ_INT("ClassLimit", nClassLimit);
	READ_INT("SpiritLevelLimit", nSpiritLevelLimit);
	READ_INT("BroadcastStringID", nBroadcastStringID);

	char szDropAir[COMMON_NAME_LEN];
	memset(szDropAir, 0, sizeof(szDropAir));

	for (INT32 nIndex = 1; nIndex <= MAX_DROP_AIR_COUNT; nIndex++)
	{
		snprintf(szDropAir, COMMON_NAME_LEN, "DropAirID%d", nIndex);
		READ_INT(szDropAir, nDropAirID[nIndex - 1]);

		snprintf(szDropAir, COMMON_NAME_LEN, "DropAirRate%d", nIndex);
		READ_INT(szDropAir, nDropAirRate[nIndex - 1]);
	}

	rnID = MAKE_AIR_LEVEL_KEY(pData->nLevel, pData->nClassLimit);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL AIR_DATA::ReadLine(INT32& rnID, const char*& rpcszName, AIR_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	memset(pData, 0, sizeof(AIR_DATA));

	READ_INT("ID", nAirID);
	READ_INT("Color", nColor);
	READ_INT("Exp", nExp);
	READ_INT("Level", nLevel);
	READ_INT("NextLevelExp", nNextLevelExp);
	READ_INT("NextLevelID", nNextLevelID);
	READ_INT("ExchangeCount", nExchangeCount);
	READ_INT("GroupID", nGroupID);
	READ_INT("BroadcastStringID", nBroadcastStringID);
	READ_STR("Description", szAirname);

	char szAir[30];
	memset(szAir, 0, sizeof(szAir));

 	for (INT32 nIndex = 0; nIndex < MAX_ATTR_PER_NODE; nIndex++)
 	{
		memset(szAir, 0, sizeof(szAir));
		sprintf(szAir, "NodeTemplateID%d",nIndex+1);
		READ_INT(szAir, nNodeTemplateID[nIndex]);

		if (pData->nNodeTemplateID[nIndex])
		{
			const ATTRIBUTE_DATA* attr_data = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(pData->nNodeTemplateID[nIndex]);
			LOG_PROCESS_ERROR(attr_data);

			pData->nNodeID[nIndex] = attr_data->m_nNodeID;
		}
	}

	READ_END(nAirID);
}

BOOL BLOOD_DATA::ReadLine(INT32& rnID, const char*& rpcszName, BLOOD_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("Page", nPage);
	READ_INT("Slot", nSlot);
	READ_INT("Number", nNumber);     
	READ_INT("SpiritPtsCost", nSpiritPtsCost);
	READ_INT("Rate", nRate);
	READ_INT("LevelLimit", nLevelLimit);
	READ_INT("PageLevelLimit", nPageLevelLimit);

	char szBlood[30];

	memset(&pData->nAttrTemplateNodeID, 0, sizeof(pData->nAttrTemplateNodeID));
	memset(&pData->nNodeID, 0, sizeof(pData->nNodeID));

	for (INT32 nIndex = 0; nIndex < MAX_BLOODSEA_ATTR_PER_SLOT; nIndex++)
	{
		memset(szBlood, 0, sizeof(szBlood));
		sprintf(szBlood, "AttrTemplateNodeID%d",nIndex+1);
		READ_INT(szBlood, nAttrTemplateNodeID[nIndex]);

		if (pData->nAttrTemplateNodeID[nIndex])
		{
			const ATTRIBUTE_DATA* attr_data = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(pData->nAttrTemplateNodeID[nIndex]);
			LOG_PROCESS_ERROR(attr_data);

			pData->nNodeID[nIndex] = attr_data->m_nNodeID;
		}
	}

	rnID = MAKE_BLOOD_KEY(pData->nPage, pData->nSlot, pData->nNumber);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL SPIRIT_SLOT_DATA::ReadLine(INT32& rnID, const char*& rpcszName, SPIRIT_SLOT_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("SlotIndex", nSlotIndex);
	READ_INT("LevelLimit", nLevelLimit);
	READ_INT("MoneyCost", nMoneyCost);     
	
	READ_END(nSlotIndex);
}