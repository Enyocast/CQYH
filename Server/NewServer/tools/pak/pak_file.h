#ifndef _PAK_FILE_H_
#define _PAK_FILE_H_

#include "pak_def.h"

/************************************************************************/
/* Note: This PAK file class does NOT support larger than 4GB file.     */
/************************************************************************/

struct PAK_FILE_HEADER;
struct PAK_FILE_INFO;
struct PAK_CHUNK_INFO;

class CPakFile
{
public:
	CPakFile();
	virtual ~CPakFile();

	BOOL Create(const char* pcszFileName);
	BOOL Open(const char* pcszFileName);
	BOOL Close(void);

	BOOL IsOpened(void);
	BOOL SetPackageFlag(BOOL bHasHashTable, BOOL bHasNameBuffer, BOOL bCompressNameBuffer, BOOL bCompressFileInfo);

	BOOL AddFile(const char* pcszPakFileName, const char* pcszFileName);
	BOOL DelFile(const char* pcszPakFileName);
	int FindFile(const char* pcszPakFileName);

	BOOL AddFileFromPak(const char* pcszPakFileName, CPakFile* pTGPFile, int nFileIndex);
	BOOL AddFileFromData(const char* pcszPakFileName, time_t CreateTime, 
		time_t ModifyTime, const char* pszFileData, size_t uDataSize);

	int GetFileCount(void);
	size_t GetFileSize(int nFileIndex);
	const char* GetFileName(int nFileIndex);
	BOOL GetFileHashValue(int nFileIndex, unsigned long& rulHashValueA, unsigned long& rulHashValueB);
	BOOL IsDeletedFile(int nFileIndex);
	BOOL GetFileMD5Value(int nFileIndex, unsigned char ucMD5Value[16]);
	BOOL ReadFileData(int nFileIndex, char* pszFileData, size_t uDataSize);
	BOOL VerifyFile(int nFileIndex);
	BOOL ExtractFile(int nFileIndex);

private:
	FILE*				m_pFile;
	char				m_szFileName[MAX_PATH];
	BOOL				m_bUpdateHashTable;

	PAK_FILE_HEADER*	m_pHeader;	
	unsigned int*		m_puHashTable;
	char*				m_pszNameBuffer;
	PAK_FILE_INFO*		m_pFileInfoList;
	PAK_CHUNK_INFO* 	m_pChunkInfoList;
	int					m_nChunkCount;
	int*				m_pnChunkOffsetList;

	BOOL _Alloc(void);
	BOOL _Free(void);
	BOOL _AddFileFromRawData(const char* pcszPakFileName, 
		const PAK_FILE_INFO* pFileInfo, 
		const PAK_CHUNK_INFO* pChunkInfo,
		const char* pszFileData, size_t uDataSize);
	BOOL _UpdateHashTable(void);
};

#endif	// _PAK_FILE_H_