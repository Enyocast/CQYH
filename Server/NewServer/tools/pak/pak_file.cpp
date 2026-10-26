#include "stdafx.h"
#include "pak_file.h"

#include <sys/stat.h>
#include <direct.h>

#include "zlib.h"
#include "pak_def.h"
#include "md5.h"
#include "hash.h"
#include "string_ex.h"

#define MAX_FILE_NAME_LEN		(128)
#define MAX_FILE_COUNT_IN_PAK	(1024 * 128)
#define MAX_PAK_CHUNK_COUNT		(1024 * 128 * 8)
#define INVALID_PAK_FILE_INDEX		(-1)

CPakFile::CPakFile()
{
	m_pFile = NULL;
	memset(m_szFileName, 0, sizeof(m_szFileName));
	m_bUpdateHashTable = FALSE;

	m_pHeader = NULL;
	m_puHashTable = NULL;
	m_pszNameBuffer = NULL;
	m_pFileInfoList = NULL;
	m_pChunkInfoList = NULL;
	m_pnChunkOffsetList = NULL;
	m_nChunkCount = 0;
}

CPakFile::~CPakFile()
{
	Close();
}

BOOL CPakFile::_Alloc(void)
{
	_Free();

	m_pHeader = (PAK_FILE_HEADER*)malloc(sizeof(*m_pHeader));
	LOG_PROCESS_ERROR(m_pHeader);
	memset(m_pHeader, 0, sizeof(*m_pHeader));

	m_puHashTable = (unsigned int*)malloc(sizeof(*m_puHashTable) * MAX_FILE_COUNT_IN_PAK);
	LOG_PROCESS_ERROR(m_puHashTable);
	memset(m_puHashTable, INVALID_FILE_POS, 
		sizeof(*m_puHashTable) * MAX_FILE_COUNT_IN_PAK);

	m_pszNameBuffer = (char*)malloc(sizeof(*m_pszNameBuffer) * MAX_FILE_COUNT_IN_PAK * MAX_FILE_NAME_LEN);
	LOG_PROCESS_ERROR(m_pszNameBuffer);
	memset(m_pszNameBuffer, 0, sizeof(*m_pszNameBuffer) * MAX_FILE_COUNT_IN_PAK * MAX_FILE_NAME_LEN);

	m_pFileInfoList = (PAK_FILE_INFO*)malloc(sizeof(*m_pFileInfoList) * MAX_FILE_COUNT_IN_PAK);
	LOG_PROCESS_ERROR(m_pFileInfoList);
	memset(m_pFileInfoList, 0, sizeof(*m_pFileInfoList) * MAX_FILE_COUNT_IN_PAK);

	m_pChunkInfoList = (PAK_CHUNK_INFO*)malloc(sizeof(*m_pChunkInfoList) * MAX_PAK_CHUNK_COUNT);
	LOG_PROCESS_ERROR(m_pChunkInfoList);
	memset(m_pChunkInfoList, 0, sizeof(*m_pChunkInfoList) * MAX_PAK_CHUNK_COUNT);

	m_pnChunkOffsetList = (int*)malloc(sizeof(*m_pnChunkOffsetList) * MAX_FILE_COUNT_IN_PAK);
	LOG_PROCESS_ERROR(m_pnChunkOffsetList);
	memset(m_pnChunkOffsetList, 0, sizeof(*m_pnChunkOffsetList) * MAX_FILE_COUNT_IN_PAK);

	m_nChunkCount = 0;

	return TRUE;
Exit0:
	_Free();

	return FALSE;
}

BOOL CPakFile::_Free(void)
{
	m_nChunkCount = 0;
	SAFE_FREE(m_pnChunkOffsetList);
	SAFE_FREE(m_pChunkInfoList);
	SAFE_FREE(m_pFileInfoList);
	SAFE_FREE(m_pszNameBuffer);
	SAFE_FREE(m_puHashTable);
	SAFE_FREE(m_pHeader);

	return TRUE;
}

BOOL CPakFile::_UpdateHashTable(void)
{
	LOG_PROCESS_ERROR(m_szFileName[0] != 0);
	LOG_PROCESS_ERROR(m_pHeader);
	LOG_PROCESS_ERROR(m_pFileInfoList);

	if (m_bUpdateHashTable)
	{
		memset(m_puHashTable, INVALID_FILE_POS, 
			sizeof(*m_puHashTable) * MAX_FILE_COUNT_IN_PAK);

		for (int nFileIndex = 0; nFileIndex < m_pHeader->nFileCount; nFileIndex++)
		{
			PAK_FILE_INFO* pFileInfo = m_pFileInfoList + nFileIndex;

			// update hash value
			int nPos = pFileInfo->dwNameHashA % m_pHeader->nFileCount;
			int nTryIndex = 0;
			for (; nTryIndex < m_pHeader->nFileCount; nTryIndex++)
			{
				if (m_puHashTable[nPos] == INVALID_FILE_POS)
				{
					m_puHashTable[nPos] = nFileIndex;
					pFileInfo->dwHashTableIndex = nPos;
					break;
				}

				nPos++;
				if (nPos >= m_pHeader->nFileCount)
					nPos = 0;
			}
			LOG_PROCESS_ERROR(nTryIndex < m_pHeader->nFileCount);
		}
	}
	m_bUpdateHashTable = FALSE;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CPakFile::Create(const char* pcszFileName)
{
	BOOL bResult = FALSE;
	int nRetCode = 0;
	size_t uSize = 0;

	LOG_PROCESS_ERROR(pcszFileName);

	// if opened, return FALSE
	LOG_PROCESS_ERROR(pcszFileName[0] != 0);

	nRetCode = _Alloc();
	LOG_PROCESS_ERROR(nRetCode);

	// open the file
	m_pFile = fopen(pcszFileName, "wb+");
	LOG_PROCESS_ERROR(m_pFile);

	// set file header
	m_pHeader->dwTag = PAK_FILE_TAG;
	m_pHeader->dwVersion = PAK_FILE_VERSION;
	m_pHeader->dwDataOffset = sizeof(*m_pHeader);

	uSize = fwrite(m_pHeader, 1, sizeof(*m_pHeader), m_pFile);
	LOG_PROCESS_ERROR(uSize == sizeof(*m_pHeader));

	strxcpy(m_szFileName, pcszFileName, MAX_PATH - 1);

	bResult = TRUE;
Exit0:
	if (!bResult)
	{
		Close();
	}

	return bResult;
}

BOOL CPakFile::Open(const char* pcszFileName)
{
	BOOL bResult = FALSE;
	int nRetCode = FALSE;
	size_t uSize = 0;
	char* pszBuffer = NULL;
	char* pszNameBuffer = NULL;
	char* pszFileInfoBuffer = NULL;
	char* pszTempFileInfoBuffer = NULL;
	UINT32 dwFileInfoSize = 0;

	LOG_PROCESS_ERROR(pcszFileName);

	// if opened, return FALSE
	LOG_PROCESS_ERROR(m_szFileName[0] == 0);

	// alloc objects
	nRetCode = _Alloc();
	LOG_PROCESS_ERROR(nRetCode);

	// open the file
	m_pFile = fopen(pcszFileName, "rb+");
	PROCESS_ERROR(m_pFile);

	// read file header
	uSize = fread(m_pHeader, 1, sizeof(*m_pHeader), m_pFile);
	LOG_PROCESS_ERROR(uSize == sizeof(*m_pHeader));

	// check version
	LOG_PROCESS_ERROR(m_pHeader->dwTag == PAK_FILE_TAG);
	LOG_PROCESS_ERROR(m_pHeader->dwVersion == PAK_FILE_VERSION);

	// read hash table
	if (!(m_pHeader->dwPackageFlag & PackageFlag_NoHashTable))
	{
		nRetCode = fseek(m_pFile, m_pHeader->dwHashTableOffset, SEEK_SET);
		LOG_PROCESS_ERROR(nRetCode == 0);

		uSize = fread(m_puHashTable, sizeof(*m_puHashTable), m_pHeader->nFileCount, m_pFile);
		LOG_PROCESS_ERROR(uSize == m_pHeader->nFileCount);
	}
	else
	{
		m_bUpdateHashTable = TRUE;
	}

	// if has name buffer, read it
	if (!(m_pHeader->dwPackageFlag & PackageFlag_NoNameBuffer))
	{
		pszNameBuffer = (char*)malloc(sizeof(*pszNameBuffer) * m_pHeader->dwFileNameSize);
		LOG_PROCESS_ERROR(pszNameBuffer);

		if (m_pHeader->dwPackageFlag & PackageFlag_NameBufferCompressed)
		{
			pszBuffer = (char*)malloc(sizeof(*pszBuffer) * m_pHeader->dwNameBufferSize);
			LOG_PROCESS_ERROR(pszBuffer);

			nRetCode = fseek(m_pFile, m_pHeader->dwNameBufferOffset, SEEK_SET);
			LOG_PROCESS_ERROR(nRetCode == 0);

			uSize = fread(pszBuffer, sizeof(*pszBuffer), (size_t)m_pHeader->dwNameBufferSize, m_pFile);
			LOG_PROCESS_ERROR(uSize == m_pHeader->dwNameBufferSize);

			uSize = sizeof(*pszNameBuffer) * m_pHeader->dwFileNameSize;
			nRetCode = uncompress((UINT8*)pszNameBuffer, (ULONG*)(&uSize), (UINT8*)pszBuffer, m_pHeader->dwNameBufferSize);
			LOG_PROCESS_ERROR(nRetCode == Z_OK);

			SAFE_FREE(pszBuffer);
		}
		else
		{
			// check whether sizes matches
			LOG_PROCESS_ERROR(m_pHeader->dwFileNameSize * sizeof(*pszNameBuffer) == 
				m_pHeader->dwNameBufferSize);

			nRetCode = fseek(m_pFile, m_pHeader->dwNameBufferOffset, SEEK_SET);
			LOG_PROCESS_ERROR(nRetCode == 0);

			uSize = fread(pszNameBuffer, sizeof(*pszNameBuffer), m_pHeader->dwFileNameSize, m_pFile);
			LOG_PROCESS_ERROR(uSize == m_pHeader->dwFileNameSize);
		}

		// process name buffer
		LOG_PROCESS_ERROR(m_pszNameBuffer);

		int nFileNameIndex = 0;
		int nNameBufferIndex = 0;
		for (int nIndex = 0; nIndex < m_pHeader->dwFileNameSize; nIndex++)
		{
			m_pszNameBuffer[nFileNameIndex * MAX_FILE_NAME_LEN + nNameBufferIndex] = pszNameBuffer[nIndex];
			nNameBufferIndex++;

			if (pszNameBuffer[nIndex] == 0)
			{
				// disallow empty file name
				LOG_PROCESS_ERROR(m_pszNameBuffer[nFileNameIndex * MAX_FILE_NAME_LEN] != 0);

				nNameBufferIndex = 0;
				nFileNameIndex++;

				// check the count of file name
				LOG_PROCESS_ERROR(nFileNameIndex < MAX_FILE_COUNT_IN_PAK);
			}
		}

		LOG_PROCESS_ERROR(nFileNameIndex == m_pHeader->nFileCount);
		SAFE_FREE(pszNameBuffer);
	}

	// read file info list
	LOG_PROCESS_ERROR(m_pFileInfoList);

	dwFileInfoSize = m_pHeader->dwFileInfoSize;
	pszFileInfoBuffer = (char*)malloc(dwFileInfoSize);
	LOG_PROCESS_ERROR(pszFileInfoBuffer);

	nRetCode = fseek(m_pFile, m_pHeader->dwFileInfoOffset, SEEK_SET);
	LOG_PROCESS_ERROR(nRetCode == 0);

	uSize = fread(pszFileInfoBuffer, 1, (size_t)m_pHeader->dwFileInfoSize, m_pFile);
	LOG_PROCESS_ERROR(uSize == m_pHeader->dwFileInfoSize);

	if (m_pHeader->dwPackageFlag & PackageFlag_FileInfoCompressed)
	{
		pszTempFileInfoBuffer = (char*)malloc(m_pHeader->dwFileInfoSize * 4);
		LOG_PROCESS_ERROR(pszTempFileInfoBuffer);

		dwFileInfoSize = m_pHeader->dwFileInfoSize * 4;
		nRetCode = uncompress((UINT8*)pszTempFileInfoBuffer, (ULONG*)(&dwFileInfoSize), (UINT8*)pszFileInfoBuffer, m_pHeader->dwFileInfoSize);
		LOG_PROCESS_ERROR(nRetCode == Z_OK);

		SAFE_FREE(pszFileInfoBuffer);
		pszFileInfoBuffer = pszTempFileInfoBuffer;
		pszTempFileInfoBuffer = NULL;
	}

	// process file info list
	char* pszPointer = pszFileInfoBuffer;
	int nFileIndex = 0;
	while (pszPointer - pszFileInfoBuffer < dwFileInfoSize)
	{
		PAK_FILE_INFO* pFileInfo = 
			(PAK_FILE_INFO*)pszPointer;

		m_pnChunkOffsetList[nFileIndex] = m_nChunkCount;

		memcpy(m_pFileInfoList + nFileIndex, pFileInfo, sizeof(*pFileInfo));

		pszPointer += sizeof(*pFileInfo);
		LOG_PROCESS_ERROR(pszPointer - pszFileInfoBuffer <= dwFileInfoSize);

		nFileIndex++;

		for (int nChunkIndex = 0; nChunkIndex < pFileInfo->nDataChunkCount; nChunkIndex++)
		{
			PAK_CHUNK_INFO* pChunkInfo =
				(PAK_CHUNK_INFO*)pszPointer;

			memcpy(m_pChunkInfoList + m_nChunkCount, pChunkInfo, sizeof(*pChunkInfo));

			pszPointer += sizeof(*pChunkInfo);
			LOG_PROCESS_ERROR(pszPointer - pszFileInfoBuffer <= dwFileInfoSize);

			m_nChunkCount++;
			LOG_PROCESS_ERROR(m_nChunkCount < MAX_PAK_CHUNK_COUNT);
		}
	}

	// copy file name which means the file is loaded successfully
	strxcpy(m_szFileName, pcszFileName, MAX_PATH - 1);

	bResult = TRUE;

Exit0:
	if (!bResult)
		Close();

	SAFE_FREE(pszBuffer);
	SAFE_FREE(pszNameBuffer);
	SAFE_FREE(pszFileInfoBuffer);

	return bResult;
}

BOOL CPakFile::Close(void)
{
	BOOL bResult = FALSE;
	int nRetCode = 0;
	size_t uSize = 0;
	char* pszBuffer = NULL;
	char* pszFileInfoBuffer = NULL;
	char* pszTempFileInfoBuffer = NULL;

	// if opened, process hash table, name buffer and file info list
	if (m_szFileName[0] != 0)
	{
		LOG_PROCESS_ERROR(m_pHeader);
		LOG_PROCESS_ERROR(m_pFileInfoList);
		LOG_PROCESS_ERROR(m_pszNameBuffer);
		LOG_PROCESS_ERROR(m_pChunkInfoList);
		LOG_PROCESS_ERROR(m_pnChunkOffsetList);
		char* pszNameBuffer = m_pszNameBuffer;

		m_bUpdateHashTable = TRUE;
		nRetCode = _UpdateHashTable();
		LOG_PROCESS_ERROR(nRetCode);

		size_t uFileInfoBufferSize = sizeof(*m_pFileInfoList) * m_pHeader->nFileCount +
			sizeof(*m_pChunkInfoList) * m_nChunkCount;
		uFileInfoBufferSize = uFileInfoBufferSize / 2 * 3;
		pszFileInfoBuffer = (char*)malloc(uFileInfoBufferSize);
		LOG_PROCESS_ERROR(pszFileInfoBuffer);

		char* pszPointer = pszFileInfoBuffer;
		int nChunkCount = 0;

		for (int nFileIndex = 0; nFileIndex < m_pHeader->nFileCount; nFileIndex++)
		{
			PAK_FILE_INFO* pFileInfo = m_pFileInfoList + nFileIndex;

			// update file info
			pFileInfo->dwFileNameOffset = pszNameBuffer - m_pszNameBuffer;

			// update name buffer
			int nIndex = 0;
			while (nIndex < MAX_FILE_NAME_LEN && m_pszNameBuffer[nFileIndex * MAX_FILE_NAME_LEN + nIndex] != 0)
			{
				*pszNameBuffer = m_pszNameBuffer[nFileIndex * MAX_FILE_NAME_LEN + nIndex];
				pszNameBuffer++;
				nIndex++;
			}

			*pszNameBuffer = 0;
			pszNameBuffer++;

			// update file info buffer
			memcpy(pszPointer, pFileInfo, sizeof(*pFileInfo));

			pszPointer += sizeof(*pFileInfo);
			LOG_PROCESS_ERROR(pszPointer - pszFileInfoBuffer <= uFileInfoBufferSize);

			for (int nChunkIndex = 0; nChunkIndex < pFileInfo->nDataChunkCount; nChunkIndex++)
			{
				LOG_PROCESS_ERROR(m_pnChunkOffsetList[nFileIndex] + nChunkIndex <
					MAX_PAK_CHUNK_COUNT);
				PAK_CHUNK_INFO* pChunkInfo =
					m_pChunkInfoList + m_pnChunkOffsetList[nFileIndex] + nChunkIndex;

				memcpy(pszPointer, pChunkInfo, sizeof(*pChunkInfo));

				pszPointer += sizeof(*pChunkInfo);
				LOG_PROCESS_ERROR(pszPointer - pszFileInfoBuffer <= uFileInfoBufferSize);
			}

			nChunkCount += pFileInfo->nDataChunkCount;
			LOG_PROCESS_ERROR(nChunkCount <= m_nChunkCount);
		}

		if (m_pHeader->dwPackageFlag & PackageFlag_NoNameBuffer)
			m_pHeader->dwFileNameSize = 0;
		else
			m_pHeader->dwFileNameSize = pszNameBuffer - m_pszNameBuffer;

		uFileInfoBufferSize = pszPointer - pszFileInfoBuffer;
		if ((m_pHeader->dwPackageFlag & PackageFlag_FileInfoCompressed) && uFileInfoBufferSize > 0)
		{
			pszTempFileInfoBuffer = (char*)malloc(uFileInfoBufferSize * 3 / 2);
			LOG_PROCESS_ERROR(pszTempFileInfoBuffer);

			size_t uCompressedSize = uFileInfoBufferSize * 3 / 2;
			nRetCode = compress((UINT8*)pszTempFileInfoBuffer, (unsigned long*)&uCompressedSize, (UINT8*)pszFileInfoBuffer, uFileInfoBufferSize);
			LOG_PROCESS_ERROR(nRetCode == Z_OK);

			SAFE_FREE(pszFileInfoBuffer);
			pszFileInfoBuffer = pszTempFileInfoBuffer;
			pszTempFileInfoBuffer = NULL;
			uFileInfoBufferSize = uCompressedSize;
		}

		// Get the end of the pak file which may be appended
		nRetCode = fseek(m_pFile, 0, SEEK_END);
		LOG_PROCESS_ERROR(nRetCode == 0);

		size_t uFileSize = ftell(m_pFile);
		size_t uEndOffset = 0;
		if (m_pHeader->dwPackageFlag & PackageFlag_NoHashTable &&
			m_pHeader->dwPackageFlag & PackageFlag_NoNameBuffer)
		{
			uSize = m_pHeader->dwFileInfoSize;
			if (m_pHeader->dwFileInfoOffset + uSize == uFileSize)
				uEndOffset = m_pHeader->dwFileInfoOffset;
			else
				uEndOffset = uFileSize;
		}
		else if (m_pHeader->dwPackageFlag & PackageFlag_NoHashTable)
		{
			uSize = m_pHeader->dwNameBufferSize + m_pHeader->dwFileInfoSize;
			if (m_pHeader->dwNameBufferOffset + uSize == uFileSize)
				uEndOffset = m_pHeader->dwNameBufferOffset;
			else if (m_pHeader->dwFileInfoOffset + uSize == uFileSize)
				uEndOffset = m_pHeader->dwFileInfoOffset;
			else
				uEndOffset = uFileSize;
		}
		else if (m_pHeader->dwPackageFlag & PackageFlag_NoNameBuffer)
		{
			uSize = m_pHeader->dwHashTableSize + m_pHeader->dwFileInfoSize;
			if (m_pHeader->dwHashTableOffset + uSize == uFileSize)
				uEndOffset = m_pHeader->dwHashTableOffset;
			else if (m_pHeader->dwFileInfoOffset + uSize == uFileSize)
				uEndOffset = m_pHeader->dwFileInfoOffset;
			else
				uEndOffset = uFileSize;
		}
		else
		{
			uSize = m_pHeader->dwHashTableSize + m_pHeader->dwNameBufferSize + m_pHeader->dwFileInfoSize;
			if (m_pHeader->dwHashTableOffset + uSize == uFileSize)
				uEndOffset = m_pHeader->dwHashTableOffset;
			else if (m_pHeader->dwNameBufferOffset + uSize == uFileSize)
				uEndOffset = m_pHeader->dwNameBufferOffset;
			else if (m_pHeader->dwFileInfoOffset + uSize == uFileSize)
				uEndOffset = m_pHeader->dwFileInfoOffset;
			else
				uEndOffset = uFileSize;
		}

		nRetCode = fseek(m_pFile, uEndOffset, SEEK_SET);
		LOG_PROCESS_ERROR(nRetCode == 0);

		// write hash table
		if (m_pHeader->dwPackageFlag & PackageFlag_NoHashTable)
		{
			m_pHeader->dwHashTableOffset = 0;
			m_pHeader->dwHashTableSize = 0;
		}
		else
		{
			m_pHeader->dwHashTableOffset = ftell(m_pFile);
			m_pHeader->dwHashTableSize = sizeof(*m_puHashTable) * m_pHeader->nFileCount;
			uSize = fwrite(m_puHashTable, sizeof(*m_puHashTable), m_pHeader->nFileCount, m_pFile);
			LOG_PROCESS_ERROR(uSize == m_pHeader->nFileCount);
		}

		// write name buffer
		if (m_pHeader->dwPackageFlag & PackageFlag_NoNameBuffer)
		{
			m_pHeader->dwNameBufferOffset = 0;
			m_pHeader->dwNameBufferSize = 0;
		}
		else
		{
			if (m_pHeader->dwPackageFlag & PackageFlag_NameBufferCompressed)
			{
				size_t uBufferSize = sizeof(*m_pszNameBuffer) * m_pHeader->dwFileNameSize;
				if (uBufferSize < ONE_CHUNK_SIZE)
					uBufferSize = ONE_CHUNK_SIZE;
				pszBuffer = (char*)malloc(uBufferSize);
				LOG_PROCESS_ERROR(pszBuffer);

				size_t uCompressedSize = uBufferSize;
				nRetCode = compress((UINT8*)pszBuffer, (unsigned long*)&uCompressedSize, (UINT8*)m_pszNameBuffer, sizeof(*m_pszNameBuffer) * m_pHeader->dwFileNameSize);
				LOG_PROCESS_ERROR(nRetCode == Z_OK);

				m_pHeader->dwNameBufferOffset = ftell(m_pFile);
				m_pHeader->dwNameBufferSize = uCompressedSize;

				uSize = fwrite(pszBuffer, 1, uCompressedSize, m_pFile);
				LOG_PROCESS_ERROR(uSize == uCompressedSize);

				SAFE_FREE(pszBuffer);
			}
			else
			{
				m_pHeader->dwNameBufferOffset = ftell(m_pFile);
				m_pHeader->dwNameBufferSize = sizeof(*m_pszNameBuffer) * m_pHeader->dwFileNameSize;

				uSize = fwrite(m_pszNameBuffer, sizeof(*m_pszNameBuffer), m_pHeader->dwFileNameSize, m_pFile);
				LOG_PROCESS_ERROR(uSize == m_pHeader->dwFileNameSize);
			}
		}

		// write file info and chunk info
		m_pHeader->dwFileInfoOffset = ftell(m_pFile);
		m_pHeader->dwFileInfoSize = uFileInfoBufferSize;

		uSize = fwrite(pszFileInfoBuffer, 1, uFileInfoBufferSize, m_pFile);
		LOG_PROCESS_ERROR(uSize == uFileInfoBufferSize);

		// write header
		nRetCode = fseek(m_pFile, 0, SEEK_SET);
		LOG_PROCESS_ERROR(nRetCode == 0);

		uSize = fwrite(m_pHeader, 1, sizeof(*m_pHeader), m_pFile);
		LOG_PROCESS_ERROR(uSize == sizeof(*m_pHeader));
	}

	bResult = TRUE;
Exit0:
	if (m_pFile)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}

	_Free();

	memset(m_szFileName, 0, sizeof(m_szFileName));

	SAFE_FREE(pszBuffer);
	SAFE_FREE(pszFileInfoBuffer);
	SAFE_FREE(pszTempFileInfoBuffer);

	return bResult;
}

BOOL CPakFile::IsOpened(void)
{
	return m_szFileName[0] != 0;
}

BOOL CPakFile::SetPackageFlag(BOOL bHasHashTable, BOOL bHasNameBuffer, BOOL bCompressNameBuffer, BOOL bCompressFileInfo)
{
	LOG_PROCESS_ERROR(m_szFileName[0] != 0);
	LOG_PROCESS_ERROR(m_pHeader);

	m_pHeader->dwPackageFlag = 0;

	if (!bHasHashTable)
		m_pHeader->dwPackageFlag |= PackageFlag_NoHashTable;
	if (!bHasNameBuffer)
		m_pHeader->dwPackageFlag |= PackageFlag_NoNameBuffer;
	if (bCompressNameBuffer)
		m_pHeader->dwPackageFlag |= PackageFlag_NameBufferCompressed;
	if (bCompressFileInfo)
		m_pHeader->dwPackageFlag |= PackageFlag_FileInfoCompressed;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CPakFile::AddFile(const char* pcszPakFileName, const char* pcszFileName)
{
	BOOL bResult = FALSE;
	int nRetCode = 0;
	size_t uSize = 0;
	FILE* pAddFile = NULL;
	char* pszBuffer = NULL;

	LOG_PROCESS_ERROR(pcszFileName);
	LOG_PROCESS_ERROR(pcszPakFileName);

	// If not opened, return FALSE
	LOG_PROCESS_ERROR(m_szFileName[0] != 0);
	LOG_PROCESS_ERROR(FindFile(pcszPakFileName) == INVALID_PAK_FILE_INDEX);

	// open the file
	pAddFile = fopen(pcszFileName, "rb");
	LOG_PROCESS_ERROR(pAddFile);

	// get file size
	nRetCode = fseek(pAddFile, 0, SEEK_END);
	LOG_PROCESS_ERROR(nRetCode == 0);

	size_t uFileSize = ftell(pAddFile);

	// malloc buffer to read
	pszBuffer = (char*)malloc(uFileSize);
	LOG_PROCESS_ERROR(pszBuffer);

	// read the whole file
	nRetCode = fseek(pAddFile, 0, SEEK_SET);
	LOG_PROCESS_ERROR(nRetCode == 0);

	uSize = fread(pszBuffer, 1, uFileSize, pAddFile);
	LOG_PROCESS_ERROR(uSize == uFileSize);

	// get file information
	int fd = fileno(pAddFile);
	LOG_PROCESS_ERROR(fd != -1);

	struct stat FileStat;
	nRetCode = fstat(fd, &FileStat);
	LOG_PROCESS_ERROR(nRetCode == 0);

	nRetCode = AddFileFromData(pcszPakFileName, FileStat.st_ctime, 
		FileStat.st_mtime, pszBuffer, uFileSize);
	LOG_PROCESS_ERROR(nRetCode);

	bResult = TRUE;
Exit0:
	SAFE_FREE(pszBuffer);

	if (pAddFile)
		fclose(pAddFile);

	return bResult;
}

BOOL CPakFile::AddFileFromPak(const char* pcszPakFileName, CPakFile* pPakFile, int nFileIndex)
{
	BOOL bResult = FALSE;
	int nRetCode = 0;
	char* pszBuffer = NULL;

	LOG_PROCESS_ERROR(pcszPakFileName);
	LOG_PROCESS_ERROR(pPakFile);
	LOG_PROCESS_ERROR(pPakFile->IsOpened());
	LOG_PROCESS_ERROR(pPakFile->m_pHeader);
	LOG_PROCESS_ERROR(pPakFile->m_pFileInfoList);
	LOG_PROCESS_ERROR(pPakFile->m_pChunkInfoList);
	LOG_PROCESS_ERROR(pPakFile->m_pnChunkOffsetList);

	PAK_FILE_INFO* pFileInfo = 
		pPakFile->m_pFileInfoList + nFileIndex;

	LOG_PROCESS_ERROR(pPakFile->m_pnChunkOffsetList[nFileIndex] < MAX_PAK_CHUNK_COUNT);
	PAK_CHUNK_INFO* pChunkInfo = 
		pPakFile->m_pChunkInfoList + pPakFile->m_pnChunkOffsetList[nFileIndex];

	size_t uDataSize = 0;
	if (pFileInfo->dwFileFlag & FileFlag_NoCompressed)
		uDataSize = pFileInfo->dwOriginalSize;
	else
		uDataSize = pFileInfo->dwCompressedSize;

	pszBuffer = (char*)malloc(uDataSize);
	LOG_PROCESS_ERROR(pszBuffer);

	nRetCode = fseek(pPakFile->m_pFile, pPakFile->m_pHeader->dwDataOffset + pFileInfo->dwChunkStartOffset, SEEK_SET);
	LOG_PROCESS_ERROR(nRetCode == 0);

	size_t uSize = fread(pszBuffer, 1, uDataSize, pPakFile->m_pFile);
	LOG_PROCESS_ERROR(uSize == uDataSize);

	nRetCode = _AddFileFromRawData(pcszPakFileName, pFileInfo, pChunkInfo, pszBuffer, uDataSize);
	LOG_PROCESS_ERROR(nRetCode);

	SAFE_FREE(pszBuffer);

	bResult = TRUE;
Exit0:
	SAFE_FREE(pszBuffer);

	return bResult;
}

BOOL CPakFile::AddFileFromData(const char* pcszPakFileName, time_t CreateTime, 
							   time_t ModifyTime, const char* pszFileData, size_t uDataSize)
{
	BOOL bResult = FALSE;
	int nRetCode = 0;
	size_t uSize = 0;
	char* pszBuffer = NULL;
	md5_ctx* pCtx= NULL;

	LOG_PROCESS_ERROR(pcszPakFileName);
	LOG_PROCESS_ERROR(pszFileData);

	// if not opened, return FALSE
	LOG_PROCESS_ERROR(m_szFileName[0] != 0);

	LOG_PROCESS_ERROR(m_pHeader);
	LOG_PROCESS_ERROR(m_puHashTable);
	LOG_PROCESS_ERROR(m_pszNameBuffer);
	LOG_PROCESS_ERROR(m_pFileInfoList);
	LOG_PROCESS_ERROR(m_pnChunkOffsetList);
	LOG_PROCESS_ERROR(m_pHeader->nFileCount < MAX_FILE_COUNT_IN_PAK);

	LOG_PROCESS_ERROR(FindFile(pcszPakFileName) == INVALID_PAK_FILE_INDEX);

	// save file info
	PAK_FILE_INFO* pFileInfo = m_pFileInfoList + m_pHeader->nFileCount;

	memset(pFileInfo, 0, sizeof(*pFileInfo));

	// file time
	pFileInfo->dwCreateTime = CreateTime;
	pFileInfo->dwModifyTime = ModifyTime;
	pFileInfo->dwOriginalSize = uDataSize;

	// calculate chunk size
	size_t uChunkSize = 0;
	if (uDataSize < ONE_CHUNK_SIZE)
		uChunkSize = uDataSize;
	else
		uChunkSize = DEFAULT_CHUNK_SIZE;
	pFileInfo->dwChunkSize = uChunkSize;

	// calculate hash values of file name
	hash_file_name(pcszPakFileName, &pFileInfo->dwNameHashA, &pFileInfo->dwNameHashB);

	// save file name
	LOG_PROCESS_ERROR(strlen(pcszPakFileName) < MAX_FILE_NAME_LEN);
	strxcpy(m_pszNameBuffer + m_pHeader->nFileCount * MAX_FILE_NAME_LEN, pcszPakFileName, MAX_FILE_NAME_LEN - 1);

	// calculate MD5 value of original file
	calc_md5(pFileInfo->md5OriginDataHash, (UINT8*)pszFileData, uDataSize);

	// set chunk start offset to the end of pak file
	nRetCode = fseek(m_pFile, 0, SEEK_END);
	LOG_PROCESS_ERROR(nRetCode == 0);

	pFileInfo->dwChunkStartOffset = ftell(m_pFile) - m_pHeader->dwDataOffset;
	m_pnChunkOffsetList[m_pHeader->nFileCount] = m_nChunkCount;

	// write file data to pak file

	if (uDataSize < uChunkSize)
		pFileInfo->dwFileFlag = FileFlag_NoCompressed;

	if (pFileInfo->dwFileFlag & FileFlag_NoCompressed)
	{
		// calculate chunk count and chunk info
		if (uDataSize % uChunkSize == 0)
			pFileInfo->nDataChunkCount = uDataSize / uChunkSize;
		else
			pFileInfo->nDataChunkCount = uDataSize / uChunkSize + 1;

		LOG_PROCESS_ERROR(m_nChunkCount + pFileInfo->nDataChunkCount < MAX_PAK_CHUNK_COUNT);
		for (int nChunkIndex = 0; nChunkIndex < pFileInfo->nDataChunkCount; nChunkIndex++)
		{
			m_pChunkInfoList[m_nChunkCount + nChunkIndex].dwChunkSize = pFileInfo->dwChunkSize;
			m_pChunkInfoList[m_nChunkCount + nChunkIndex].dwChunkOffset = 
				ftell(m_pFile) + nChunkIndex * pFileInfo->dwChunkSize - m_pHeader->dwDataOffset;
		}
		m_nChunkCount += pFileInfo->nDataChunkCount;
		if ((uDataSize % uChunkSize) != 0)
			m_pChunkInfoList[m_nChunkCount - 1].dwChunkSize = uDataSize % uChunkSize;

		uSize = fwrite(pszFileData, 1, uDataSize, m_pFile);
		LOG_PROCESS_ERROR(uSize == uDataSize);

		m_pHeader->dwDataSize += uSize;
	}
	else
	{
		size_t uBufferSize = uChunkSize < ONE_CHUNK_SIZE ? ONE_CHUNK_SIZE : uChunkSize;
		pszBuffer = (char*)malloc(uBufferSize);
		LOG_PROCESS_ERROR(pszBuffer);

		size_t uTotalProcessedSize = 0;
		size_t uTotalCompressedSize = 0;

		pCtx = md5_init();
		LOG_PROCESS_ERROR(pCtx);

		while (uTotalProcessedSize < uDataSize)
		{
			size_t uProcessedSize = (uDataSize - uTotalProcessedSize) < uChunkSize ? 
				(uDataSize - uTotalProcessedSize) : uChunkSize;

			size_t uCompressedSize = uBufferSize;
			nRetCode = compress((UINT8*)pszBuffer, (unsigned long*)&uCompressedSize, (UINT8*)pszFileData + uTotalProcessedSize, uProcessedSize);
			LOG_PROCESS_ERROR(nRetCode == Z_OK);

			md5_update(pCtx, (UINT8*)pszBuffer, uCompressedSize);

			m_pChunkInfoList[m_nChunkCount].dwChunkSize = uCompressedSize;
			m_pChunkInfoList[m_nChunkCount].dwChunkOffset = ftell(m_pFile) - m_pHeader->dwDataOffset;
			m_nChunkCount++;
			pFileInfo->nDataChunkCount++;

			uSize = fwrite(pszBuffer, 1, uCompressedSize, m_pFile);
			LOG_PROCESS_ERROR(uSize == uCompressedSize);

			uTotalCompressedSize += uCompressedSize;
			uTotalProcessedSize += uProcessedSize;
		}
		LOG_PROCESS_ERROR(uTotalProcessedSize == uDataSize);

		md5_final(pFileInfo->md5CompressedDataHash, pCtx);

		pFileInfo->dwCompressedSize = uTotalCompressedSize;
		m_pHeader->dwDataSize += uTotalCompressedSize;
	}

	m_bUpdateHashTable = TRUE;
	m_pHeader->nFileCount++;

	bResult = TRUE;

Exit0:
	SAFE_FREE(pszBuffer);

	return bResult;
}

BOOL CPakFile::_AddFileFromRawData(const char* pcszPakFileName, 
								   const PAK_FILE_INFO* pFileInfo, 
								   const PAK_CHUNK_INFO* pChunkInfo,
								   const char* pszFileData, size_t uDataSize)
{
	BOOL bResult = FALSE;
	int nRetCode = 0;
	size_t uSize = 0;
	char* pszBuffer = NULL;
	PAK_FILE_INFO* pDestFileInfo = NULL;

	LOG_PROCESS_ERROR(pcszPakFileName);
	LOG_PROCESS_ERROR(pFileInfo);
	LOG_PROCESS_ERROR(pChunkInfo);
	LOG_PROCESS_ERROR(pszFileData);
	LOG_PROCESS_ERROR((pFileInfo->dwFileFlag & FileFlag_Deleted) == 0);

	// if not opened, return FALSE
	LOG_PROCESS_ERROR(m_szFileName[0] != 0);

	LOG_PROCESS_ERROR(m_pHeader);
	LOG_PROCESS_ERROR(m_puHashTable);
	LOG_PROCESS_ERROR(m_pszNameBuffer);
	LOG_PROCESS_ERROR(m_pFileInfoList);
	LOG_PROCESS_ERROR(m_pChunkInfoList);
	LOG_PROCESS_ERROR(m_pnChunkOffsetList);

	int nFileIndex = FindFile(pcszPakFileName);
	if (nFileIndex == INVALID_PAK_FILE_INDEX)
	{
		LOG_PROCESS_ERROR(m_pHeader->nFileCount < MAX_FILE_COUNT_IN_PAK);
		nFileIndex = m_pHeader->nFileCount;
	}
	else
	{
		if (m_pFileInfoList[nFileIndex].dwOriginalSize == pFileInfo->dwOriginalSize)
		{
			BOOL bSame = TRUE;
			for (int nIndex = 0; nIndex < 16; nIndex++)
			{
				if (m_pFileInfoList[nFileIndex].md5OriginDataHash[nIndex] !=
					pFileInfo->md5OriginDataHash[nIndex])
				{
					bSame = FALSE;
					break;
				}
			}
			if (bSame)
				goto Exit1;
		}
	}
	pDestFileInfo = m_pFileInfoList + nFileIndex;

	// save file name
	LOG_PROCESS_ERROR(strlen(pcszPakFileName) < MAX_FILE_NAME_LEN);
	strxcpy(m_pszNameBuffer + nFileIndex * MAX_FILE_NAME_LEN, pcszPakFileName, MAX_FILE_NAME_LEN - 1);

	// save file info
	memcpy(pDestFileInfo, pFileInfo, sizeof(*pFileInfo));

	// set chunk start offset to the end of pak file
	nRetCode = fseek(m_pFile, 0, SEEK_END);
	LOG_PROCESS_ERROR(nRetCode == 0);

	pDestFileInfo->dwChunkStartOffset = ftell(m_pFile) - m_pHeader->dwDataOffset;

	// save chunk info
	m_pnChunkOffsetList[nFileIndex] = m_nChunkCount;

	LOG_PROCESS_ERROR(m_nChunkCount + pFileInfo->nDataChunkCount < MAX_PAK_CHUNK_COUNT);
	memcpy(m_pChunkInfoList + m_nChunkCount, pChunkInfo, sizeof(*pChunkInfo) * pFileInfo->nDataChunkCount);

	size_t uChunkOffset = pDestFileInfo->dwChunkStartOffset;
	for (int nChunkIndex = 0; nChunkIndex < pFileInfo->nDataChunkCount; nChunkIndex++)
	{
		m_pChunkInfoList[m_nChunkCount + nChunkIndex].dwChunkOffset = uChunkOffset;
		uChunkOffset += m_pChunkInfoList[m_nChunkCount + nChunkIndex].dwChunkSize;
	}

	// write file data to pak file
	uSize = fwrite(pszFileData, 1, uDataSize, m_pFile);
	LOG_PROCESS_ERROR(uSize == uDataSize);
	LOG_PROCESS_ERROR(m_pHeader->dwDataOffset + uChunkOffset == ftell(m_pFile));

	m_nChunkCount += pFileInfo->nDataChunkCount;
	m_pHeader->dwDataSize += uSize;
	if (nFileIndex == m_pHeader->nFileCount)
		m_pHeader->nFileCount++;
	m_bUpdateHashTable = TRUE;

Exit1:
	bResult = TRUE;

Exit0:
	SAFE_FREE(pszBuffer);

	return bResult;
}

BOOL CPakFile::DelFile(const char* pcszPakFileName)
{
	int nFileIndex = FindFile(pcszPakFileName);
	PROCESS_ERROR(nFileIndex != INVALID_PAK_FILE_INDEX);

	m_pFileInfoList[nFileIndex].dwFileFlag |= FileFlag_Deleted;

	return TRUE;

Exit0:

	return FALSE;
}

int CPakFile::FindFile(const char* pcszPakFileName)
{
	int nResult = INVALID_PAK_FILE_INDEX;
	int nRetCode = 0;

	LOG_PROCESS_ERROR(pcszPakFileName);

	LOG_PROCESS_ERROR(m_szFileName[0] != 0);
	LOG_PROCESS_ERROR(m_pHeader);
	LOG_PROCESS_ERROR(m_pszNameBuffer);
	LOG_PROCESS_ERROR(m_pFileInfoList);

	nRetCode = _UpdateHashTable();
	LOG_PROCESS_ERROR(nRetCode);

	if (m_pHeader->nFileCount > 0)
	{
		UINT32 dwHashA, dwHashB;
		hash_file_name(pcszPakFileName, &dwHashA, &dwHashB);

		int nPos = dwHashA % m_pHeader->nFileCount;
		int nTryIndex = 0;
		int nFileIndex = m_puHashTable[nPos];
		for (; nTryIndex < m_pHeader->nFileCount; nTryIndex++)
		{
			if (m_pFileInfoList[nFileIndex].dwNameHashB == dwHashB)
				break;
			nPos++;
			if (nPos >= m_pHeader->nFileCount)
				nPos = 0;
			nFileIndex = m_puHashTable[nPos];
		}
		PROCESS_ERROR(nTryIndex < m_pHeader->nFileCount);

		nResult = nFileIndex;
	}

Exit0:

	return nResult;
}

int CPakFile::GetFileCount(void)
{
	LOG_PROCESS_ERROR(m_szFileName[0] != 0);

	LOG_PROCESS_ERROR(m_pHeader);

	return m_pHeader->nFileCount;
Exit0:
	return -1;
}

size_t CPakFile::GetFileSize(int nFileIndex)
{
	LOG_PROCESS_ERROR(m_szFileName[0] != 0);

	LOG_PROCESS_ERROR(m_pHeader);
	LOG_PROCESS_ERROR(m_pFileInfoList);

	LOG_PROCESS_ERROR(nFileIndex >= 0 && nFileIndex < m_pHeader->nFileCount);

	return m_pFileInfoList[nFileIndex].dwOriginalSize;

Exit0:

	return 0;
}

const char* CPakFile::GetFileName(int nFileIndex)
{
	LOG_PROCESS_ERROR(nFileIndex >= 0 && nFileIndex < m_pHeader->nFileCount);
	LOG_PROCESS_ERROR(m_szFileName[0] != 0);
	LOG_PROCESS_ERROR(m_pHeader);

	if (m_pHeader->dwPackageFlag & PackageFlag_NoNameBuffer)
	{
		static char s_szFileName[MAX_FILE_NAME_LEN];

		LOG_PROCESS_ERROR(m_pFileInfoList);
		snprintf(s_szFileName, MAX_FILE_NAME_LEN, "%08X_%08X.dat", m_pFileInfoList[nFileIndex].dwNameHashA, m_pFileInfoList[nFileIndex].dwNameHashB);

		return s_szFileName;
	}
	else
	{
		LOG_PROCESS_ERROR(m_pszNameBuffer);

		return m_pszNameBuffer + nFileIndex * MAX_FILE_NAME_LEN;
	}

Exit0:

	return NULL;
}

BOOL CPakFile::GetFileHashValue(int nFileIndex, unsigned long& rulHashValueA, unsigned long& rulHashValueB)
{
	LOG_PROCESS_ERROR(m_szFileName[0] != 0);

	LOG_PROCESS_ERROR(m_pHeader);
	LOG_PROCESS_ERROR(m_pFileInfoList);
	LOG_PROCESS_ERROR(nFileIndex >= 0 && nFileIndex < m_pHeader->nFileCount);

	rulHashValueA = m_pFileInfoList[nFileIndex].dwNameHashA;
	rulHashValueB = m_pFileInfoList[nFileIndex].dwNameHashB;

	return TRUE;

Exit0:

	return FALSE;
}

BOOL CPakFile::IsDeletedFile(int nFileIndex)
{
	LOG_PROCESS_ERROR(m_szFileName[0] != 0);

	LOG_PROCESS_ERROR(m_pHeader);
	LOG_PROCESS_ERROR(m_pFileInfoList);
	LOG_PROCESS_ERROR(nFileIndex >= 0 && nFileIndex < m_pHeader->nFileCount);

	return (m_pFileInfoList[nFileIndex].dwFileFlag & FileFlag_Deleted) != 0;

Exit0:

	return FALSE;
}

BOOL CPakFile::GetFileMD5Value(int nFileIndex, unsigned char ucMD5Value[16])
{
	LOG_PROCESS_ERROR(m_szFileName[0] != 0);

	LOG_PROCESS_ERROR(m_pHeader);
	LOG_PROCESS_ERROR(m_pFileInfoList);
	LOG_PROCESS_ERROR(nFileIndex >= 0 && nFileIndex < m_pHeader->nFileCount);

	memcpy(ucMD5Value, m_pFileInfoList[nFileIndex].md5OriginDataHash, 16);

	return TRUE;

Exit0:

	return FALSE;
}

BOOL CPakFile::ReadFileData(int nFileIndex, char* pszFileData, size_t uDataSize)
{
	int nRetCode = 0;
	size_t uSize = 0;
	char* pszBuffer = NULL;

	LOG_PROCESS_ERROR(pszFileData);

	LOG_PROCESS_ERROR(m_szFileName[0] != 0);
	LOG_PROCESS_ERROR(m_pHeader);
	LOG_PROCESS_ERROR(m_pFileInfoList);
	LOG_PROCESS_ERROR(m_pChunkInfoList);
	LOG_PROCESS_ERROR(m_pnChunkOffsetList);

	LOG_PROCESS_ERROR(nFileIndex >= 0 && nFileIndex < m_pHeader->nFileCount);

	PAK_FILE_INFO* pFileInfo = m_pFileInfoList + nFileIndex;
	LOG_PROCESS_ERROR(uDataSize <= pFileInfo->dwOriginalSize);

	nRetCode = fseek(m_pFile, m_pHeader->dwDataOffset + pFileInfo->dwChunkStartOffset, SEEK_SET);
	LOG_PROCESS_ERROR(nRetCode == 0);

	if (pFileInfo->dwFileFlag & FileFlag_NoCompressed)
	{
		uSize = fread(pszFileData, 1, uDataSize, m_pFile);
		LOG_PROCESS_ERROR(uSize == uDataSize);
	}
	else
	{
		size_t uTotalDecompressedSize = 0;
		pszBuffer = (char*)malloc(ONE_CHUNK_SIZE);

		LOG_PROCESS_ERROR(m_pnChunkOffsetList[nFileIndex] < MAX_PAK_CHUNK_COUNT);
		PAK_CHUNK_INFO* pChunkInfo = 
			m_pChunkInfoList + m_pnChunkOffsetList[nFileIndex];

		for (int nChunkIndex = 0; nChunkIndex < pFileInfo->nDataChunkCount; nChunkIndex++)
		{
			LOG_PROCESS_ERROR(ftell(m_pFile) == (pChunkInfo[nChunkIndex].dwChunkOffset + m_pHeader->dwDataOffset));
			LOG_PROCESS_ERROR(pChunkInfo[nChunkIndex].dwChunkSize < ONE_CHUNK_SIZE);

			uSize = fread(pszBuffer, 1, pChunkInfo[nChunkIndex].dwChunkSize, m_pFile);
			LOG_PROCESS_ERROR(uSize == pChunkInfo[nChunkIndex].dwChunkSize);

			size_t uDecompressedSize = uDataSize - uTotalDecompressedSize;
			nRetCode = uncompress((UINT8*)pszFileData + uTotalDecompressedSize, (ULONG*)&uDecompressedSize, 
				(UINT8*)pszBuffer, pChunkInfo[nChunkIndex].dwChunkSize);
			LOG_PROCESS_ERROR(nRetCode == Z_OK);

			uTotalDecompressedSize += uDecompressedSize;
		}
		LOG_PROCESS_ERROR(uTotalDecompressedSize == uDataSize);
	}

	SAFE_FREE(pszBuffer);

	return TRUE;
Exit0:
	SAFE_FREE(pszBuffer);

	return FALSE;
}

BOOL CPakFile::VerifyFile(int nFileIndex)
{
	int nRetCode = 0;
	char* pszBuffer = NULL;
	unsigned char ucMD5Value[16];

	LOG_PROCESS_ERROR(m_szFileName[0] != 0);

	LOG_PROCESS_ERROR(m_pHeader);
	LOG_PROCESS_ERROR(m_pFileInfoList);

	LOG_PROCESS_ERROR(nFileIndex >= 0 && nFileIndex < m_pHeader->nFileCount);

	pszBuffer = (char*)malloc(m_pFileInfoList[nFileIndex].dwOriginalSize);
	LOG_PROCESS_ERROR(pszBuffer);

	nRetCode = ReadFileData(nFileIndex, pszBuffer, m_pFileInfoList[nFileIndex].dwOriginalSize);
	LOG_PROCESS_ERROR(nRetCode);

	calc_md5(ucMD5Value, (UINT8*)pszBuffer, m_pFileInfoList[nFileIndex].dwOriginalSize);

	for (int nIndex = 0; nIndex < 16; nIndex++)
	{
		LOG_PROCESS_ERROR(ucMD5Value[nIndex] == m_pFileInfoList[nFileIndex].md5OriginDataHash[nIndex]);
	}

	SAFE_FREE(pszBuffer);

	return TRUE;
Exit0:
	SAFE_FREE(pszBuffer);

	return FALSE;
}

BOOL CPakFile::ExtractFile(int nFileIndex)
{
	BOOL bResult = FALSE;
	int nRetCode = 0;
	char szDirName[MAX_FILE_NAME_LEN] = {0};
	FILE* pFile = NULL;
	char* pszBuffer = NULL;

	LOG_PROCESS_ERROR(m_szFileName[0] != 0);

	LOG_PROCESS_ERROR(m_pHeader);
	LOG_PROCESS_ERROR(m_pFileInfoList);
	LOG_PROCESS_ERROR(m_pszNameBuffer);

	LOG_PROCESS_ERROR(nFileIndex >= 0 && nFileIndex < m_pHeader->nFileCount);

	PAK_FILE_INFO* pFileInfo = m_pFileInfoList + nFileIndex;
	const char* pcszFileName = m_pszNameBuffer + nFileIndex * MAX_FILE_NAME_LEN;

	memset(szDirName, 0, sizeof(szDirName));
	for (int nIndex = 0; nIndex < strlen(pcszFileName); nIndex++)
	{
		if (pcszFileName[nIndex] == L'/' || pcszFileName[nIndex] == L'\\')
		{
			mkdir(szDirName);
		}
		szDirName[nIndex] = pcszFileName[nIndex];
	}

	if (pcszFileName[0] == 0)
	{
		snprintf(szDirName, MAX_FILE_NAME_LEN, "%08X_%08X.dat", pFileInfo->dwNameHashA, pFileInfo->dwNameHashB);
		pcszFileName = szDirName;
	}

	pFile = fopen(pcszFileName, "wb");
	LOG_PROCESS_ERROR(pFile);

	pszBuffer = (char*)malloc(pFileInfo->dwOriginalSize);
	LOG_PROCESS_ERROR(pszBuffer);

	nRetCode = ReadFileData(nFileIndex, pszBuffer, pFileInfo->dwOriginalSize);
	LOG_PROCESS_ERROR(nRetCode);

	size_t uSize = fwrite(pszBuffer, 1, pFileInfo->dwOriginalSize, pFile);
	LOG_PROCESS_ERROR(uSize == pFileInfo->dwOriginalSize);

	bResult = TRUE;
Exit0:
	SAFE_FREE(pszBuffer);

	if (pFile)
		fclose(pFile);

	return bResult;
}
