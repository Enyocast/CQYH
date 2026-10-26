#include "stdafx.h"
#include "tabfile.h"

#include <stdio.h>
#include "zlib.h"

#include "utf8.h"
#include "ifile.h"

CTabFile::CTabFile()
{
	m_pData = NULL;
	m_uSize = 0;
	m_nRowCount = 0;
	m_nColCount = 0;
	m_pOffsetTable = NULL;
    m_dwCRC32 = 0;
}

CTabFile::~CTabFile()
{
	UnInit();
}

BOOL CTabFile::Init(const TCHAR* pcszFileName, INT32 nSkipLine)
{
	INT32 nRetCode = 0;
    IFile* pFile = NULL;
    UINT32 uBOM = 0;
    INT32 nStringIndex = 0;
    INT32 nOffsetIndex = 0;
    INT32 nIndex = 0;
    BOOL bInQuote = FALSE;
    INT32 nTabCount = 0;
	wchar_t* pszData = NULL;
    char* pszTmp = NULL;

	m_nSkipLine = nSkipLine;
	m_nColCount = 1;
	m_nRowCount = 0;

	LOG_PROCESS_ERROR(pcszFileName);

	pFile = g_OpenFile(pcszFileName, "rb");
	LOG_PROCESS_ERROR(pFile);
	
	m_uSize = pFile->Size();
	LOG_PROCESS_ERROR(m_uSize > 0);

	nRetCode = pFile->Read(&uBOM, sizeof(uBOM));
	LOG_PROCESS_ERROR(nRetCode == sizeof(uBOM));

	//comment by chy, 2015/9/2
    //LOG_PROCESS_ERROR((uBOM & 0xFFFF) == UTF16_BOM);

	if ((uBOM & 0xFFFF) == UTF16_BOM)
	{
		m_uSize -= 2;
		nRetCode = pFile->Seek(2, SEEK_SET);
		LOG_PROCESS_ERROR(nRetCode);
	}
	else if ((uBOM & 0xFFFFFF) == UTF8_BOM)
	{
		m_uSize -= 3;
		nRetCode = pFile->Seek(3, SEEK_SET);
		LOG_PROCESS_ERROR(nRetCode);
	}
	else	// utf8 default
	{
		nRetCode = pFile->Seek(0, SEEK_SET);
		LOG_PROCESS_ERROR(nRetCode);
	}

	LOG_PROCESS_ERROR(m_pData == NULL);
	m_pData = new char[m_uSize];
    memset(m_pData, 0, m_uSize);
	LOG_PROCESS_ERROR(m_pData);

    nRetCode = pFile->Read(m_pData, (UINT32)m_uSize);
	LOG_PROCESS_ERROR(nRetCode == m_uSize);

	pFile->Close();
	pFile = NULL;

	// convert
	if ((uBOM & 0xFFFF) == UTF16_BOM)
	{
        pszTmp = new char[m_uSize * 3 / 2];
        memset(pszTmp, 0, m_uSize * 3 / 2);
#ifdef __linux__
        iconv_t handle = iconv_open("UTF-8", "UTF-16LE");
        LOG_PROCESS_ERROR(handle != (iconv_t) -1);

        char * inbuf = m_pData;
        char * outbuf = pszTmp;
        size_t inbytesleft = m_uSize;
        size_t outbytesleft = m_uSize * 3 / 2;
        nRetCode = iconv(handle, &inbuf, &inbytesleft,
                         &outbuf, &outbytesleft);
        LOG_PROCESS_ERROR(nRetCode != -1);

        m_uSize = m_uSize * 3 / 2 - outbytesleft;
        iconv_close(handle);
#else
        pszData = (wchar_t*)m_pData;
        m_pData = new char[m_uSize * 3 / 2];
        LOG_PROCESS_ERROR(m_pData);

		m_uSize = utf16_2_utf8(pszData, m_uSize / 2, pszTmp, m_uSize * 3 / 2);
		LOG_PROCESS_ERROR(m_uSize > 0);
#endif

		memcpy(m_pData, pszTmp, m_uSize);
        SAFE_DELETE_ARRAY(pszTmp);
	}

    m_dwCRC32 = crc32(0, (const Bytef*)m_pData, m_uSize);

	// first scan
    m_nColCount = 1;
    m_nRowCount = 0;
    while (nIndex < m_uSize)
    {
	    switch (m_pData[nIndex])
	    {
	    case '\t':
		    if (m_nRowCount == 0 && !bInQuote)
			    m_nColCount++;
		    nTabCount++;
		    break;
	    case '\r':
            if (!bInQuote)
            {
                m_pData[nIndex] = 0;
            }
            break;
	    case '\n':
	        if (!bInQuote)
		    {
	            if (nIndex - 1 >= 0 && m_pData[nIndex - 1] == '\r')
                {
                    nIndex++;
                    continue;
                }
			    m_nRowCount++;
		    }
		    break;
	    case '\"':
		    if (bInQuote)
		    {
			    if (m_pData[nIndex + 1] != '\"')
				    bInQuote =  false;
			    else
				    nIndex++;
		    }
		    else
			    bInQuote = true;
		    break;
	    }

	    nIndex++;
    }

	LOG_PROCESS_ERROR(m_pOffsetTable == NULL);
	m_pOffsetTable = new int[m_nColCount * m_nRowCount];
	LOG_PROCESS_ERROR(m_pOffsetTable);

	// second scan
	nIndex = 0;

	bInQuote = false;
	while (nIndex < m_uSize)
	{
		switch (m_pData[nIndex])
		{
		case '\t':
		case '\n':
			if (!bInQuote)
			{
				m_pData[nIndex] = 0;

				while ((nStringIndex < nIndex) && 
                    (m_pData[nStringIndex] == 0 ||
                    m_pData[nStringIndex] == '\r' ||
					m_pData[nStringIndex] == '\n'))
					nStringIndex++;

				LOG_PROCESS_ERROR(nOffsetIndex < m_nColCount * m_nRowCount);
				m_pOffsetTable[nOffsetIndex] = nStringIndex;
				nOffsetIndex++;

				nStringIndex = nIndex + 1;
			}
			break;
		case '\"':
			if (bInQuote)
			{
				if (m_pData[nIndex + 1] == '\"')
				{
					int nTempIndex = nIndex;
					while (m_pData[nTempIndex] != 0 && m_pData[nTempIndex+1] != '\n' && m_pData[nTempIndex+1] != '\t')
					{
						m_pData[nTempIndex] = m_pData[nTempIndex + 1];
						nTempIndex++;
					}
					m_pData[nTempIndex] = 0;
				}
				else
				{
					bInQuote =  false;
					m_pData[nIndex] = 0;
				}
			}
			else
			{
				bInQuote = true;
				m_pData[nIndex] = 0;
			}

			break;
		}

		nIndex++;
	}

	// create name map
	for (int nIndex = 0; nIndex < m_nColCount; nIndex++)
	{
		std::pair<MAP_NAME_2_COL::iterator, bool> InsRet;

		const char* pcszValue = GetData(nIndex, 0);
		LOG_PROCESS_ERROR(pcszValue);

		InsRet = m_mapName2Col.insert(std::make_pair(pcszValue, nIndex));
		LOG_PROCESS_ERROR(InsRet.second);
	}

	SAFE_DELETE_ARRAY(pszData);

	return TRUE;
Exit0:
	if (pFile)
        pFile->Close();

	SAFE_DELETE_ARRAY(pszData);
    SAFE_DELETE_ARRAY(pszTmp);

	UnInit();

	return FALSE;
}

BOOL CTabFile::UnInit(void)
{
	SAFE_DELETE_ARRAY(m_pData);
	SAFE_DELETE_ARRAY(m_pOffsetTable);

    m_mapName2Col.clear();

	return true;
}

INT32 CTabFile::GetRowCount(void)
{
	if (m_nRowCount >= (1 + m_nSkipLine))
		return m_nRowCount - 1 - m_nSkipLine;
	else
		return 0;
}

INT32 CTabFile::GetColCount(void)
{
	return m_nColCount;
}

const char* CTabFile::GetColName(INT32 nCol)
{
    return GetData(nCol, 0);
}

const char* CTabFile::GetData(INT32 nCol, INT32 nRow)
{
    LOG_PROCESS_ERROR(nCol >= 0 && nCol < m_nColCount);
    LOG_PROCESS_ERROR(nRow >= 0 && nRow < m_nRowCount);

    return m_pData + m_pOffsetTable[nRow * m_nColCount + nCol];
Exit0:
    return NULL;
}

const char* CTabFile::GetData(const char* pcszColName, INT32 nRow)
{
    MAP_NAME_2_COL::iterator it;

    it = m_mapName2Col.find(pcszColName);
    LOG_PROCESS_ERROR(it != m_mapName2Col.end());

    return GetData(it->second, nRow);
Exit0:
    return NULL;
}

BOOL CTabFile::ReadData(int nCol, int nRow, char* pszValue, INT32 nSize)
{
	LOG_PROCESS_ERROR(nCol >= 0 && nCol < m_nColCount);
	nRow += (1 + m_nSkipLine);
	LOG_PROCESS_ERROR(nRow >= 0 && nRow < m_nRowCount);
    LOG_PROCESS_ERROR(pszValue);

    if ((m_pData + m_pOffsetTable[nRow * m_nColCount + nCol])[0])
        strxcpy(pszValue, m_pData + m_pOffsetTable[nRow * m_nColCount + nCol], nSize);
    else
        strxcpy(pszValue, m_pData + m_pOffsetTable[2 * m_nColCount + nCol], nSize);

    return TRUE;
Exit0:
	return FALSE;
}

BOOL CTabFile::ReadData(const char* pcszColName, int nRow, char* pszValue, INT32 nSize)
{
	MAP_NAME_2_COL::iterator it;

	it = m_mapName2Col.find(pcszColName);
	LOG_PROCESS_ERROR(it != m_mapName2Col.end());

	return ReadData(it->second, nRow, pszValue, nSize);
Exit0:
	return FALSE;
}

BOOL CTabFile::ReadData(INT32 nCol, INT32 nRow, INT32& rnValue)
{
    LOG_PROCESS_ERROR(nCol >= 0 && nCol < m_nColCount);
	nRow += (1 + m_nSkipLine);
    LOG_PROCESS_ERROR(nRow >= 0 && nRow < m_nRowCount);

    if ((m_pData + m_pOffsetTable[nRow * m_nColCount + nCol])[0])
        rnValue = atoi(m_pData + m_pOffsetTable[nRow * m_nColCount + nCol]);
    else
        rnValue = atoi(m_pData + m_pOffsetTable[2 * m_nColCount + nCol]);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CTabFile::ReadData(const char* pcszColName, int nRow, INT32& rnValue)
{
    MAP_NAME_2_COL::iterator it;

    it = m_mapName2Col.find(pcszColName);
    LOG_PROCESS_ERROR(it != m_mapName2Col.end());

    return ReadData(it->second, nRow, rnValue);
Exit0:
    return FALSE;
}

UINT32 CTabFile::GetCRC(void)
{
    return m_dwCRC32;
}
