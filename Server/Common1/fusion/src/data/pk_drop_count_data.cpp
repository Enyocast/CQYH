#include "stdafx.h"
#include "pk_drop_count_data.h"

BOOL PK_DROP_COUNT_DATA::ReadLine(INT32& rnID, const char*& rpcszName, PK_DROP_COUNT_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("Level", m_nLevel);

    READ_INT("MaxDropNormalWhite", m_nMaxDropCount[0][rncWhite]);
    READ_INT("MaxDropNormalYellow", m_nMaxDropCount[0][rncYellow]);
    READ_INT("MaxDropNormalRed", m_nMaxDropCount[0][rncRed]);

    READ_INT("MaxDropExpensiveWhite", m_nMaxDropCount[1][rncWhite]);
    READ_INT("MaxDropExpensiveYellow", m_nMaxDropCount[1][rncYellow]);
    READ_INT("MaxDropExpensiveRed", m_nMaxDropCount[1][rncRed]);

    READ_INT("MaxDropEquippedWhite", m_nMaxDropCount[2][rncWhite]);
    READ_INT("MaxDropEquippedYellow", m_nMaxDropCount[2][rncYellow]);
    READ_INT("MaxDropEquippedRed", m_nMaxDropCount[2][rncRed]);

    READ_TIME("ProtectTime", m_nProtectTime);

    READ_END(m_nLevel);
}
