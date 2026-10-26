#ifdef _DEBUG
#define check(express) assert(express)
#else
#define check(express) if (!(express)) OutputInfo(BuildinLog, "%s\n", #express);
#endif

void ParseCmdLine(std::vector<std::string>& vCmdString, const char* pCmdLine)
{
	const char* pHead = pCmdLine;

	while (*pHead == ' ')
	{
		++pHead;
	}

	const char* pTail = pHead;

	while (1)
	{
		if (*pTail == ' ' || *pTail == 0)
		{
			vCmdString.push_back(std::string(pHead, pTail));

			if (*pTail == 0)
				break;

			while(*pTail == ' ')
			{
				++pTail;
			}

			pHead = pTail;
		}

		++pTail;
	}
}

class PathString : public std::string
{
public:
	PathString()
		: std::string()
	{

	}

	PathString(const char* p)
		: std::string(p)
	{

	}

	PathString(const char* p, UINT len)
		: std::string(p, len)
	{

	}

	PathString(const char* s, const char* e)
		: std::string(s, e)
	{

	}

	PathString(const std::string& rhs)
		: std::string(rhs)
	{

	}

	PathString(const WCHAR* p)
	{
		char szTemp[1024];

		WideCharToMultiByte(CP_ACP,0,p,(DWORD)(wcslen(p))+1,szTemp,sizeof(szTemp),NULL,NULL);

		assign(szTemp);
	}

	PathString(const PathString& rhs)
	{
		assign(rhs);
	}

	operator const char*() const
	{
		return c_str();
	}

	void AppendInt(int n)
	{
		// 强行叠一个数字
		append((const char*)(&n), sizeof(n));
	}

	void AppendStringWithLen(const PathString& s)
	{
		AppendInt(s.size());
		append(s);
	}

	// used for map::find
	//bool operator==(const PakPathString& rhs)
	//{
	//	return true;
	//}

	//bool operator!=(const PakPathString& rhs)
	//{
	//	return true;
	//}

	// >=, >, <=, <

	//const char* c_str() const
	//{
	//	return std::string::c_str();
	//}

	//const WCHAR* C_STR() const
	//{

	//}
};


void ExtractString(PathString& str, const char*& p, unsigned int len)
{
	str.assign(p, len);

	p += len;
}

void ExtractInt(int& n, const char*& p)
{
	const int* pn = (const int*)(p);

	n = *pn;

	p += sizeof(int);
}

void ExtractString(PathString& str, const char*& p)
{
	int n;
	ExtractInt(n, p);
	ExtractString(str, p, n);
}

void GetConfigDirs(std::vector<PathString>& VersionSubDirs, const char* pConfigFileName)
{
	FILE* hFile = NULL;

	fopen_s(&hFile, pConfigFileName, "r");

	if (hFile != NULL)
	{
		char szBuff[1024];

		while(fscanf_s(hFile, "%s", szBuff) != EOF )
		{
			VersionSubDirs.push_back(szBuff);
		}

		fclose(hFile);
	}
}


class DeleteFileMap : public std::map<PathString, std::vector<PathString>>
{
public:
	bool ToString(PathString& data) const
	{
		if (size() > 0)
		{
			data += PATCH_DEL_TABLE_FILE_MAGIC;
			data += PATCH_DEL_TABLE_FILE_VER;

			data.AppendInt(size());

			DeleteFileMap::const_iterator itor;

			for (itor = begin(); itor != end(); ++itor)
			{
				const PathString& Pak = itor->first;
				const std::vector<PathString>& SubPaths = itor->second;

				data.AppendStringWithLen(Pak);

				data.AppendInt(SubPaths.size());
				for (unsigned int p = 0; p < SubPaths.size(); ++p)
				{
					const PathString& DelFileName = SubPaths[p];
					data.AppendStringWithLen(DelFileName);
				}
			}

			return true;
		}
		else
		{
			return false;
		}
	}

	void FromString(const PathString& data)
	{
		const char* p = data.c_str();

		PathString temp;

		ExtractString(temp, p, strlen(PATCH_DEL_TABLE_FILE_MAGIC));

		check(temp == PATCH_DEL_TABLE_FILE_MAGIC);

		ExtractString(temp, p, strlen(PATCH_DEL_TABLE_FILE_VER));

		check(temp == PATCH_DEL_TABLE_FILE_VER);

		int count;

		ExtractInt(count, p);

		for (int i = 0; i < count; ++i)
		{
			ExtractString(temp, p);

			int nDelCount = 0;

			ExtractInt(nDelCount, p);

			std::vector<PathString>& DelFiles = operator[](temp);

			for (int f = 0; f < nDelCount; ++f)
			{
				ExtractString(temp, p);

				DelFiles.push_back(temp);
			}
		}
	}
};

class RenameFileMap : public std::map<PathString, std::vector<std::pair<PathString, PathString>>>
{
public:
	bool ToString(PathString& data) const
	{
		if (size() > 0)
		{
			data += PATCH_RENAME_TABLE_FILE_MAGIC;
			data += PATCH_RENAME_TABLE_FILE_VER;

			data.AppendInt(size());

			const_iterator itor;

			for (itor = begin(); itor != end(); ++itor)
			{
				const PathString& Pak = itor->first;
				const std::vector<std::pair<PathString, PathString>>& SubPaths = itor->second;

				data.AppendStringWithLen(Pak);

				data.AppendInt(SubPaths.size());

				for (unsigned int p = 0; p < SubPaths.size(); ++p)
				{
					const std::pair<PathString, PathString>& RenameFile = SubPaths[p];
					data.AppendStringWithLen(RenameFile.first);
					data.AppendStringWithLen(RenameFile.second);
				}
			}

			return true;
		}
		else
		{
			return false;
		}
	}

	void FromString(PathString& data)
	{
		const char* p = data.c_str();

		PathString temp;
		PathString temp2;

		ExtractString(temp, p, strlen(PATCH_RENAME_TABLE_FILE_MAGIC));

		check(temp == PATCH_RENAME_TABLE_FILE_MAGIC);

		ExtractString(temp, p, strlen(PATCH_RENAME_TABLE_FILE_VER));

		check(temp == PATCH_RENAME_TABLE_FILE_VER);

		int count;

		ExtractInt(count, p);

		for (int i = 0; i < count; ++i)
		{
			ExtractString(temp, p);

			int nDelCount = 0;

			ExtractInt(nDelCount, p);

			std::vector<std::pair<PathString, PathString>>& RenameFiles = operator[](temp);

			for (int f = 0; f < nDelCount; ++f)
			{
				ExtractString(temp, p);
				ExtractString(temp2, p);

				RenameFiles.push_back(std::pair<PathString, PathString>(temp, temp2));
			}
		}
	}
};

#include <atlstr.h>

bool IsDirExist(const LPCSTR dir)
{
	DWORD attr;
	attr = GetFileAttributes(dir);

	return ((attr != (DWORD)-1) && (attr & FILE_ATTRIBUTE_DIRECTORY));
}

bool IsFileExist(const LPCSTR f)
{
	DWORD attr;
	attr = GetFileAttributes(f);

	return ((attr != (DWORD)-1) && (!(attr & FILE_ATTRIBUTE_DIRECTORY)));
}

bool mkDir(std::string filePath, bool bRecurse, bool bIncludeLastLayer = false)
{
	//统一路径分隔符
	//filePath.Replace('/', '\\');

	int len = filePath.size();
	if(len < 2)
		return false;

	//去掉最后的斜杠
	while(len != 0 && (filePath[len - 1] == '\\' || filePath[len - 1] == '/'))
	{
		filePath.assign(filePath.c_str(), len - 1);
		len = filePath.size();
	}

	if(len <= 0 )    return false;

	//已经存在直接返回成功
	if(IsDirExist(filePath.c_str()))
	{
		return true;
	}

	//类似G:这样的目录不允许创建
	if(len == 2)    return false;

	//不递归创建，直接返回创建结果
	if(!bRecurse)
	{
		return CreateDirectory(filePath.c_str(), NULL) == TRUE;
	}

	//递归创建目录
	std::string topDir ;
	const char* pTail = strchr(filePath.c_str(), '\\');
	if (pTail == NULL)
	{
		pTail = strchr(filePath.c_str(), '/');
	}

	while(NULL != pTail)
	{
		topDir.assign(filePath.c_str(), pTail);

		const char* const pTemp = pTail;
		pTail = strchr(pTail + 1, '\\');
		if (pTail == NULL)
		{
			pTail = strchr(pTemp + 1, '/');
		}

		//存在
		if(IsDirExist(topDir.c_str()))
		{
			continue;
		}

		//不存在
		CreateDirectory(topDir.c_str(), NULL);  
	}

	if(bIncludeLastLayer)
		return CreateDirectory(filePath.c_str(), NULL) == TRUE; 

	return 0;
}


INT CreateDirectoryHierarchy(const char* Path, bool bIncludeLastLayer = false)
{
	return (INT)mkDir(Path, true, bIncludeLastLayer);

	INT CreateCount=0;

	char Full[1024]=("");

	for(char* Ptr=Full; ; *Ptr++=*Path++)
	{
		if( (*Path)=='\\' || (*Path)=='/' || (bIncludeLastLayer && *Path==0) )
		{
			*Ptr = 0;

			if( Ptr != Full)
			{
				if( !CreateDirectory( Full, 0 ) )
				{
					int err = GetLastError();

					if (err != ERROR_ALREADY_EXISTS)
					{
						return 0;
					}
					else
					{
						printf("Create failed: %x %s\n", err, Full);
					}
				}

				++CreateCount;
			}
		}

		if( *Path==0 )
		{
			break;
		}
	}

	return CreateCount!=0;
}

DWORD GetFileSize(const char* FileName)
{
	HANDLE Handle = CreateFile( FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

	if( Handle==INVALID_HANDLE_VALUE )
	{
		return -1;
	}

	DWORD Result = GetFileSize( Handle, NULL );
	BOOL hr = CloseHandle( Handle );

	return Result;
}

void EnumFilesInDirectory(std::vector<PathString>& files, 
	const char* FolderName, const char* ExtNameWithPoint = NULL, 
	bool bRecursive = true, const std::set<PathString>* ExcludeFiles = NULL)
{
	HANDLE Handle=NULL;

	WIN32_FIND_DATA fd;

	check(strchr(FolderName, '/') == NULL);
	check(*(FolderName + strlen(FolderName) - 1) != '\\');

	PathString strPath(FolderName);

	strPath += "\\*.*";

	Handle=FindFirstFile(strPath.c_str(),&fd);

	if( Handle!=INVALID_HANDLE_VALUE )
	{
		do
		{
			if(fd.cFileName[0] != '.' && (ExcludeFiles == NULL || ExcludeFiles->find(fd.cFileName) == ExcludeFiles->end()))
			{
				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (bRecursive)
					{
						strPath.assign(FolderName);
						strPath += "\\";
						strPath += fd.cFileName;

						EnumFilesInDirectory(files, strPath.c_str(), ExtNameWithPoint, bRecursive);
					}
				}
				else if (ExtNameWithPoint == NULL || strstr(fd.cFileName, ExtNameWithPoint) != NULL)
				{
					strPath = FolderName;
					strPath += "\\";
					strPath += fd.cFileName;

					files.push_back(strPath);
				}
			}

		}
		while( FindNextFile(Handle,&fd) );

		FindClose( Handle );
	}
}

void DeleteFilesInDirectory(const char* FolderName, bool bRecursive)
{
	/*
	char szCmd[1024];
	sprintf_s(szCmd, sizeof(szCmd), "del /s/q %s", FolderName);
	system(szCmd);

	sprintf_s(szCmd, sizeof(szCmd), "rd /s/q %s", FolderName);
	system(szCmd);
	*/

	HANDLE Handle = NULL;
	WIN32_FIND_DATA fd;

	check(strchr(FolderName, '/') == NULL);
	check(*(FolderName + strlen(FolderName) - 1) != '\\');

	PathString strPath(FolderName);
	strPath += "\\*.*";
	Handle=FindFirstFile(strPath.c_str(),&fd);
	if (Handle != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (fd.cFileName[0] != '.')
			{
				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (bRecursive)
					{
						strPath.assign(FolderName);
						strPath += "\\";
						strPath += fd.cFileName;

						DeleteFilesInDirectory(strPath.c_str(), bRecursive);
						::RemoveDirectory((LPCSTR)strPath);
					}
				}
				else
				{
					strPath = FolderName;
					strPath += "\\";
					strPath += fd.cFileName;

					if (IsFileExist(strPath))
					{// 去除文件的只读属性， 否则会删除失败
						DWORD attr = ::GetFileAttributes((LPCSTR)strPath);
						attr &= ~FILE_ATTRIBUTE_READONLY;
						::SetFileAttributes((LPCSTR)strPath, attr);
					}

					::DeleteFile(strPath);
				}
			}

		} while (FindNextFile(Handle,&fd));

		FindClose(Handle);
	}
}

class MPQPath
{

public:
	PathString MPQFilePath;		// where is the mpq locate in the os
	PathString InMPQPath;		// where is the file locate in the mpq, the name in MPQ

	MPQPath()
	{

	}

	MPQPath(const char* szMPQFilePath, const char* szInMPQPath)
		: MPQFilePath(szMPQFilePath)
		, InMPQPath(szInMPQPath)
	{

	}

};

class PakFileInfo
{
public:
	PathString SrcFileName;

	PathString RefMPQFilePath;
	PathString RefInMPQPath;

public:
	PakFileInfo()
	{

	}

	PakFileInfo(const PathString& SrcFile)
		: SrcFileName(SrcFile)
	{

	}

	PakFileInfo(const PathString& SrcFile, const PathString& MPQ, const PathString& InMPQ)
		: SrcFileName(SrcFile)
		, RefMPQFilePath(MPQ)
		, RefInMPQPath(InMPQ)
	{

	}
};

class ArchiveInfo
{
public:

	UINT ArchiveRawSize;
	// patch size must be smaller or equal than size

	union
	{
		struct  
		{
			//HANDLE hArchive;
			//HANDLE hPatchArchive;

			std::vector<PathString> EntireFiles;
			std::vector<PathString> PatchFiles;

			std::vector<PathString> EntirePathsInMPQ;
			std::vector<PathString> PatchPathsInMPQ;
		};

		struct
		{
			//HANDLE hArchives[2];
			std::vector<PathString> Files[2];
			std::vector<PathString> PathsInMPQ[2];
		};
	};

	ArchiveInfo()
	{
		//hArchive = NULL;
		ArchiveRawSize = 0;


		//hPatchArchive = NULL;
	}

	void AddFile(const char* pFile, const char* pRelativePathInMPQ, UINT nFileSize = 0)
	{
		check(pFile && pRelativePathInMPQ);

		EntireFiles.push_back(pFile);
		EntirePathsInMPQ.push_back(pRelativePathInMPQ);

		check(0 == nFileSize || nFileSize == GetFileSize(pFile));

		ArchiveRawSize += (nFileSize == 0 ? GetFileSize(pFile) : nFileSize);
	}

	void AddPatchFile(const char* pFile, const char* pRelativePathInMPQ)
	{
		check(pFile && pRelativePathInMPQ);

		PatchFiles.push_back(pFile);
		PatchPathsInMPQ.push_back(pRelativePathInMPQ);
	}
};

INT EnumFilesInPackage(const char* PackageName, 
	std::map<PathString, MPQPath>& FilesToMPQMap, const char* pPathHeader/* = NULL*/)
{
	HANDLE hArchive = NULL;

	SFileOpenArchive(PackageName, 0, STREAM_PROVIDER_FLAT, &hArchive);

	INT nCount = 0;

	if (hArchive)
	{
		SFILE_FIND_DATA fd;
		HANDLE hFind = SFileFindFirstFile(hArchive, "*", &fd, NULL);

		if (hFind)
		{
			do 
			{
				if (strcmp(fd.cFileName, "(listfile)") != 0 && strcmp(fd.cFileName, "(attributes)") != 0)
				{
					PathString strFile;

					if (pPathHeader)
					{
						strFile = pPathHeader;
						strFile += "\\";
						strFile += fd.cFileName;
					}
					else
					{
						strFile = fd.cFileName;
					}

					check(FilesToMPQMap.find(strFile) == FilesToMPQMap.end());
					FilesToMPQMap[strFile] = MPQPath(PackageName, fd.cFileName);

					++nCount;
				}

			} while (SFileFindNextFile(hFind, &fd));

			SFileFindClose(hFind);
		}

		SFileCloseArchive(hArchive);
	}
	else
	{
		// warning
	}

	return nCount;
}

void PushDeleteFile(DeleteFileMap& DeleteFiles, const MPQPath& rPath)
{
	PathString key(rPath.MPQFilePath.c_str() + rPath.MPQFilePath.size() - PAK_NAME_LEN);
	DeleteFiles[key].push_back(rPath.InMPQPath);
}

void PushRenameFile(RenameFileMap& RenameFiles, 
	const MPQPath& rPath, const PathString& NewInMPQPath)
{
	PathString key(rPath.MPQFilePath.c_str() + rPath.MPQFilePath.size() - PAK_NAME_LEN);
	RenameFiles[key].push_back(std::pair<PathString, PathString>(rPath.InMPQPath, NewInMPQPath));
}

#include <xiosbase>
#include <fstream>
#include "md5.h"

// if changed return true, otherwise false
bool CompareFile(const PathString& FileName, 
	const PathString& MPQName, const PathString& PathInMPQ)
{
	DWORD dwRefFileSize = 0;
	DWORD dwSrcFileSize = 0;

	unsigned char* szRefFile = NULL;

	bool bUpdated = false;

	HANDLE hArchive = NULL;
	SFileOpenArchive(MPQName, 0, STREAM_PROVIDER_FLAT, &hArchive);

	if (hArchive)
	{
		HANDLE hFile = NULL;
		SFileOpenFileEx(hArchive, PathInMPQ, 0, &hFile);

		if (hFile)
		{
			dwRefFileSize = SFileGetFileSize(hFile, NULL);

			dwSrcFileSize = GetFileSize(FileName);

			if (dwRefFileSize != dwSrcFileSize)
			{
				//  different size
				bUpdated = true;
			}
			else if (dwRefFileSize > 0)
			{
				// same size and greater than 0
				szRefFile = new unsigned char[dwRefFileSize];

				DWORD dwRead = 0;

				SFileReadFile(hFile, szRefFile, dwRefFileSize, &dwRead, NULL);

				check(dwRead == dwRefFileSize);

				bUpdated = false;
			}
			else
			{
				// both 0
				bUpdated = false;
			}

			SFileCloseFile(hFile);
		}

		SFileCloseArchive(hArchive);
	}


	if (szRefFile != NULL)
	{
		FILE* pSrcFile = NULL;
		fopen_s(&pSrcFile, FileName.c_str(), "rb");

		if (pSrcFile)
		{
			MD5 SrcMD5(pSrcFile);
			fclose(pSrcFile);

			MD5 RefMD5;
			RefMD5.update(szRefFile, dwRefFileSize);
			RefMD5.finalize();

			char* pSrcDigest = SrcMD5.hex_digest();
			char* pRefDigest = RefMD5.hex_digest();

			const unsigned char* pSrcRaw = SrcMD5.raw_digest2();
			const unsigned char* pRefRaw = RefMD5.raw_digest2();

			bUpdated = !!memcmp(pSrcRaw, pRefRaw, 16);
		}

		delete [] szRefFile;
	}

	return bUpdated;
}

bool CompareFile(const PathString& FileName, const PathString& RefFileName)
{
	DWORD dwRefFileSize = 0;
	DWORD dwSrcFileSize = 0;

	unsigned char* szRefFile = NULL;

	bool bUpdated = false;

	HANDLE hArchive = NULL;

	dwSrcFileSize = GetFileSize(FileName);
	dwRefFileSize = GetFileSize(RefFileName);

	if (dwSrcFileSize != dwRefFileSize)
	{
		bUpdated = true;
	}
	else
	{
		FILE* pSrcFile = NULL;
		FILE* pRefFile = NULL;
		fopen_s(&pSrcFile, FileName.c_str(), "rb");
		fopen_s(&pRefFile, RefFileName.c_str(), "rb");

		if (pSrcFile && pRefFile)
		{
			MD5 SrcMD5(pSrcFile);

			if (pSrcFile)
				fclose(pSrcFile);

			MD5 RefMD5(pRefFile);
			if (pRefFile)
				fclose(pRefFile);

			char* pSrcDigest = SrcMD5.hex_digest();
			char* pRefDigest = RefMD5.hex_digest();

			const unsigned char* pSrcRaw = SrcMD5.raw_digest2();
			const unsigned char* pRefRaw = RefMD5.raw_digest2();

			bUpdated = !!memcmp(pSrcRaw, pRefRaw, 16);
		}
	}

	return bUpdated;
}

#include <algorithm>
bool CompareFileWithMD5(const PathString& FileName, const PathString& md5)
{
	bool bSucc = false;

	FILE* pSrcFile = NULL;
	fopen_s(&pSrcFile, FileName.c_str(), "rb");
	if (pSrcFile)
	{
		MD5 SrcMD5(pSrcFile);
		fclose(pSrcFile);

		PathString strSrcMD5 = SrcMD5.hex_digest();
		PathString strDstMD5 = md5;

		std::transform(strSrcMD5.begin(), strSrcMD5.end(), strSrcMD5.begin(), ::tolower);
		std::transform(strDstMD5.begin(), strDstMD5.end(), strDstMD5.begin(), ::tolower);

		bSucc = (strSrcMD5 == strDstMD5);
	}

	return bSucc;
}

void ExtractPackageDirectory(const PathString& PackagePath, PathString& PackageDirectory)
{
	PackageDirectory.assign(PackagePath.c_str(), PackagePath.size() - PAK_NAME_LEN);
}

void ExtractPackageFileBaseName(const PathString& PackagePath, PathString& PackageFileName)
{
	PackageFileName.assign(PackagePath.c_str() + PackagePath.size() - PAK_NAME_LEN, PAK_BASENAME_LEN);
} 

INT GenerateFileToMPQMap(const char* FolderName, 
	std::map<PathString, MPQPath>& FilesToMPQMap, bool bRelativePath = true)
{
	std::vector<PathString> MPQFiles;

	EnumFilesInDirectory(MPQFiles, FolderName, PAK_EXT_WITH_POINT, false);

	INT nCount = 0;

	for (UINT i = 0; i < MPQFiles.size(); ++i)
	{
		const char* PackageName = MPQFiles[i].c_str();

		nCount += EnumFilesInPackage(PackageName, FilesToMPQMap, bRelativePath ? NULL : FolderName);
	}

	return nCount;
}

#include "Markup.h"

bool ParseDirectFileSection(LPCTSTR lpszDirectFile, LPCTSTR lpszSectionName, std::map<std::string, std::string> &mapKeyValue)
{
	CMarkup markup;
	bool bSucceed = markup.Load(lpszDirectFile);
	if (bSucceed)
	{
		bSucceed = markup.FindElem();
		if (bSucceed)
		{
			bSucceed = markup.IntoElem();
			if (bSucceed)
			{
				bSucceed = markup.FindElem(lpszSectionName);
				if (bSucceed)
				{
					markup.IntoElem();
					while(markup.FindElem())
					{
						mapKeyValue[markup.GetAttrib(STR_DIRECT_FILE_SUB_ITEM_KEY_ATTRIB)] = markup.GetAttrib(STR_DIRECT_FILE_SUB_ITEM_VALUE_ATTRIB);
					}
					markup.OutOfElem();
				}
			}
			markup.OutOfElem();
		}
	}
	return true;
}