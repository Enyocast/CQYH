#include "stdafx.h"
#include "aura_data.h"
#include "scene_def.h"
#include "script_mgr.h"

BOOL AURA_ENTRY::ReadLine(INT32& rnID, const char*& rpcszName, AURA_ENTRY* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("TemplateID", m_nID);
	READ_INT("Category", m_nAttrTable[aatCategory]);
	READ_INT("Type", m_nAttrTable[aatType]);
	READ_INT("Group", m_nAttrTable[aatGroup]);

	READ_INT("Duration", m_nAttrTable[aatDuration]);
	READ_INT("Delay", m_nAttrTable[aatDelay]);
	READ_INT("Interval", m_nAttrTable[aatInterval]);

	READ_INT("StackSameIdSameCaster", m_nAttrTable[aatStackTypeSameIdSameCaster]);
	READ_INT("StackSameTypeSameCaster", m_nAttrTable[aatStackSameTypeSameCaster]);
	READ_INT("StackSameGroupSameCaster", m_nAttrTable[aatStackSameGroupSameCaster]);
	READ_INT("StackSameIdDiffCaster", m_nAttrTable[aatStackTypeSameIdDiffCaster]);
	READ_INT("StackSameTypeDiffCaster", m_nAttrTable[aatStackSameTypeDiffCaster]);
	READ_INT("StackSameGroupDiffCaster", m_nAttrTable[aatStackSameGroupDiffCaster]);


	READ_INT("TimeCover", m_nAttrTable[aatTimeCover]);
	READ_INT("StackResetTime", m_nAttrTable[aatStackResetTime]);

	READ_INT("InitStackCount", m_nAttrTable[aatInitStackCount]);
	READ_INT("MaxStackCount", m_nAttrTable[aatMaxStackCount]);
	LOG_PROCESS_ERROR(pData->m_nAttrTable[aatInitStackCount] <= pData->m_nAttrTable[aatMaxStackCount]);

//	READ_INT("StackEfficient", m_nAttrTable[aatStackEfficient]);

//	if(pData->m_nAttrTable[aatMaxStackCount] <= 1)
//	{
//		if(pData->m_nAttrTable[aatStackEfficient] != 0)
//		{
//			WRN("Force set stack efficient to 0 for none stack aura, id: %d, MaxStackCount: %d, Efficient: %d", pData->m_nID, pData->m_nAttrTable[aatMaxStackCount], pData->m_nAttrTable[aatStackEfficient]);
//			pData->m_nAttrTable[aatStackEfficient] = 0;
//		}
//	}

	READ_INT("StrengthLevel", m_nAttrTable[aatStrengthLevel]);

	READ_INT("CanDispel", m_nAttrTable[aatCanDispel]);
	READ_INT("CanCancel", m_nAttrTable[aatCanCancel]);
	READ_INT("DispelCount", m_nAttrTable[aatDispelCount]);

	READ_INT("TrigOnRemoveWhenDispel", m_nAttrTable[aatTrigOnRemoveWhenDispel]);
	READ_INT("TrigOnRemoveWhenTimeup", m_nAttrTable[aatTrigOnRemoveWhenTimeup]);

	READ_INT("AttackType", m_nAttrTable[aatAttackType]);
	READ_INT("JudgeType", m_nAttrTable[aatJudgeType]);
	READ_INT("ElementaryType", m_nAttrTable[aatElementaryType]);

	READ_INT("EffectPctX", m_nAttrTable[aatEffectPctX]);
	READ_INT("EffectValueX", m_nAttrTable[aatEffectValueX]);
	READ_INT("EffectPct", m_nAttrTable[aatEffectPct]);
	READ_INT("EffectValue", m_nAttrTable[aatEffectValue]);
	READ_INT("RemoveWhenDead", m_nAttrTable[aatRemoveWhenDead]);
	READ_INT("SaveToDB", m_nAttrTable[aatSaveToDB]);
	READ_INT("OfflineTimeValid", m_nAttrTable[aatOfflineTimeValid]);

	READ_INT("HiddenToClient", m_nAttrTable[aatHiddenToClient]);
	READ_INT("HiddenToSelf", m_nAttrTable[aatHiddenToSelf]);

	READ_INT("ThreatPct", m_nAttrTable[aatThreatPct]);
	READ_INT("ThreatValue", m_nAttrTable[aatThreatValue]);
	READ_INT("ThreatMax", m_nAttrTable[aatThreatMax]);

	READ_INT("ControlDecay", m_nAttrTable[aatControlDecay]);
	READ_INT("EffectTimeMin", m_nAttrTable[aatEffectTimeMin]);
	READ_INT("Eternal", m_nAttrTable[aatEternal]);
	READ_INT("IgnoreDefense", m_nAttrTable[aatIgnoreDefense]);

	READ_INT("DisplayGroup", m_nAttrTable[aatDisplayGroup]);
	READ_INT("DisplayValue", m_nAttrTable[aatDisplayValue]);

	READ_INT("ResistType", m_nAttrTable[aatResistType]);
	READ_INT("EffectDecay", m_nAttrTable[aatEffectDecay]);

	READ_INT("OnAppendID", m_nAttrTable[aatOnAppend]);
	READ_INT("BeforeStackID", m_nAttrTable[aatBeforeStack]);
	READ_INT("AfterStackID", m_nAttrTable[aatAfterStack]);
	READ_INT("OnTimeupID", m_nAttrTable[aatOnTimeup]);
	READ_INT("OnDispelID", m_nAttrTable[aatOnDispel]);
	READ_INT("OnRemoveID", m_nAttrTable[aatOnRemove]);

	READ_INT("ExDelay1", m_ExEvtPoint[0].m_nExEvtTime);
	READ_INT("ExDelay2", m_ExEvtPoint[1].m_nExEvtTime);

	READ_INT("OnEx1ID", m_ExEvtPoint[0].m_nExOnEvt);
	READ_INT("OnEx2ID", m_ExEvtPoint[1].m_nExOnEvt);

	rnID = pData->m_nID;
	return TRUE;
Exit0:
	rnID = pData->m_nID;
	return FALSE;
}
