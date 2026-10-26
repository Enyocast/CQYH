#include "stdafx.h"
#include "ifile.h"

#include <sys/stat.h>
#include "pak_loader.h"

CPakLoader	g_PakLoader;

class CNormalFile : public IFile
{
public:
	CNormalFile();
	virtual ~CNormalFile();

	BOOL Init(const char* pcszFileName, const char* pcszMode);
	BOOL UnInit(void);

	virtual BOOL Close(void);

	virtual UINT32 Read(void* pData, UINT32 dwLen);
	virtual UINT32 Write(const void* pData, UINT32 dwLen);
	virtual BOOL  Seek(INT32 nOffset, INT32 nOrigin);
	virtual BOOL Eof(void);
	virtual UINT32 Size(void);

private:
	FILE*   m_pFile;
};

CNormalFile::CNormalFile()
{
	m_pFile = NULL;
}

CNormalFile::~CNormalFile()
{
	UnInit();
}

BOOL CNormalFile::Init(const char* pcszFileName, const char* pcszMode)
{
	LOG_PROCESS_ERROR(m_pFile == NULL);

	m_pFile = fopen(pcszFileName, pcszMode);
	PROCESS_ERROR(m_pFile);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CNormalFile::UnInit(void)
{
	if (m_pFile)
    {
		fclose(m_pFile);
    }
	m_pFile = NULL;

	return TRUE;
}

BOOL CNormalFile::Close(void)
{
	UnInit();
	delete this;

	return TRUE;
}

UINT32 CNormalFile::Read(void* pData, UINT32 dwLen)
{
	return (UINT32)fread(pData, 1, dwLen, m_pFile);
}

UINT32 CNormalFile::Write(const void* pData, UINT32 dwLen)
{
	return (UINT32)fwrite(pData, 1, dwLen, m_pFile);
}

BOOL CNormalFile::Seek(INT32 nOffset, INT32 nOrigin)
{
	return fseek(m_pFile, nOffset, nOrigin) == 0;
}

BOOL CNormalFile::Eof(void)
{
	if (m_pFile)
		return feof(m_pFile);
	return TRUE;
}

UINT32 CNormalFile::Size(void)
{
	UINT32 dwResult = 0;
	INT32 nRetCode = 0;
	UINT32 dwCurrent = 0;

	LOG_PROCESS_ERROR(m_pFile);

	dwCurrent = ftell(m_pFile);

	nRetCode = fseek(m_pFile, 0, SEEK_END);
	LOG_PROCESS_ERROR(nRetCode == 0);

	dwResult = ftell(m_pFile);

	nRetCode = fseek(m_pFile, dwCurrent, SEEK_SET);
	LOG_PROCESS_ERROR(nRetCode == 0);

Exit0:
	return dwResult;
}

/************************************************************************/

class CPakFileDummy : public IFile
{
public:
	CPakFileDummy();
	~CPakFileDummy();

	BOOL Init(INT32 nFileIndex);
	BOOL UnInit(void);

	virtual BOOL Close(void);

	virtual UINT32 Read(void* pData, UINT32 dwLen);
	virtual BOOL  Seek(INT32 nOffset, INT32 nOrigin);
	virtual BOOL Eof(void);
	virtual UINT32 Size(void);

private:
	INT32	m_nFileIndex;
	char*	m_pData;
	UINT32	m_dwSize;
	UINT32	m_dwOffset;
};


CPakFileDummy::CPakFileDummy()
{
	m_nFileIndex = INVALID_PAK_FILE_INDEX;
	m_pData = NULL;
	m_dwSize = 0;
	m_dwOffset = 0;
}

CPakFileDummy::~CPakFileDummy()
{
	UnInit();
}

BOOL CPakFileDummy::Init(INT32 nFileIndex)
{
	INT32 nRetCode = 0;

	m_dwSize = g_PakLoader.GetFileSize(nFileIndex);
	LOG_PROCESS_ERROR(m_dwSize >= 0);

	m_pData = new char[m_dwSize];
	LOG_PROCESS_ERROR(m_pData);

	nRetCode = g_PakLoader.ReadFileData(nFileIndex, m_pData, m_dwSize);
	LOG_PROCESS_ERROR(nRetCode);

	m_nFileIndex = nFileIndex;
	m_dwOffset = 0;

	return TRUE;
Exit0:
	UnInit();

	return FALSE;
}

BOOL CPakFileDummy::UnInit(void)
{
	m_nFileIndex = INVALID_PAK_FILE_INDEX;
	SAFE_DELETE_ARRAY(m_pData);
	m_dwSize = 0;

	return TRUE;
}

BOOL CPakFileDummy::Close(void)
{
	UnInit();
	delete this;

	return TRUE;
}

UINT32 CPakFileDummy::Read(void* pData, UINT32 dwLen)
{
	if (pData == NULL)
		return 0;

	UINT32 dwRealSize = dwLen;
	if (m_dwOffset + dwLen > m_dwSize)
		dwRealSize = m_dwSize - m_dwOffset;

	memcpy(pData, m_pData + m_dwOffset, dwRealSize);
	m_dwOffset += dwRealSize;

	return dwRealSize;
}

BOOL  CPakFileDummy::Seek(INT32 nOffset, INT32 nOrigin)
{
	UINT32 dwNewOffset = -1;

	if (nOrigin == SEEK_SET)
		dwNewOffset = nOffset;
	else if (nOrigin ==  SEEK_CUR)
		dwNewOffset = m_dwOffset + nOffset;
	else if (nOrigin == SEEK_END)
		dwNewOffset = m_dwSize - nOffset - 1;
	else
		return FALSE;

	if (dwNewOffset > m_dwSize)
		return FALSE;

	m_dwOffset = dwNewOffset;

	return TRUE;
}

BOOL CPakFileDummy::Eof(void)
{
	return (m_dwOffset == m_dwSize) && (m_nFileIndex != INVALID_PAK_FILE_INDEX);
}

UINT32 CPakFileDummy::Size(void)
{
	return m_dwSize;
}

/************************************************************************/

BOOL g_OpenPakFolder(const char* pcszFolderName)
{
	return g_PakLoader.Init(pcszFolderName);
}

BOOL g_ClosePakFolder(void)
{
	return g_PakLoader.UnInit();
}

BOOL g_ReloadPakFolder(const char* pcszFolderName)
{
	return g_PakLoader.Reload(pcszFolderName);
}

IFile* g_OpenFile(const char* pcszFileName, const char* pcszMode)
{
	INT32 nRetCode = 0;
	IFile* pResult = NULL;
	INT32 nFileIndex = INVALID_PAK_FILE_INDEX;
	
	pResult = new CNormalFile;
	LOG_PROCESS_ERROR(pResult);

	nRetCode = ((CNormalFile*)pResult)->Init(pcszFileName, pcszMode);
	PROCESS_SUCCESS(nRetCode);

	SAFE_DELETE(pResult);

	if (g_PakLoader.GetFileCount() > 0)
	{
		nFileIndex = g_PakLoader.FindFile(pcszFileName);
		PROCESS_ERROR(nFileIndex != INVALID_PAK_FILE_INDEX);

		pResult = new CPakFileDummy;
		LOG_PROCESS_ERROR(pResult);

		nRetCode = ((CPakFileDummy*)pResult)->Init(nFileIndex);
		LOG_PROCESS_ERROR(nRetCode);
	}

Exit1:
	return pResult;
Exit0:
	SAFE_DELETE(pResult);

	return NULL;
}

BOOL _FileExists(const char* strFileName)
{
    FILE* fp = fopen(strFileName, "r");
    if (fp == NULL)
    {
        return FALSE;
    }

    fclose(fp);

    return TRUE;
}

BOOL g_IsFileExist(const char* pcszFileName)
{
    INT32 nRetCode = 0;
    INT32 nFileIndex = INVALID_PAK_FILE_INDEX;

    nRetCode = _FileExists(pcszFileName);
    if (nRetCode)
        return TRUE;

    if (g_PakLoader.GetFileCount() > 0)
    {
        nFileIndex = g_PakLoader.FindFile(pcszFileName);
        if (nFileIndex != INVALID_PAK_FILE_INDEX)
            return TRUE;
    }

    return FALSE;
}

UINT32 g_GetFileCreateTime(const char* pcszFileName)
{
    UINT32 dwResult = 0;
    INT32 nRetCode = 0;
    FILE* pFile = NULL;
    INT32 nFileIndex = INVALID_PAK_FILE_INDEX;

    LOG_PROCESS_ERROR(pcszFileName);

    pFile = fopen(pcszFileName, "rb");
    if (pFile)
    {
        int fd;
        struct stat FileStat;

        fd = fileno(pFile);
        LOG_PROCESS_ERROR(fd != -1);

        nRetCode = fstat(fd, &FileStat);
        LOG_PROCESS_ERROR(nRetCode == 0);

        dwResult = (UINT32)FileStat.st_ctime;
    }
    else if (g_PakLoader.GetFileCount() > 0)
    {
        nFileIndex = g_PakLoader.FindFile(pcszFileName);
        PROCESS_ERROR(nFileIndex != INVALID_PAK_FILE_INDEX);

        dwResult = g_PakLoader.GetFileCreateTime(nFileIndex);
    }

Exit0:
    if (pFile)
        fclose(pFile);

    return dwResult;
}

UINT32 g_GetFileModifyTime(const char* pcszFileName)
{
    UINT32 dwResult = 0;
    INT32 nRetCode = 0;
    FILE* pFile = NULL;
    INT32 nFileIndex = INVALID_PAK_FILE_INDEX;

    LOG_PROCESS_ERROR(pcszFileName);

    pFile = fopen(pcszFileName, "rb");
    if (pFile)
    {
        int fd;
        struct stat FileStat;

        fd = fileno(pFile);
        LOG_PROCESS_ERROR(fd != -1);

        nRetCode = fstat(fd, &FileStat);
        LOG_PROCESS_ERROR(nRetCode == 0);

        dwResult = (UINT32)FileStat.st_mtime;
    }
    else if (g_PakLoader.GetFileCount() > 0)
    {
        nFileIndex = g_PakLoader.FindFile(pcszFileName);
        PROCESS_ERROR(nFileIndex != INVALID_PAK_FILE_INDEX);

        dwResult = g_PakLoader.GetFileModifyTime(nFileIndex);
    }

Exit0:
    if (pFile)
        fclose(pFile);

    return dwResult;
}
