#ifndef _PAK_LOADER_H_
#define _PAK_LOADER_H_

#include "pak_def.h"

class CPakLoader
{
public:
	CPakLoader();
	~CPakLoader();

	BOOL Init(const char* pcszPakFolder);
	BOOL UnInit(void);
	BOOL Reload(const char* pcszPakFolder);

	INT32 GetFileCount(void);
	INT32 FindFile(const char* pcszPakFileName);
	UINT32 GetFileSize(INT32 nFileIndex);
	BOOL ReadFileData(INT32 nFileIndex, char* pszFileData, size_t uDataSize);
    UINT32 GetFileCreateTime(INT32 nFileIndex);
    UINT32 GetFileModifyTime(INT32 nFileIndex);

private:
	BOOL _PreloadPakFile(const char* pcszFileName);
	BOOL _LoadPakFile(const char* pcszFileName);
	BOOL _UpdateHashTable(void);

	struct PACKAGE_DATA
	{
		FILE*				pFile;
		UINT32				dwDataOffset;
		UINT32				dwDataSize;
	};

	PACKAGE_DATA*			m_pPackageList;
	INT32					m_nPackageIndex;
	INT32					m_nPackageCount;

	struct PAK_FILE_DATA
	{
		PAK_FILE_DATA() {dwNameHashA = dwNameHashB = 0;}
		INT32				nPackageIndex;
		UINT32				dwNameHashA;
		UINT32				dwNameHashB;
		UINT32				dwFileFlag;

		UINT32				dwOriginalSize;
		UINT32				dwCompressedSize;

        UINT32				dwCreateTime;			
        UINT32				dwModifyTime;		

		UINT32				dwChunkStartOffset;
		UINT32				dwChunkSize;

		std::list<PAK_CHUNK_INFO>	ChunkList;
	};

	PAK_FILE_DATA*			m_pPakFileList;
	INT32					m_nPakFileIndex;
	INT32					m_nPakFileCount;
};

#endif	// _PAK_LOADER_H_