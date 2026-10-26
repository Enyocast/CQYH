#ifndef _NEW_SPELL_DATA_H_
#define _NEW_SPELL_DATA_H_

#include "string_def.h"
#include "attribute_def.h"
#include "data_manager.h"
#include "spell_def.h"

struct SPELL_PROGRESS_DATA
{
	INT32 m_nID;
	INT32 m_nLevel;
	INT32 m_nConsumePts;
	INT32 m_nRequireLevel;
    INT32 m_nRequireItem;
    INT32 m_nRequireItemCount;
	INT32 m_nPow;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SPELL_PROGRESS_DATA* pData, CTabFile* poTabConfig, INT32 nRow);
};

struct TRASFORM_DATA
{
	INT32 m_nAuraID;
	INT32 m_nEquipSpell[qssSlotCount];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, TRASFORM_DATA* pData, CTabFile* poTabConfig, INT32 nRow);
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

struct SPELL_ENTRY
{
	INT32 m_nID;
	INT32 m_nLevel;
	INT32 m_nRuneSlotID;
	INT32 m_nAttrTable[satTotal];

	char m_szName[MAX_SPELL_NAME_LEN];

	struct CD_GROUP
	{
		INT32 m_nCdGrpID;
		INT32 m_nCdGrpValue;
	};

	INT32 m_nCdGrpCount;
	CD_GROUP m_CdGrp[MAX_CD_GROUP];

	struct EX_CAST_POINT
	{
		INT32 m_nExCastTime;
		INT32 m_nExOnCast;
	};
	EX_CAST_POINT m_ExCastPoint[MAX_EX_CAST];
	BOOL m_bInited;
	BOOL m_bShowOnUI;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SPELL_ENTRY* pData, CTabFile* pTabConfig, INT32 nRow);

//	static INT32 ReadAndReplaceVar(const char* szField, CTabFile* pTabConfig, INT32 nRow, SPELL_VAR* pVar);
};

struct SPELL_VAR
{
	INT32 m_nID;
	INT32 m_nLevel;
	INT32 m_nRuneSlotID;

	INT32 m_nVariableTable[MAX_EX_PARAM_COUNT][2];

	INT32 m_nX[MAX_EX_PARAM_COUNT];
	INT32 m_nTempValue;

//	BOOL GetValue(const char* szVariable, INT32& nValue);

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SPELL_VAR* pData, CTabFile* pTabConfig, INT32 nRow);
};


//struct SPELL_NODE_DATA
//{
//	INT32 m_nID;
//	INT32 m_nRuneSlotID;
//
//	INT32 m_nCasterCheckNode;
//	INT32 m_nTargetCheckNode;
//	INT32 m_nOnLearn;
//	INT32 m_nOnForget;
//	INT32 m_nOnEquip;
//	INT32 m_nOnUnEquip;
//	INT32 m_nOnPrepare;
//	INT32 m_nOnCast;
//	INT32 m_nOnBreak;
//	INT32 m_nOnBulletCreate;
//	INT32 m_nBeforeRoll;
//	INT32 m_nAfterRoll;
//	INT32 m_nBeforeEffect;
//	INT32 m_nAfterEffect;
//	INT32 m_ExOnCast[MAX_EX_CAST];
//
//	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SPELL_NODE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
//};


#endif // _new_spell_data_h__
