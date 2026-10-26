#include "stdafx.h"
#include "tabfile.h"

#include <stdio.h>

#include "utf8.h"
//#include "ifile.h"

#define LOG_PROCESS_ERROR(__condition__)							\
	do																\
	{																\
	if (!(__condition__))										\
		{															\
		printf("LOG_PROCESS_ERROR("#__condition__") at line %d in function %s() file \"%s\"", \
		__LINE__, __FUNCTION__, __FILE__);                  \
		goto Exit0;												\
		}															\
	} while (0)

#define SAFE_DELETE(__pointer__)				\
	do											\
	{											\
	if (__pointer__)						\
		{										\
		delete (__pointer__);				\
		(__pointer__) = NULL;				\
		}										\
	} while (0);

#define SAFE_DELETE_ARRAY(__pointer__)			\
	do											\
	{											\
	if (__pointer__)						\
		{										\
		delete [] (__pointer__);			\
		(__pointer__) = NULL;				\
		}										\
	} while (0);

CTabFile::CTabFile()
{
	m_pData = NULL;
	m_uSize = 0;
	m_nRowCount = 0;
	m_nColCount = 0;
	m_pOffsetTable = NULL;
}

CTabFile::~CTabFile()
{
	UnInit();
}

bool CTabFile::Init(const TCHAR* pcszFileName)
{
	int nRetCode = 0;
    FILE* pFile = NULL;
    unsigned int uBOM = 0;
    size_t nStringIndex = 0;
    int nOffsetIndex = 0;
    size_t nIndex = 0;
    bool bInQuote = false;
    int nTabCount = 0;
	wchar_t* pszData = NULL;
    char* pszTmp = NULL;

	m_nColCount = 1;
	m_nRowCount = 0;

	LOG_PROCESS_ERROR(pcszFileName);

	pFile = _tfopen(pcszFileName, _T("rb"));
	LOG_PROCESS_ERROR(pFile);
	
	fseek(pFile, 0, SEEK_END);
	m_uSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	//m_uSize = pFile->Size();
	LOG_PROCESS_ERROR(m_uSize > 0);

	nRetCode = fread(&uBOM, sizeof(unsigned int), 1, pFile);
	LOG_PROCESS_ERROR(nRetCode == 1);

    LOG_PROCESS_ERROR((uBOM & 0xFFFF) == UTF16_BOM);

	if ((uBOM & 0xFFFF) == UTF16_BOM)
	{
		m_uSize -= 2;
		nRetCode = fseek(pFile, 2, SEEK_SET);
		LOG_PROCESS_ERROR(nRetCode == 0);
	}
	else if ((uBOM & 0xFFFFFF) == UTF8_BOM)
	{
		m_uSize -= 3;
		//nRetCode = pFile->Seek(3, SEEK_SET);
		nRetCode = fseek(pFile, 3, SEEK_SET);
		LOG_PROCESS_ERROR(nRetCode == 0);
	}
	else	// utf8 default
	{
		//nRetCode = pFile->Seek(0, SEEK_SET);
		nRetCode = fseek(pFile, 0, SEEK_SET);
		LOG_PROCESS_ERROR(nRetCode == 0);
	}

	LOG_PROCESS_ERROR(m_pData == NULL);
	m_pData = new char[m_uSize];
    memset(m_pData, 0, m_uSize);
	LOG_PROCESS_ERROR(m_pData);

	nRetCode = fread(m_pData, m_uSize, 1, pFile);
    //nRetCode = pFile->Read(m_pData, (Uint)m_uSize);
	LOG_PROCESS_ERROR(nRetCode == 1);

	//pFile->Close();
	fclose(pFile);
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
        //SAFE_DELETE_ARRAY(pszTmp);
		delete[] pszTmp;
	}

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

	SAFE_DELETE_ARRAY(pszData)

	return true;
Exit0:
	
	if (pFile)
	{
		fclose(pFile);
		pFile = NULL;
	}

	SAFE_DELETE_ARRAY(pszData)
	SAFE_DELETE_ARRAY(pszTmp)

	UnInit();

	return false;
}

bool CTabFile::UnInit(void)
{
	SAFE_DELETE_ARRAY(m_pData)
	SAFE_DELETE_ARRAY(m_pOffsetTable)

    m_mapName2Col.clear();

	return true;
}

int CTabFile::GetRowCount(void)
{
	return m_nRowCount;
}

int CTabFile::GetColCount(void)
{
	return m_nColCount;
}

const char* CTabFile::GetData(int nCol, int nRow)
{
	LOG_PROCESS_ERROR(nCol >= 0 && nCol < m_nColCount);
	LOG_PROCESS_ERROR(nRow >= 0 && nRow < m_nRowCount);

	return m_pData + m_pOffsetTable[nRow * m_nColCount + nCol];
Exit0:
	return NULL;
}

const char* CTabFile::GetData(const char* pcszColName, int nRow)
{
	MAP_NAME_2_COL::iterator it;

	it = m_mapName2Col.find(pcszColName);
	LOG_PROCESS_ERROR(it != m_mapName2Col.end());

	return GetData(it->second, nRow);
Exit0:
	return NULL;
}
