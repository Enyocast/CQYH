#include "stdafx.h"
#include "soul_data.h"
#include "attribute_data.h"

BOOL SOUL_DATA::ReadLine(INT32& rnID, const char*& rpcszName, SOUL_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

    memset(pData, 0, sizeof(SOUL_DATA));

	READ_INT("TemplateID", m_nTemplateID);
	READ_INT("AttrID", m_nAttrID);
	READ_INT("MatchSocket", m_nMatchSocket);
	READ_INT("SoulLevel", m_nSoulLevel);
	READ_INT("PriceValue", m_nPriceValue);
	READ_INT("UpgradeSoulID", m_nUpgradeSoulID);
	READ_INT("RemovePrice", m_nRemovePrice);

	READ_END(m_nTemplateID);
}
