#include "stdafx.h"
#include "tab_config.h"

#include "tabfile.h"

#include "string_ex.h"

CTabConfig::CTabConfig()
{
}

CTabConfig::~CTabConfig()
{
    UnInit();
}

BOOL CTabConfig::Init(const TCHAR* pcszConfigName, const TCHAR* pcszPath)
{
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(pcszConfigName != NULL);
    if(pcszPath != NULL)
        strxcpy(m_szPath, pcszPath, TAB_PATH_LEN);

    nRetCode = _LoadFromTabFile(pcszConfigName);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
	return FALSE;
}

BOOL CTabConfig::UnInit(void)
{
	m_vecData.clear();
    m_mapName2Col.clear();
    return TRUE;
}

INT32 CTabConfig::GetColCount()
{
	PROCESS_ERROR(m_vecData.size() > 0);
    
	return (INT32)m_vecData[0].size();
Exit0:
	return 0;
}

INT32 CTabConfig::GetRowCount()
{
	return (INT32)m_vecData.size();
}

BOOL CTabConfig::ReadData(const TCHAR* pcszColName, INT32 nRow, TCHAR* pszData, INT32 nDataSize)
{
	MAP_NAME_2_COL::iterator it;
    const TCHAR* pcszValue = NULL;

	LOG_PROCESS_ERROR(pcszColName);
	LOG_PROCESS_ERROR((size_t) nRow < m_vecData.size());
	LOG_PROCESS_ERROR(pszData);

	it = m_mapName2Col.find(pcszColName);
	LOG_PROCESS_ERROR(it != m_mapName2Col.end());

    pcszValue = (const TCHAR*)m_vecData[nRow][it->second].c_str();

    if (pcszValue[0] == 0)
        pcszValue = (const TCHAR*)m_vecData[0][it->second].c_str();
    
    strxcpy(pszData, pcszValue, nDataSize);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CTabConfig::ReadData(const TCHAR* pcszColName, INT32 nRow, INT32& rnData)
{
	MAP_NAME_2_COL::iterator it;
    const TCHAR* pcszValue = NULL;

	LOG_PROCESS_ERROR(pcszColName);
	LOG_PROCESS_ERROR((size_t) nRow < m_vecData.size());

	it = m_mapName2Col.find(pcszColName);
	LOG_PROCESS_ERROR(it != m_mapName2Col.end());

    pcszValue = (const TCHAR*)m_vecData[nRow][it->second].c_str();

    if (pcszValue[0] == 0)
        pcszValue = (const TCHAR*)m_vecData[0][it->second].c_str();

    rnData = atoi(pcszValue);

    return TRUE;
Exit0:
	return FALSE;
}

BOOL CTabConfig::ReadData(INT32 nCol, INT32 nRow, TCHAR* pszData, INT32 nDataSize)
{
    const TCHAR* pcszValue = NULL;

    LOG_PROCESS_ERROR(nCol >= 0);
    LOG_PROCESS_ERROR((size_t) nCol < m_mapName2Col.size());
    LOG_PROCESS_ERROR((size_t) nRow < m_vecData.size());

    pcszValue = m_vecData[nRow][nCol].c_str();

    if (pcszValue[0] == 0)
        pcszValue = m_vecData[0][nCol].c_str();

    strxcpy(pszData, pcszValue, nDataSize);

    return TRUE;
Exit0:
    return FALSE;
}


BOOL CTabConfig::ReadData(INT32 nCol, INT32 nRow, INT32& rnData)
{
    const TCHAR* pcszValue = NULL;

    LOG_PROCESS_ERROR(nCol >= 0);
    LOG_PROCESS_ERROR((size_t) nCol < m_mapName2Col.size());
    LOG_PROCESS_ERROR((size_t) nRow < m_vecData.size());

    pcszValue = m_vecData[nRow][nCol].c_str();

    if (pcszValue[0] == 0)
        pcszValue = m_vecData[0][nCol].c_str();

    rnData = atoi(pcszValue);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CTabConfig::_LoadFromTabFile(const TCHAR* pcszConfigName)
{
    INT32 nRetCode = 0;
	CTabFile oTabFile;
    TCHAR szFileName[TAB_PATH_LEN];

    LOG_PROCESS_ERROR(pcszConfigName);

    snprintf(szFileName, sizeof(szFileName), "%s/%s%s", 
		m_szPath, pcszConfigName, TAB_FILE_EXT_NAME);

    nRetCode = oTabFile.Init(szFileName);
    PROCESS_ERROR(nRetCode);

	m_vecData.resize(oTabFile.GetRowCount() - 1);

	for (INT32 nRowIndex = 1; nRowIndex < oTabFile.GetRowCount(); nRowIndex++)
	{
		m_vecData[nRowIndex - 1].resize(oTabFile.GetColCount());

		for (INT32 nColIndex = 0; nColIndex < oTabFile.GetColCount(); nColIndex++)
		{
			const char* pcszValue = oTabFile.GetData(nColIndex, nRowIndex);
			LOG_PROCESS_ERROR(pcszValue);
			
			m_vecData[nRowIndex - 1][nColIndex] = pcszValue;
		}
	}

	for (INT32 nColIndex = 0; nColIndex < oTabFile.GetColCount(); nColIndex++)
	{
		std::pair<MAP_NAME_2_COL::iterator, bool> InsRet;

		const char* pcszValue = oTabFile.GetData(nColIndex, 0);
		LOG_PROCESS_ERROR(pcszValue);

		InsRet = m_mapName2Col.insert(std::make_pair(pcszValue, nColIndex));
		LOG_PROCESS_ERROR(InsRet.second);
	}

	nRetCode = oTabFile.UnInit();
	LOG_CHECK_ERROR(nRetCode);

    return TRUE;

Exit0: 
	nRetCode = oTabFile.UnInit();
	LOG_CHECK_ERROR(nRetCode);

    return FALSE;
}

BOOL CTabConfig::_LoadFromSqlLite(const TCHAR* pcszConfigName)
{
	INT32 nRetCode = 0;
    char szFileName[TAB_PATH_LEN];
    char szSql[TAB_PATH_LEN];
    SGDP::CSqlite3RecordSet oRecordSet;
	SGDP::CSqlite3Conn oSqliteConn;
	INT32 nRowIndex = 0;

    LOG_PROCESS_ERROR(pcszConfigName);

    _SDTsnprintf(szFileName, sizeof(szFileName), _SDT("%s/%s%s"),
		m_szPath, pcszConfigName, SQLITE_FILE_EXT_NAME);

	nRetCode = oSqliteConn.Connect(szFileName);
    PROCESS_ERROR(nRetCode);

    _SDTsnprintf(szSql, sizeof(szSql), _SDT("SELECT * FROM %s"),
            pcszConfigName);

    nRetCode = oSqliteConn.Execute(szSql, &oRecordSet);
	LOG_PROCESS_ERROR(nRetCode);

	if (oRecordSet.GetRecord()) {
	    // Get fields name.
	    for (UINT32 uIndex = 0; uIndex < oRecordSet.GetFieldCount(); uIndex++)
	    {
	        std::pair<MAP_NAME_2_COL::iterator, bool> insRet;
            const char * pcszValue = oRecordSet.GetFieldName(uIndex);
            insRet = m_mapName2Col.insert(std::make_pair(pcszValue, uIndex));
            LOG_PROCESS_ERROR(insRet.second);
        }
	}

    do
    {
        std::vector<tstring> vecLine;
        vecLine.resize(oRecordSet.GetFieldCount());

        for (UINT32 uColIndex = 0; uColIndex < oRecordSet.GetFieldCount(); uColIndex++)
        {
            vecLine[uColIndex] = oRecordSet.GetFieldValue(uColIndex);
        }
        m_vecData.push_back(vecLine);
    } while (oRecordSet.GetRecord());

    return TRUE;
Exit0:

	return FALSE;
}

const char* CTabConfig::GetColName(INT32 nColID)
{
	MAP_NAME_2_COL::iterator it;

	LOG_PROCESS_ERROR(nColID < GetColCount());

	for (it = m_mapName2Col.begin(); it != m_mapName2Col.end(); it++)
	{
		if (it->second == nColID)
		{
			break;
		}
	}

	PROCESS_ERROR(it != m_mapName2Col.end());

	return (it->first).c_str();
Exit0:
	return NULL;
}