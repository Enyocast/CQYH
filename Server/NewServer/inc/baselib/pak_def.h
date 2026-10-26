#ifndef _PAK_DEF_H_
#define _PAK_DEF_H_

#define PAK_FILE_TAG			'ZJQP'
#define PAK_FILE_VERSION		(1)
#define DEFAULT_CHUNK_SIZE		65536
#define ONE_CHUNK_SIZE			102400
#define INVALID_PAK_FILE_INDEX	(-1)

#define INVALID_FILEID			0xFFFFFFFF
#define CHUNK_INDEX_EOF			0xFFFFFFFF

#define INVALID_FILE_POS		0xFFFFFFFF

enum PAK_FILE_FLAG
{
	PackageFlag_NoHashTable				=	0x00000001,
	PackageFlag_NoNameBuffer			=	0x00000010,
	PackageFlag_NameBufferCompressed	=	0x00000100,
	PackageFlag_FileInfoCompressed		=	0x00001000,

	FileFlag_NoCompressed				=	0x00000001,
	FileFlag_Deleted					=	0x00000002,
};

struct	PAK_FILE_HEADER
{
	UINT32				dwTag;
	UINT32				dwVersion;

	UINT32				dwPackageFlag;
	INT32				nFileCount;
	UINT32				dwFileNameSize;

	UINT32				dwHashTableOffset;
	UINT32				dwHashTableSize;

	UINT32				dwNameBufferOffset;
	UINT32				dwNameBufferSize;

	UINT32				dwFileInfoOffset;
	UINT32				dwFileInfoSize;

	UINT32				dwDataOffset;
	UINT32				dwDataSize;

};

struct	PAK_FILE_INFO
{
	UINT32				dwFileNameOffset;
	UINT32				dwNameHashA;
	UINT32				dwNameHashB;
	UINT32				dwHashTableIndex;

	UINT32				dwFileFlag;

	UINT32				dwCreateTime;			
	UINT32				dwModifyTime;		

	UINT32				dwOriginalSize;
	UINT32				dwCompressedSize;

	UINT32				dwChunkStartOffset;
	UINT32				dwChunkSize;
	INT32				nDataChunkCount;

	UINT8				md5OriginDataHash[16];		
	UINT8				md5CompressedDataHash[16];		
};

struct	PAK_CHUNK_INFO
{
	UINT32				dwChunkOffset;
	UINT32				dwChunkSize;
};


#endif	// _PAK_DEF_H_