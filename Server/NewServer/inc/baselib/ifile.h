#ifndef _IFILE_H_
#define _IFILE_H_

class IFile
{
public:
	virtual BOOL Close(void) = 0;

	virtual UINT32 Read(void* pData, UINT32 dwLen) = 0;
	virtual BOOL  Seek(INT32 nOffset, INT32 nOrigin) = 0;
	virtual BOOL Eof(void) = 0;
	virtual UINT32 Size(void) = 0;
};

BOOL g_OpenPakFolder(const char* pcszFolderName);
BOOL g_ClosePakFolder(void);
BOOL g_ReloadPakFolder(const char* pcszFolderName);

IFile* g_OpenFile(const char* pcszFileName, const char* pcszMode);
BOOL g_IsFileExist(const char* pcszFileName);
UINT32 g_GetFileCreateTime(const char* pcszFileName);
UINT32 g_GetFileModifyTime(const char* pcszFileName);

#endif	// _IFILE_H_