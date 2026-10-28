#ifndef _MOUNT_DATA_H_
#define _MOUNT_DATA_H_

#include "data_manager.h"
#include "mount_def.h"

class CTabFile;
struct MOUNT_ENTRY
{
	INT32 m_nID;
	INT32 m_nLevelLimit;
	INT32 m_nSpeedModificationRate;
	INT32 m_nHitUnmountRate;

	INT32 m_nAuraID;

	INT32 m_nItemID[mftCount];
	INT32 m_nItemCount[mftCount];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, MOUNT_ENTRY* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // _mount_data_h__
