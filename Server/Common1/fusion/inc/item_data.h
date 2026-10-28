#ifndef _ITEM_DATA_H_
#define _ITEM_DATA_H_

#include "item_def.h"
#include "string_def.h"
#include "attribute_def.h"
#include "data_manager.h"
#include "spell_def.h"

//Intrinsic attribute list
static const INT16 FixAttrTable[] =
{
    catPhyAtk,
    catMaxPhyAtk,
    catMagAtk,
    catMaxMagAtk,
    catTaoAtk,
    catMaxTaoAtk,
    catPhyDef,
    catMaxPhyDef,
    catMagDef,
    catMaxMagDef,
    catMaxHp,
    catMaxMp,
    catAccurate,
    catAgility,
    catAtkSpeed,
    catMagDodge
};

static const INT32 FixAttrTableSize = sizeof(FixAttrTable) / sizeof(FixAttrTable[0]);
struct ITEM_DATA
{
    INT32 m_nTemplateID;
    char  m_szName[MAX_ITEM_NAME_LEN];
    UINT8 m_byItemLevel;
    UINT8 m_byType;
    UINT8 m_bySubType;
    UINT8 m_byUseInCombat;
    UINT8 m_byUseInArena;
    UINT8 m_byRequireLevel;
    UINT8 m_byRequireClass;
    UINT8 m_byRequireGender;
    UINT8 m_byMaxEquip;
    INT32 m_nMaxOwn;
    UINT8 m_byColor;
    UINT8 m_byBindType;
    UINT8 m_byDurType;
    INT32 m_nDur;
    INT32 m_nWeight;
    UINT8 m_byCanDelete;
    UINT8 m_byCanStorage;
    UINT8 m_byCanSell;
    INT32 m_nSellPrice;
    INT32 m_nSpellID;
    INT32 m_nSpellLevel;
    INT32 m_nSelfCoolDown;
	INT32 m_nHandbookType;
	INT32 m_nHandbookIndex;

    struct CD_GROUP
    {
        INT32 m_nCdGrpID;
        INT32 m_nCdGrpValue;

    };

    INT32 m_nCdGrpCount;
    CD_GROUP m_CdGrp[MAX_CD_GROUP];

    INT32 m_nDropLimitDuration;
    INT32 m_nDropLimitCount;
    INT32 m_nDropFromServerStart;
    UINT8 m_byLog;
    UINT8 m_byStat;
    UINT8 m_byExpensiveItem;
    UINT8 m_bPkDrop;
    UINT8 m_bTeamAuction;       //Whether team auction is allowed
    UINT8 m_bAuction;           //Whether auction is allowed
    INT32 m_nAuctionFee;        //Auction storage fee
    UINT8 m_byAuctionType;
    UINT8 m_byAuctionSubType;
    INT32 m_nDefaultAuctionPrice;
    INT32 m_nPlayerDropTime;
    INT32 m_nDropGroupID;
    INT32 m_nShopTypeSell;
    INT32 m_nVarIndex;
    char m_szScript[MAX_EMBEDDED_SCRIPT_LEN];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, ITEM_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

const ITEM_DATA* GetItemData(INT32 nTemplateID);

struct SET_DATA;
struct ATTRIBUTE_DATA;
struct EQUIP_DATA : public ITEM_DATA
{
    INT32 m_nRequireMaxPhyAtk;
    INT32 m_nRequireMaxMagAtk;
    INT32 m_nRequireMaxTaoAtk;
    UINT8 m_byEquipType;
    UINT8 m_byEquipStrength;
    UINT8 m_byIdentified;
    UINT8 m_byDestroyOnDeath;
    UINT8 m_byCannotUnEquip;
    INT32 m_nSocketChance;
    UINT8 m_bySocketCountMin;
    UINT8 m_bySocketCountMax;
    INT32 m_nColorSocketRate;
    INT32 m_nCanRepair;
    INT32 m_nRepairCost;
    INT32 m_nSpecialRepairCost;
    INT32 m_nIdentifyCost;
    INT32 m_nRandomizeCost;
    INT32 m_nPow;
    INT32 m_nLuckModifier;
    INT32 m_nCanDecompose;
    SET_DATA* m_SetData;

    //Intrinsic attributes
    INT32 m_nFixAttr[FixAttrTableSize];

    //Intrinsic weather attributes
    INT32 m_nWeatherAttrID;

    //Intrinsic special skills
    INT32 m_nSpecialAttrID;

    //Attribute pool IDs and probabilities
    INT32 m_nRandomAttributeChance;
    INT32 m_nAttributePoolID[MAX_RANDOM_ATTR_COUNT];
    INT32 m_nAttributePoolChance[MAX_RANDOM_ATTR_COUNT];

    // Minimum cost before the second inscription can appear
    UINT32 m_dwSecondRuneCost;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, EQUIP_DATA* pData, CTabFile* pTabConfig, INT32 nRow);

    //attr nodes
    INT32 m_nNodeCount;
    INT32 m_nNodeIDs[FixAttrTableSize];

    const ATTRIBUTE_DATA* m_pWeatherAttrData;
    const ATTRIBUTE_DATA* m_pSpecialAttrData;
};



#endif // _ITEM_DATA_H_
