#include "stdafx.h"
#include "item_data.h"
#include "script_mgr.h"
#include "scene_def.h"
#include "attribute_data.h"

BOOL ITEM_DATA::ReadLine(INT32& rnID, const char*& rpcszName, ITEM_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();
    char* pValue = NULL;
    char szValue[128] = { 0 };

	READ_INT("ID", m_nTemplateID);
	READ_STR("Name", m_szName);

	READ_INT("ItemLevel", m_byItemLevel);
	READ_INT_EXPR("Type", m_byType);
	READ_INT_EXPR("SubType", m_bySubType);
	READ_INT("UsedStatus", m_byUseInCombat);
    READ_INT("CanUseInArena", m_byUseInArena);
	READ_INT("RequireLevel", m_byRequireLevel);
	READ_BIT_MASK("RequireClass", m_byRequireClass);
	READ_INT("RequireGender", m_byRequireGender);
	READ_INT("MaxEquip", m_byMaxEquip);
	READ_INT("MaxOwn", m_nMaxOwn);
	READ_INT("Color", m_byColor);
	READ_INT_EXPR("BindType", m_byBindType);
	READ_INT_EXPR("DurType", m_byDurType);
	READ_INT("Dur", m_nDur);

    if (pData->m_byType == ITEMTYPE_DEPOSIT)
        LOG_PROCESS_ERROR(pData->m_byDurType == DURTYPE_DEPOSIT);

    READ_INT("Weight", m_nWeight);
    READ_INT("CanDrop", m_byCanDelete);
    READ_INT("Storage", m_byCanStorage);
    READ_INT("CanSell", m_byCanSell);
	READ_INT("Price", m_nSellPrice);
	READ_INT("SpellID", m_nSpellID);
	READ_INT("SpellLevel", m_nSpellLevel);
	READ_TIME("SelfCoolDown", m_nSelfCoolDown);

    nRetCode = pTabConfig->ReadData("GroupCoolDown", nRow, szValue, sizeof(szValue)/sizeof(char));
    LOG_PROCESS_ERROR(nRetCode);

    pValue = szValue;
    pData->m_nCdGrpCount = 0;
    while(1)
    {
        char* tok = SplitStr(pValue, ';');
        if(tok == NULL)
            break;

        sscanf(tok, "%d-%d",&pData->m_CdGrp[pData->m_nCdGrpCount].m_nCdGrpID, 
            &pData->m_CdGrp[pData->m_nCdGrpCount].m_nCdGrpValue);
        pData->m_CdGrp[pData->m_nCdGrpCount].m_nCdGrpValue = CONVERT_TIME(pData->m_CdGrp[pData->m_nCdGrpCount].m_nCdGrpValue);

        pData->m_nCdGrpCount++;
    }

    READ_INT("LimitDuration", m_nDropLimitDuration);
    READ_INT("LimitCount", m_nDropLimitCount);
    READ_INT("ServerStart", m_nDropFromServerStart);
    READ_INT("Log", m_byLog);
    READ_INT("Stat", m_byStat);
    READ_INT("Expensive", m_byExpensiveItem);
    READ_INT("PkDrop", m_bPkDrop);
    READ_INT("TeamAuction", m_bTeamAuction);
    READ_INT("Auction", m_bAuction);
    READ_INT("AuctionFee", m_nAuctionFee);
    READ_INT("AuctionType", m_byAuctionType);
    READ_INT("AuctionSubType", m_byAuctionSubType);
    READ_INT("AuctionDefaultPrice", m_nDefaultAuctionPrice);
    READ_INT("PlayerDropTime", m_nPlayerDropTime);
    READ_INT("DropGroupID", m_nDropGroupID);
    READ_INT("ShopTypeSell", m_nShopTypeSell);
	READ_STR("Script", m_szScript);

	pData->m_nVarIndex = -1;

	rpcszName = pData->m_szName;
	READ_END(m_nTemplateID);
}

BOOL EQUIP_DATA::ReadLine(INT32& rnID, const char*& rpcszName, EQUIP_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	nRetCode = ITEM_DATA::ReadLine(rnID, rpcszName, pData, pTabConfig, nRow);
	LOG_PROCESS_ERROR(nRetCode);

	LOG_PROCESS_ERROR(pData->m_byType == ITEMTYPE_EQUIP);
	LOG_PROCESS_ERROR(pData->m_byDurType == DURTYPE_EQUIP);
	pData->m_nDur *= EQUIP_DUR_MULTIPLIER;

    READ_INT("RequireMaxPhyAtk", m_nRequireMaxPhyAtk);
    READ_INT("RequireMaxMagAtk", m_nRequireMaxMagAtk);
    READ_INT("RequireMaxTaoAtk", m_nRequireMaxTaoAtk);
	READ_INT_EXPR("SubSubType", m_byEquipType);
    READ_INT("EquipStrength", m_byEquipStrength);
	READ_INT("Identified", m_byIdentified);
    READ_INT("DestroyOnDeath", m_byDestroyOnDeath);
    READ_INT("CannotUnEquip", m_byCannotUnEquip);
    READ_INT("SocketChance", m_nSocketChance);
	READ_INT("SocketCountMin", m_bySocketCountMin);
    READ_INT("SocketCountMax", m_bySocketCountMax);
    READ_INT("ColorSocketRate", m_nColorSocketRate);
    READ_INT("CanRepair", m_nCanRepair);
    READ_INT("RepairCost", m_nRepairCost);
    READ_INT("SpecialRepairCost", m_nSpecialRepairCost);
    READ_INT("IdentifyCost", m_nIdentifyCost);
    READ_INT("RandomizeCost", m_nRandomizeCost);
    READ_INT("BasePow", m_nPow);
    READ_INT("LuckModifier", m_nLuckModifier);
    READ_INT("CanDecompose", m_nCanDecompose);
    pData->m_SetData = NULL;

	READ_INT("PhyAtk", m_nFixAttr[0]);
	READ_INT("MaxPhyAtk", m_nFixAttr[1]);
	READ_INT("MagAtk", m_nFixAttr[2]);
	READ_INT("MaxMagAtk", m_nFixAttr[3]);
	READ_INT("TaoAtk", m_nFixAttr[4]);
	READ_INT("MaxTaoAtk", m_nFixAttr[5]);
	READ_INT("PhyDef", m_nFixAttr[6]);
	READ_INT("MaxPhyDef", m_nFixAttr[7]);
    READ_INT("MagDef", m_nFixAttr[8]);
    READ_INT("MaxMagDef", m_nFixAttr[9]);
    READ_INT("MaxHp", m_nFixAttr[10]);
    READ_INT("MaxMp", m_nFixAttr[11]);
    READ_INT("Accurate", m_nFixAttr[12]);
    READ_INT("Agility", m_nFixAttr[13]);
    READ_INT("AtkSpeed", m_nFixAttr[14]);
    READ_INT("MagDodge", m_nFixAttr[15]);

    READ_INT("WeatherAttrID", m_nWeatherAttrID);
    READ_INT("SpecialAttrID", m_nSpecialAttrID);
    READ_INT("RandomAttributeChance", m_nRandomAttributeChance);
    READ_INT("AttributePoolID1", m_nAttributePoolID[0]);
    READ_INT("AttributePoolID2", m_nAttributePoolID[1]);
    READ_INT("AttributePoolID3", m_nAttributePoolID[2]);
    READ_INT("AttributePoolID4", m_nAttributePoolID[3]);
    READ_INT("PoolChance1", m_nAttributePoolChance[0]);
    READ_INT("PoolChance2", m_nAttributePoolChance[1]);
    READ_INT("PoolChance3", m_nAttributePoolChance[2]);
    READ_INT("PoolChance4", m_nAttributePoolChance[3]);
    READ_INT("SecondRuneCost", m_dwSecondRuneCost);

	rpcszName = pData->m_szName;
	READ_END(m_nTemplateID);
}

const ITEM_DATA* GetItemData(INT32 nTemplateID)
{
	const ITEM_DATA* itemdata = CDataManager<ITEM_DATA>::GetInstance().GetData(nTemplateID);

	if (itemdata)
		return itemdata;

	return CDataManager<EQUIP_DATA>::GetInstance().GetData(nTemplateID);
}
