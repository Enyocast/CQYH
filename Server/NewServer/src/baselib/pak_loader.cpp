#include "stdafx.h"
#include "pak_loader.h"

#include "zlib.h"
#include "hash.h"
#include "linux_compatible.h"

CPakLoader::CPakLoader()
{
	m_pPackageList = NULL;
	m_nPackageCount = 0;
	m_nPackageIndex = 0;

	m_pPakFileList = NULL;
	m_nPakFileCount = 0;
	m_nPakFileIndex = 0;
}

CPakLoader::~CPakLoader()
{
	UnInit();
}

int _FileNameCmp( const void* a, const void* b)
{
	return strcmp((const char*)a,(const char*)b);
}
BOOL CPakLoader::Init(const char* pcszPakFolder)
{
#ifdef WIN32
	INT32 nRetCode = 0;
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	char szPattern[MAX_PATH];

	const INT32 MAX_FILE_COUNT = 64;
	char* SortedFileList[MAX_FILE_COUNT] = { NULL };
	char szFileList[MAX_FILE_COUNT][MAX_PATH];
	INT32 nFileListCount = 0;

	char szCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szCurrentDir);

	LOG_PROCESS_ERROR(pcszPakFolder);
	LOG_PROCESS_ERROR(m_pPakFileList == NULL);
	LOG_PROCESS_ERROR(m_pPakFileList == NULL);
	m_nPackageCount = 0;
	m_nPackageIndex = 0;

	m_nPakFileCount = 0;
	m_nPakFileIndex = 0;

	// 1 get all *.pak files
	snprintf(szPattern, MAX_PATH, "%s\\*.pak", pcszPakFolder);
	hFind = FindFirstFile(szPattern, &FindFileData);
	PROCESS_ERROR(hFind != INVALID_HANDLE_VALUE);
	do
	{
		if (FindFileData.cFileName[0] == L'.')
			continue;

		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
			continue;

		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;

		strxcpy(szFileList[nFileListCount], FindFileData.cFileName, sizeof(szFileList[0]));
		LOG_PROCESS_ERROR(nFileListCount<MAX_FILE_COUNT);
		++nFileListCount;
	} while (FindNextFile(hFind, &FindFileData));
	FindClose(hFind);
	hFind = INVALID_HANDLE_VALUE;

	// 2 sort
	for (INT32 i = 0; i < nFileListCount; ++i)
	{
		SortedFileList[i] = szFileList[i];
	}
	// patch file name eg.
	// commonconfig.pak
	// commonconfig_patch#123-124.pak
	// commonconfig_patch#123-125.pak
	// commonconfig_patch#124-125.pak
	// so just sort them in alphabetical order one by one
	qsort(SortedFileList, nFileListCount, sizeof(SortedFileList[0]), _FileNameCmp);

	// 3 preload
	for (INT32 i = 0; i < nFileListCount; ++i)
	{
		char szFilePath[MAX_PATH];
		snprintf(szFilePath, MAX_PATH, "%s\\%s\\%s", szCurrentDir, pcszPakFolder, SortedFileList[i]);

		nRetCode = _PreloadPakFile(szFilePath);
		if (!nRetCode)
			WRN("failed to pre load package file %s", szFilePath);

	}

	// 4 load
	m_pPackageList = new PACKAGE_DATA[m_nPackageCount];
	LOG_PROCESS_ERROR(m_pPackageList);

	m_pPakFileList = new PAK_FILE_DATA[m_nPakFileCount];
	LOG_PROCESS_ERROR(m_pPakFileList);

	for (INT32 i = 0; i < nFileListCount; ++i)
	{
		char szFilePath[MAX_PATH];
		snprintf(szFilePath, MAX_PATH, "%s\\%s\\%s", szCurrentDir, pcszPakFolder, szFileList[i]);

		nRetCode = _LoadPakFile(szFilePath);
		if (!nRetCode)
			WRN("failed to load package file %s", szFilePath);
	}
#endif	// WIN32

	nRetCode = _UpdateHashTable();
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (hFind != INVALID_HANDLE_VALUE)
		FindClose(hFind);

	SAFE_DELETE_ARRAY(m_pPackageList);
	SAFE_DELETE_ARRAY(m_pPakFileList);

	return FALSE;
}

BOOL CPakLoader::Reload(const char* pcszPakFolder)
{
	BOOL nRetCode = FALSE;

	nRetCode = UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = Init(pcszPakFolder);
	LOG_CHECK_ERROR(nRetCode);

Exit0:
	return TRUE;
}

BOOL CPakLoader::UnInit(void)
{
	for (INT32 nPackageIndex = 0; nPackageIndex < m_nPackageCount; nPackageIndex++)
	{
		if (m_pPackageList[nPackageIndex].pFile)
		{
			fclose(m_pPackageList[nPackageIndex].pFile);
			m_pPackageList[nPackageIndex].pFile = NULL;
		}
	}

	SAFE_DELETE_ARRAY(m_pPackageList);
	m_nPackageCount = 0;
	m_nPackageIndex = 0;
	SAFE_DELETE_ARRAY(m_pPakFileList);
	m_nPakFileCount = 0;
	m_nPakFileIndex = 0;
	return TRUE;
}

INT32 CPakLoader::GetFileCount(void)
{
	return m_nPakFileCount;
}

INT32 CPakLoader::FindFile(const char* pcszPakFileName)
{
	INT32 nResult = INVALID_PAK_FILE_INDEX;
	INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(pcszPakFileName);
    LOG_PROCESS_ERROR(m_pPakFileList);
	if (m_nPakFileCount > 0)
	{
		UINT32 dwHashA, dwHashB;
		hash_file_name(pcszPakFileName, &dwHashA, &dwHashB);

		INT32 nFileIndex = dwHashA % m_nPakFileCount;
		INT32 nTryIndex = 0;
		for (; nTryIndex < m_nPakFileCount; nTryIndex++)
		{
			if (m_pPakFileList[nFileIndex].dwNameHashB == dwHashB)
				break;
			nFileIndex++;
			if (nFileIndex >= m_nPakFileCount)
				nFileIndex = 0;
		}
		PROCESS_ERROR(nTryIndex < m_nPakFileCount);

		nResult = nFileIndex;
	}

Exit0:

	return nResult;
}

UINT32 CPakLoader::GetFileSize(INT32 nFileIndex)
{
	LOG_PROCESS_ERROR(m_pPakFileList);
	LOG_PROCESS_ERROR(nFileIndex >= 0 && nFileIndex < m_nPakFileCount);

	return m_pPakFileList[nFileIndex].dwOriginalSize;
Exit0:

	return 0;
}

BOOL CPakLoader::ReadFileData(INT32 nFileIndex, char* pszFileData, size_t uDataSize)
{
	INT32 nRetCode = 0;
	size_t uSize = 0;
	PAK_FILE_DATA* pPakFileData = NULL;
	PACKAGE_DATA* pPackageData = NULL;
	FILE* pFile = NULL;
	static char s_szBuffer[ONE_CHUNK_SIZE];

	LOG_PROCESS_ERROR(pszFileData);
	LOG_PROCESS_ERROR(nFileIndex >= 0 && nFileIndex < m_nPakFileCount);

	pPakFileData = m_pPakFileList + nFileIndex;
	LOG_PROCESS_ERROR(uDataSize <= pPakFileData->dwOriginalSize);

	LOG_PROCESS_ERROR(pPakFileData->nPackageIndex >= 0 && pPakFileData->nPackageIndex < m_nPackageCount);
	pPackageData = m_pPackageList + pPakFileData->nPackageIndex;

	pFile = pPackageData->pFile;
	LOG_PROCESS_ERROR(pFile);

	nRetCode = fseek(pFile, pPackageData->dwDataOffset + pPakFileData->dwChunkStartOffset, SEEK_SET);
	LOG_PROCESS_ERROR(nRetCode == 0);

	if (pPakFileData->dwFileFlag & FileFlag_NoCompressed)
	{
		uSize = fread(pszFileData, 1, uDataSize, pFile);
		LOG_PROCESS_ERROR(uSize == uDataSize);
	}
	else
	{
		size_t uTotalDecompressedSize = 0;

		for (std::list<PAK_CHUNK_INFO>::iterator it = pPakFileData->ChunkList.begin();
				it != pPakFileData->ChunkList.end(); ++it)
		{
			LOG_PROCESS_ERROR(ftell(pFile) == (it->dwChunkOffset + pPackageData->dwDataOffset));
			LOG_PROCESS_ERROR(it->dwChunkSize < ONE_CHUNK_SIZE);

			uSize = fread(s_szBuffer, 1, it->dwChunkSize, pFile);
			LOG_PROCESS_ERROR(uSize == it->dwChunkSize);

			size_t uDecompressedSize = uDataSize - uTotalDecompressedSize;
			nRetCode = uncompress((UINT8*)pszFileData + uTotalDecompressedSize, (ULONG*)&uDecompressedSize, 
				(UINT8*)s_szBuffer, it->dwChunkSize);
			LOG_PROCESS_ERROR(nRetCode == Z_OK);

			uTotalDecompressedSize += uDecompressedSize;
		}
		LOG_PROCESS_ERROR(uTotalDecompressedSize == uDataSize);
	}

	return TRUE;
Exit0:

	return FALSE;
}

BOOL CPakLoader::_PreloadPakFile(const char* pcszFileName)
{
	INT32 nRetCode = 0;
	FILE* pFile = NULL;
	PAK_FILE_HEADER Header;
	size_t sizeRead;

	LOG_PROCESS_ERROR(pcszFileName);

	pFile = fopen(pcszFileName, "rb");
	LOG_PROCESS_ERROR(pFile);

	sizeRead = fread(&Header, 1, sizeof(Header), pFile);
	LOG_PROCESS_ERROR(sizeRead == sizeof(Header));
	LOG_PROCESS_ERROR(Header.dwTag == PAK_FILE_TAG);
	LOG_PROCESS_ERROR(Header.dwVersion == PAK_FILE_VERSION);

	m_nPakFileCount += Header.nFileCount;
	m_nPackageCount++;

	fclose(pFile);
	pFile = NULL;

	return TRUE;
Exit0:
	if (pFile)
		fclose(pFile);

	return FALSE;
}

BOOL CPakLoader::_LoadPakFile(const char* pcszFileName)
{
	INT32 nRetCode = 0;
	PACKAGE_DATA* pPakFileData = NULL;
	char* pszBuffer = NULL;
	char* pszTempBuffer = NULL;
	char* pszPointer = NULL;
	INT32 nChunkCount = 0;
	UINT32 uSize = 0;
	PAK_FILE_HEADER Header;
	size_t sizeRead = 0;

	LOG_PROCESS_ERROR(pcszFileName);
	LOG_PROCESS_ERROR(m_nPackageIndex < m_nPackageCount);

	pPakFileData = m_pPackageList + m_nPackageIndex;

	pPakFileData->pFile = fopen(pcszFileName, "rb");
	LOG_PROCESS_ERROR(pPakFileData->pFile);

	sizeRead = fread(&Header, 1, sizeof(Header), pPakFileData->pFile);
	LOG_PROCESS_ERROR(sizeRead == sizeof(Header));
	LOG_PROCESS_ERROR(Header.dwTag == PAK_FILE_TAG);
	LOG_PROCESS_ERROR(Header.dwVersion == PAK_FILE_VERSION);

	pPakFileData->dwDataOffset = Header.dwDataOffset;
	pPakFileData->dwDataSize = Header.dwDataSize;

	// load file info
	pszBuffer = new char[Header.dwFileInfoSize];
	LOG_PROCESS_ERROR(pszBuffer);

	nRetCode = fseek(pPakFileData->pFile, Header.dwFileInfoOffset, SEEK_SET);
	LOG_PROCESS_ERROR(nRetCode == 0);

	sizeRead = fread(pszBuffer, 1, (size_t)Header.dwFileInfoSize, pPakFileData->pFile);
	LOG_PROCESS_ERROR(sizeRead == Header.dwFileInfoSize);

	// process file info list
	if (Header.dwPackageFlag & PackageFlag_FileInfoCompressed)
	{
		uSize = Header.dwFileInfoSize * 8;
		pszTempBuffer = new char[uSize];
		LOG_PROCESS_ERROR(pszTempBuffer);

		nRetCode = uncompress((UINT8*)pszTempBuffer, (ULONG*)(&uSize), (UINT8*)pszBuffer, Header.dwFileInfoSize);
		LOG_PROCESS_ERROR(nRetCode == Z_OK);

		SAFE_DELETE_ARRAY(pszBuffer);
		pszBuffer = pszTempBuffer;
		pszTempBuffer = NULL;
		Header.dwFileInfoSize = uSize;
	}

	pszPointer = pszBuffer;
	for (int nFileIndex = 0; nFileIndex < Header.nFileCount; nFileIndex++)
	{
		PAK_FILE_INFO* pPakFileInfo = (PAK_FILE_INFO*)pszPointer;
		PAK_FILE_DATA* pPakFileData = m_pPakFileList + m_nPakFileIndex;

		pPakFileData->nPackageIndex = m_nPackageIndex;
		pPakFileData->dwNameHashA = pPakFileInfo->dwNameHashA;
		pPakFileData->dwNameHashB = pPakFileInfo->dwNameHashB;
		pPakFileData->dwFileFlag = pPakFileInfo->dwFileFlag;

		pPakFileData->dwOriginalSize = pPakFileInfo->dwOriginalSize;
		pPakFileData->dwCompressedSize = pPakFileInfo->dwCompressedSize;

        pPakFileData->dwCreateTime = pPakFileInfo->dwCreateTime;
        pPakFileData->dwModifyTime = pPakFileInfo->dwModifyTime;

		pPakFileData->dwChunkStartOffset = pPakFileInfo->dwChunkStartOffset;
		pPakFileData->dwChunkSize = pPakFileInfo->dwChunkSize;

		pszPointer += sizeof(PAK_FILE_INFO);
		LOG_PROCESS_ERROR(pszPointer - pszBuffer <= Header.dwFileInfoSize);

		for (int nChunkIndex = 0; nChunkIndex < pPakFileInfo->nDataChunkCount; nChunkIndex++)
		{
			PAK_CHUNK_INFO* pChunkInfo = (PAK_CHUNK_INFO*)pszPointer;
			pszPointer += sizeof(PAK_CHUNK_INFO);
			LOG_PROCESS_ERROR(pszPointer - pszBuffer <= Header.dwFileInfoSize);

			pPakFileData->ChunkList.push_back(*pChunkInfo);

			nChunkCount++;
		}

		m_nPakFileIndex++;
	}

	m_nPackageIndex++;

    SAFE_DELETE_ARRAY(pszBuffer);
    SAFE_DELETE_ARRAY(pszTempBuffer);

	return TRUE;
Exit0:
	SAFE_DELETE_ARRAY(pszBuffer);
	SAFE_DELETE_ARRAY(pszTempBuffer);

	return FALSE;
}

BOOL CPakLoader::_UpdateHashTable(void)
{
	PAK_FILE_DATA* pNewPakFileList = NULL;
	
	pNewPakFileList = new PAK_FILE_DATA[m_nPakFileCount];
	LOG_PROCESS_ERROR(pNewPakFileList);

	for (INT32 nFileIndex = 0; nFileIndex < m_nPakFileCount; nFileIndex++)
	{
		INT32 nCorrectFileIndex = m_pPakFileList[nFileIndex].dwNameHashA % m_nPakFileCount;
		while ( (pNewPakFileList[nCorrectFileIndex].dwNameHashA != 0 || pNewPakFileList[nCorrectFileIndex].dwNameHashB != 0) && 
			(pNewPakFileList[nCorrectFileIndex].dwNameHashA != m_pPakFileList[nFileIndex].dwNameHashA ||
			pNewPakFileList[nCorrectFileIndex].dwNameHashB != m_pPakFileList[nFileIndex].dwNameHashB) )
		{
			nCorrectFileIndex++;
			if (nCorrectFileIndex >= m_nPakFileCount)
				nCorrectFileIndex = 0;
		}

		pNewPakFileList[nCorrectFileIndex].nPackageIndex = m_pPakFileList[nFileIndex].nPackageIndex;
		pNewPakFileList[nCorrectFileIndex].dwNameHashA = m_pPakFileList[nFileIndex].dwNameHashA;
		pNewPakFileList[nCorrectFileIndex].dwNameHashB = m_pPakFileList[nFileIndex].dwNameHashB;
		pNewPakFileList[nCorrectFileIndex].dwFileFlag = m_pPakFileList[nFileIndex].dwFileFlag;
		pNewPakFileList[nCorrectFileIndex].dwOriginalSize = m_pPakFileList[nFileIndex].dwOriginalSize;
		pNewPakFileList[nCorrectFileIndex].dwCompressedSize = m_pPakFileList[nFileIndex].dwCompressedSize;
		pNewPakFileList[nCorrectFileIndex].dwChunkStartOffset = m_pPakFileList[nFileIndex].dwChunkStartOffset;
		pNewPakFileList[nCorrectFileIndex].dwChunkSize = m_pPakFileList[nFileIndex].dwChunkSize;
		pNewPakFileList[nCorrectFileIndex].dwCreateTime = m_pPakFileList[nFileIndex].dwCreateTime;
		pNewPakFileList[nCorrectFileIndex].dwModifyTime = m_pPakFileList[nFileIndex].dwModifyTime;

		pNewPakFileList[nCorrectFileIndex].ChunkList.clear();
		for (std::list<PAK_CHUNK_INFO>::iterator it = m_pPakFileList[nFileIndex].ChunkList.begin();
			it != m_pPakFileList[nFileIndex].ChunkList.end(); ++it)
		{
			pNewPakFileList[nCorrectFileIndex].ChunkList.push_back(*it);
		}
	}

	SAFE_DELETE_ARRAY(m_pPakFileList);
	m_pPakFileList = pNewPakFileList;

	return TRUE;
Exit0:
	SAFE_DELETE_ARRAY(pNewPakFileList);

	return FALSE;
}

UINT32 CPakLoader::GetFileCreateTime(INT32 nFileIndex)
{
    LOG_PROCESS_ERROR(m_pPakFileList);
    LOG_PROCESS_ERROR(nFileIndex >= 0 && nFileIndex < m_nPakFileCount);

    return m_pPakFileList[nFileIndex].dwCreateTime;
Exit0:

    return 0;
}

UINT32 CPakLoader::GetFileModifyTime(INT32 nFileIndex)
{
    LOG_PROCESS_ERROR(m_pPakFileList);
    LOG_PROCESS_ERROR(nFileIndex >= 0 && nFileIndex < m_nPakFileCount);

    return m_pPakFileList[nFileIndex].dwModifyTime;
Exit0:

    return 0;
}
