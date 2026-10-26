/*=============================================================================
	FFileManagerMPQ.h: Unreal Windows OS based file manager.
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __FILEMANAGERMPQ_H__
#define __FILEMANAGERMPQ_H__

#if WITH_STORMLIB

#include "FTableOfContents.h"
#include "FFileManagerGeneric.h"

// oscar@snda
#define M_DEBUG_FILE_HANDLE 0
#define M_TRACE_FILE_HANDLE 0

#if M_DEBUG_FILE_HANDLE
#	define dbgF debugf
#	define dbgCreateFile(fhdl) appOutputDebugStringf(TEXT("#########[%s] Handle:%x\n"), *FString( __FUNCTION__ ), fhdl);
#	define dbgCloseFile(fnm, fhdl, hr) appOutputDebugStringf(TEXT("#########[%s] File:%s Handle:%x %d\n"), *FString( __FUNCTION__ ), fnm, fhdl, hr);
#else
#	define dbgF(...)
#	define dbgCreateFile(fhdl)
#	define dbgCloseFile(fnm, fhdl, hr)
#endif


#define 	M_HASH_FILE_NAME 0

#ifndef M_HASH_FILE_NAME
#	if SHIPPING_PC_GAME
#		define 	M_HASH_FILE_NAME 1
#	else
#		define 	M_HASH_FILE_NAME 0
#	endif
#endif

#if M_HASH_FILE_NAME
FString TryFindHashFileName( const TCHAR* FilenameSrc );
#endif

#define PAK_EXT	TEXT("pak")
#define PAK_EXT_WITH_POINT	TEXT(".pak")

#define PAK_EXT_SIZE sizeof(PAK_EXT)
#define PAK_EXT_WITH_POINT_SIZE sizeof(PAK_EXT_WITH_POINT)

#define PAK_BASENAME_FORMAT TEXT("%05d")
#define PAK_NAMELEN (5+4)

#define RELATIVE_TO_FULL_FUNC(filename)	GFileManager->ConvertToAbsolutePath(filename)	// appConvertRelativePathToFull()

// MPQ_COMPRESSION_ZLIB...
#define PAK_COMPRESS_TYPE 0

// oscar@snda

/*-----------------------------------------------------------------------------
	FArchiveFileReaderWindows
-----------------------------------------------------------------------------*/

// File manager.
class FArchiveFileReaderMPQ : public FArchive
{
public:
	FArchiveFileReaderMPQ( HANDLE InHandle, INT InStatsHandle, const TCHAR* InFilename, FOutputDevice* InError, INT InSize );
	~FArchiveFileReaderMPQ();

	virtual void Seek( INT InPos );
	virtual INT Tell();
	virtual INT TotalSize();
	virtual UBOOL Close();
	virtual void Serialize( void* V, INT Length );

protected:
	UBOOL InternalPrecache( INT PrecacheOffset, INT PrecacheSize );

	HANDLE          Handle;
	/** Handle for stats tracking */
	INT				StatsHandle;
	/** Filename for debugging purposes. */
	FString			Filename;
	FOutputDevice*  Error;
	INT             Size;
	INT             Pos;
	INT             BufferBase;
	
	INT             BufferCount;

#ifdef _WIN64
	BYTE            Buffer[1024*512];
#else
	BYTE            Buffer[1024*512];
#endif
};


/*-----------------------------------------------------------------------------
	FArchiveFileWriterWindows
-----------------------------------------------------------------------------*/

class FArchiveFileWriterMPQ : public FArchive
{
public:
	FArchiveFileWriterMPQ( HANDLE InHandle, INT InStatsHandle, const TCHAR* InFilename, FOutputDevice* InError, INT InPos );
	~FArchiveFileWriterMPQ();

	virtual void Seek( INT InPos );
	virtual INT Tell();
	virtual INT TotalSize();
	virtual UBOOL Close();
	virtual void Serialize( void* V, INT Length );
	virtual void Flush();

	// oscar@snda
	const FString& GetFileName() const {return Filename;}
	// oscar@snda

protected:
	HANDLE          Handle;
	/** Handle for stats tracking */
	INT				StatsHandle;
	/** Filename for debugging purposes */
	FString			Filename;
	FOutputDevice*  Error;
	INT             Pos;
	INT             BufferCount;
#ifdef _WIN64
	BYTE            Buffer[1024*512];
#else
	BYTE            Buffer[1024*512];
#endif
};


/*-----------------------------------------------------------------------------
	FFileManagerWindows
-----------------------------------------------------------------------------*/

class FFileManagerMPQ : public FFileManagerGeneric
{
public:
	struct FMPQPath
	{
		FString PathMPQ;		// where is the mpq locate in the os
		FString PathInMPQ;		// where is the file locate in the mpq, the name in MPQ

		FMPQPath(const TCHAR* szPathMPQ, const char* szPathInMPQ)
			: PathMPQ(szPathMPQ)
			, PathInMPQ(szPathInMPQ)
		{

		}

		FMPQPath(const FString& strPathMPQ, const char* szPathInMPQ)
			: PathMPQ(strPathMPQ)
			, PathInMPQ(szPathInMPQ)
		{

		}
	};

public:

	virtual ~FFileManagerMPQ();	// zhaojun@snda

	void Init(UBOOL Startup);

	UBOOL SetDefaultDirectory();
	UBOOL SetCurDirectory(const TCHAR* Directory);
	FString GetCurrentDirectory();

	FArchive* CreateFileReader( const TCHAR* InFilename, DWORD Flags, FOutputDevice* Error );
	FArchive* CreateFileWriter( const TCHAR* Filename, DWORD Flags, FOutputDevice* Error, INT MaxFileSize );
	INT	UncompressedFileSize( const TCHAR* Filename );
	DWORD Copy( const TCHAR* DestFile, const TCHAR* SrcFile, UBOOL ReplaceExisting, UBOOL EvenIfReadOnly, UBOOL Attributes, FCopyProgress* Progress );
	UBOOL Delete( const TCHAR* Filename, UBOOL RequireExists=0, UBOOL EvenReadOnly=0 );
	UBOOL IsReadOnly( const TCHAR* Filename );
	UBOOL Move( const TCHAR* Dest, const TCHAR* Src, UBOOL Replace=1, UBOOL EvenIfReadOnly=0, UBOOL Attributes=0 );
	UBOOL MakeDirectory( const TCHAR* Path, UBOOL Tree=0 );
	UBOOL DeleteDirectory( const TCHAR* Path, UBOOL RequireExists=0, UBOOL Tree=0 );
	void FindFiles( TArray<FString>& Result, const TCHAR* Filename, UBOOL Files, UBOOL Directories );
	DOUBLE GetFileAgeSeconds( const TCHAR* Filename );
	DOUBLE GetFileTimestamp( const TCHAR* Filename );
	UBOOL GetTimestamp( const TCHAR* Filename, FTimeStamp& Timestamp );

	/**
	 * Updates the modification time of the file on disk to right now, just like the unix touch command
	 * @param Filename Path to the file to touch
	 * @return TRUE if successful
	 */
	UBOOL TouchFile(const TCHAR* Filename);

	/**
	 * Converts a path pointing into the installed directory (C:\Program Files\MyGame\ExampleGame\Config\ExampleEngine.ini)
	 * to a path that a least-privileged user can write to (C:\<UserDir>\MyGame\ExampleGame\Config\ExampleEngine.ini)
	 *
	 * @param AbsolutePath Source path to convert
	 *
	 * @return Path to the user directory
	 */
	FString ConvertAbsolutePathToUserPath(const TCHAR* AbsolutePath);

	/**
	 * Converts passed in filename to use a relative path.
	 *
	 * @param	Filename	filename to convert to use a relative path
	 * 
	 * @return	filename using relative path
	 */
	FString FFileManagerMPQ::ConvertToRelativePath( const TCHAR* Filename );

	/**
	 * Converts passed in filename to use an absolute path.
	 *
	 * @param	Filename	filename to convert to use an absolute path, safe to pass in already using absolute path
	 * 
	 * @return	filename using absolute path
	 */
	FString ConvertToAbsolutePath( const TCHAR* Filename );

	/**
	 *	Returns the size of a file. (Thread-safe)
	 *
	 *	@param Filename		Platform-independent Unreal filename.
	 *	@return				File size in bytes or INDEX_NONE if the file didn't exist.
	 **/
	virtual INT FileSize( const TCHAR* Filename );

	/**
	 *	Retrieves the total size of a volume and how much free space can be allocated by the caller.
	 *
	 *	@param Drive				Full path for the drive that we want to check: ex. C:\
	 *	@param FreeBytesToCaller	Receives the total number of free bytes on a disk that are available to the user who is associated with the calling thread.
	 *	@param TotalBytes			Receives the total number of bytes on a disk that are available to the user who is associated with the calling thread.
	 *	@param FreeBytes			Receives the total number of free bytes on a disk.
	 *	@return						False if the operation failed to retrieve valid size info, true otherwise. 
	 **/
	UBOOL FFileManagerMPQ::GetDiskFreeSpace(const TCHAR* Drive, QWORD& FreeBytesToCaller, QWORD& TotalBytes, QWORD& FreeBytes );

protected:
	FArchive* InternalCreateFileReader( const TCHAR* InFilename, DWORD Flags, FOutputDevice* Error );

	FArchive* InternalCreateFileWriter( const TCHAR* Filename, DWORD Flags, FOutputDevice* Error );
	/**
	 *	Looks up the size of a file by opening a handle to the file.
	 *
	 *	@param	Filename	The path to the file.
	 *	@return	The size of the file or -1 if it doesn't exist.
	 */
	virtual INT InternalFileSize( const TCHAR* Filename );
	DWORD InternalCopy( const TCHAR* DestFile, const TCHAR* SrcFile, UBOOL ReplaceExisting, UBOOL EvenIfReadOnly, UBOOL Attributes, FCopyProgress* Progress );
	UBOOL InternalDelete( const TCHAR* Filename, UBOOL RequireExists=0, UBOOL EvenReadOnly=0 );
	UBOOL InternalIsReadOnly( const TCHAR* Filename );
	UBOOL InternalMove( const TCHAR* Dest, const TCHAR* Src, UBOOL Replace=1, UBOOL EvenIfReadOnly=0, UBOOL Attributes=0 );
	UBOOL InternalMakeDirectory( const TCHAR* Path, UBOOL Tree=0 );
	UBOOL InternalDeleteDirectory( const TCHAR* Path, UBOOL RequireExists=0, UBOOL Tree=0 );
	void InternalFindFiles( TArray<FString>& Result, const TCHAR* Filename, UBOOL Files, UBOOL Directories );
	DOUBLE InternalGetFileAgeSeconds( const TCHAR* Filename );
	DOUBLE InternalGetFileTimestamp( const TCHAR* Filename );
	UBOOL InternalGetTimestamp( const TCHAR* Filename, FTimeStamp& Timestamp );

	/**
	 * Updates the modification time of the file on disk to right now, just like the unix touch command
	 * @param Filename Path to the file to touch
	 * @return TRUE if successful
	 */
	UBOOL InternalTouchFile(const TCHAR* Filename);

	/**
	 *	Sets the timestamp of a file.
	 *
	 *	@param Filename		Full path to the file.
	 *	@param Timestamp	Timestamp to set
	 *	@return				File size in bytes or -1 if the file didn't exist.
	 **/
	UBOOL InternalSetFileTimestamp( const TCHAR* Filename, DOUBLE TimeStamp );

	/**
	 *	Truncates an existing file, discarding data at the end to make it smaller. (Thread-safe)
	 *
	 *	@param Filename		Full path to the file.
	 *	@param FileSize		New file size to truncate to. If this is larger than current file size, the function won't do anything.
	 *	@return				Resulting file size or INDEX_NONE if the file didn't exist.
	 **/
	INT InternalFileTruncate( const TCHAR* Filename, INT FileSize );

	/**
	 *	Opens a file. (Thread-safe)
	 *	If opened for write, it will create any necessary directory structure.
	 *
	 *	@param Filename		Full path to the file
	 *	@param Flags		A combination of EFileOpenFlags, specifying read/write access.
	 *	@return				File handle
	 **/
	FFileHandle InternalFileOpen( const TCHAR* Filename, DWORD Flags );

	/**
	 *	Retrieves the total size of a volume and how much free space can be allocated by the caller.
	 *
	 *	@param Drive				Full path for the drive that we want to check: ex. C:\
	 *	@param FreeBytesToCaller	Receives the total number of free bytes on a disk that are available to the user who is associated with the calling thread.
	 *	@param TotalBytes			Receives the total number of bytes on a disk that are available to the user who is associated with the calling thread.
	 *	@param FreeBytes			Receives the total number of free bytes on a disk.
	 *	@return						False if the operation failed to retrieve valid size info, true otherwise. 
	 **/
	UBOOL FFileManagerMPQ::InternalGetDiskFreeSpace(const TCHAR* Drive, QWORD& FreeBytesToCaller, QWORD& TotalBytes, QWORD& FreeBytes );

	// return num of files in package, -1 means this file-manager does NOT support package, zhaojun@snda
	virtual INT EnumFilesInPackage(const TCHAR* PackageName, 
		TArray<FString>& FilesList, UBOOL bListPackage, UBOOL bListNonPackage, 
		UBOOL bGenerateMapping);

	static INT EnumFilesInPackage(const TCHAR* PackageName, 
		TArray<FString>& FilesList, UBOOL bListPackage, UBOOL bListNonPackage, 
		TMap<FString, FMPQPath>& FilesToMPQMap, UBOOL bGenerateMapping);

	// return num of files in package under this folder, -1 means this file-manager does NOT support package, zhaojun@snda
	virtual INT GenerateMapFromFileToMPQ(const TCHAR* FolderName);

	static INT GenerateMapFromFileToMPQ(const TCHAR* FolderName, TMap<FString, FMPQPath>& FilesToMPQMap);

	/*zhaojun@snda*/
	virtual HANDLE GetFileHandleByName(IN const TCHAR* szFileName, IN DWORD Flags, IN FOutputDevice* Error, OUT HANDLE& hArchive);

	HANDLE GetFileHandleByName(const TCHAR* szNameInMPQ, HANDLE hArchive);
	HANDLE GetArchiveHandleByName(const TCHAR* szArchiveName);
	HANDLE GetArchiveHandleByName(const TCHAR* szFileName, char szPathInMPQ[], UINT nPathInMPQLen);

public:
	static UBOOL ParsePAKFileMap(TMap<FString, FMPQPath>& PathMap, const TCHAR* PackageName);
	static UBOOL LoadPAKFileMap(TMap<FString, FMPQPath>& PathMap, const TCHAR* FileName);
	
	static UBOOL PackFolder(const TCHAR* FolderName, const TArray<FString>* ArrayExcludeFiles,
		TMap<FString, FMPQPath>& RefPathMap,
		UINT expectedSize = 1073741824, UINT maxSize = 2147483648, 
		UBOOL bDelSrc = FALSE);

	static UBOOL PackFiles(const FString& destPackage, TArray<FString>& Srcfiles, UBOOL bDelSrc = FALSE);

public:
	/** Directory where a Standard User can write to (to save settings, etc) */
	FString WindowsUserDir;

	/** Directory where the game in installed to */
	FString WindowsRootDir;

	/** Is the game running as if installed, ie, out of a directory a Standard User can't write to? */
	UBOOL bIsRunningInstalled;

	TMap<FString, HANDLE>	MapMPQHandle;	// zhaojun@snda, handle of opened mpqs

	TMap<FString, FMPQPath> MapFilesToMPQ;	// zhaojun@snda, map from file-name to (packname, path in package)

#if M_TRACE_FILE_HANDLE // oscar@snda
public:

	struct FTraceFileHandleInfo
	{
		HANDLE Handle;
		FString FileName;

		FTraceFileHandleInfo(HANDLE h, const TCHAR* fnm)
		{
			Handle = h;
			FileName = fnm;
		}
	};

	TMap<HANDLE, FTraceFileHandleInfo> TraceFHMap;
	void _AddToTraceMap(FTraceFileHandleInfo info);
	void _RemoveFromTraceMap(HANDLE hdl);
	virtual void _DumpFileHandleTraceMap();

#	define TRACE_FILE_HANDLE_ADD(h, fileNm) ((FFileManagerMPQ*)GFileManager)->_AddToTraceMap(FTraceFileHandleInfo(h, fileNm))
#	define TRACE_FILE_HANDLE_REMOVE(h) ((FFileManagerMPQ*)GFileManager)->_RemoveFromTraceMap(h)
#else
#	define TRACE_FILE_HANDLE_ADD(h, fileNm)
#	define TRACE_FILE_HANDLE_REMOVE(h)
#endif  // oscar@snda

};

#endif	// WITH_STORMLIB	// zhaojun@snda
#endif
