#include "stdafx.h"
#include "mount_data.h"

BOOL MOUNT_ENTRY::ReadLine(INT32& rnID, const char*& rpcszName, MOUNT_ENTRY* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("ID", m_nID);

	READ_INT("LevelLimit", m_nLevelLimit);
	READ_INT("SpeedModificationRate", m_nSpeedModificationRate);
	READ_INT("HitUnmountRate", m_nHitUnmountRate);
	READ_INT("AuraID", m_nAuraID);

	READ_INT("ItemID1", m_nItemID[mftFragA]);
	READ_INT("ItemID2", m_nItemID[mftFragB]);
	READ_INT("ItemID3", m_nItemID[mftFragC]);

	READ_INT("ItemCount1", m_nItemCount[mftFragA]);
	READ_INT("ItemCount2", m_nItemCount[mftFragB]);
	READ_INT("ItemCount3", m_nItemCount[mftFragC]);

	rnID = pData->m_nID;

	return TRUE;
Exit0:
	return FALSE;

}
