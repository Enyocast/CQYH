
// stdafx.cpp : 只包括标准包含文件的源文件
// dump_analyze.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


extern std::string NormalizePath(const char* pcPath)
{
	char strPath[MAX_PATH];
	char* pcFilePart;
	GetFullPathName(pcPath, MAX_PATH, strPath, &pcFilePart);
	_strlwr_s(strPath, MAX_PATH);
	return strPath;
}
extern void ConvertToDOSName( char *dst, const char *src )
{
	while ( *src )
	{
		if ( *src == '/' )
			*dst = '\\';
		else
			*dst = *src;
		dst++; src++;
	}
	*dst = 0;
}
extern void ConfirmSlash( std::string& strPath )
{
	if( strPath.length() > 0)
	{
		if (strPath[strPath.length()-1] != '\\')
			strPath += '\\';
	}
}
extern std::string ExtractFileName(const std::string& strPathFileName)  
{
	char szDosName[MAX_PATH];
	ConvertToDOSName(szDosName, strPathFileName.c_str());
	return strPathFileName.substr( std::string(szDosName).rfind("\\") + 1 );

	//return strPathFileName.substr( strPathFileName.rfind("\\") + 1 );
}
extern std::string ExtractFileExt( const std::string& strPathFileName )
{
	char szDosName[MAX_PATH];
	ConvertToDOSName(szDosName, strPathFileName.c_str());

	std::string strFileName( szDosName );
	if( strPathFileName.rfind("\\") != std::string::npos )
	{
		strFileName = ExtractFileName(strPathFileName);
	}

	size_t pos = strFileName.find_last_of(".");
	if( pos != std::string::npos)
	{
		return strFileName.substr( pos );
	}
	else
	{
		return "";
	}
}
extern bool GetFullPathFileList(std::vector<std::string>& vtFiles,std::string strPath, const std::string& strPostfix, bool bFindSubDir, bool bIncludeDir)
{
	ConfirmSlash( strPath ) ;

	std::string findPath = strPath + "*";
	//strPath += "*." + strPostfix;
	WIN32_FIND_DATA FileData;
	HANDLE FindHandle=::FindFirstFile(findPath.c_str(),&FileData);
	bool bIsOver = FindHandle==INVALID_HANDLE_VALUE;
	while(!bIsOver)	
	{    
		if( bFindSubDir && (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && FileData.cFileName[0] != '.')//判断是否是目录
		{
			if(bIncludeDir)
				vtFiles.push_back(FileData.cFileName);
			GetFileList(vtFiles, strPath + FileData.cFileName, strPostfix, bFindSubDir, bIncludeDir);
		}
		else if(FileData.cFileName[0]!=_T('.'))
		{
			if(strPostfix == "*" || _stricmp(ExtractFileExt(FileData.cFileName).c_str(), strPostfix.c_str()) == 0)
			{
				vtFiles.push_back(strPath + FileData.cFileName);
			}
		}
		bIsOver=!FindNextFile(FindHandle,&FileData);
	}	
	FindClose(FindHandle);
	return true;
}
extern bool GetFileList(std::vector<std::string>& vtFiles,std::string strPath, const std::string& strPostfix, bool bFindSubDir, bool bIncludeDir)
{
	if(bFindSubDir)
		return GetFullPathFileList(vtFiles, strPath, strPostfix, bFindSubDir);

	ConfirmSlash( strPath ) ;

	std::string findPath = strPath + "*";
	//strPath += "*." + strPostfix;
	WIN32_FIND_DATA FileData;
	HANDLE FindHandle=::FindFirstFile(findPath.c_str(),&FileData);
	bool bIsOver = FindHandle==INVALID_HANDLE_VALUE;
	while(!bIsOver)	
	{    
		if( bFindSubDir && (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && FileData.cFileName[0] != '.')//判断是否是目录
		{
			if(bIncludeDir)
				vtFiles.push_back(FileData.cFileName);
			GetFileList(vtFiles, strPath + FileData.cFileName, strPostfix, bFindSubDir, bIncludeDir);
		}
		else if(FileData.cFileName[0]!=_T('.'))
		{
			if(strPostfix == "*" || ExtractFileExt(FileData.cFileName) == strPostfix)
				vtFiles.push_back(FileData.cFileName);
		}
		bIsOver=!FindNextFile(FindHandle,&FileData);
	}	
	FindClose(FindHandle);
	return true;
}
extern bool DirExist(const std::string& strDir)  
{
	DWORD ln_Attr = ::GetFileAttributes( strDir.c_str() );
	//return (ln_Attr!=INVALID_FILE_ATTRIBUTES)&&((FILE_ATTRIBUTE_DIRECTORY&ln_Attr)!=0) ? true : false;
	return ( ln_Attr != INVALID_FILE_ATTRIBUTES) && ( (FILE_ATTRIBUTE_DIRECTORY & ln_Attr) !=0 ) ? true : false;
}
extern void ConfirmDir( const std::string& strDir )  
{
	char szDosName[MAX_PATH];
	ConvertToDOSName(szDosName, strDir.c_str());

	std::string strTmp( szDosName );
	ConfirmSlash(strTmp);
	if (DirExist(strTmp)) return;
	std::string::size_type ln_Pos = strTmp.find("\\");
	if (ln_Pos==std::string::npos) return;
	for ( ; ; ) 
	{
		ln_Pos = strTmp.find("\\",ln_Pos+1);
		if (ln_Pos==std::string::npos) break;
		::CreateDirectory(strTmp.substr(0,ln_Pos).c_str(),NULL);
		if (ln_Pos==strTmp.size()) break;
	}
	return;
}
extern bool CopyDir(const std::string &strSrcDir, const std::string &strDesDir)
{
	if (strDesDir == strSrcDir)
	{
		return true;
	}
	bool bRes = true;

	std::string newSrcDir = strSrcDir;
	std::string newDesDir = strDesDir;
	//
	// begin to copy files and create subfolders
	//
	BOOL bFind = TRUE;
	WIN32_FIND_DATA wfd;
	std::string strAllFiles;
	strAllFiles += newSrcDir;
	strAllFiles += "*.*";
	HANDLE hFind = FindFirstFile(strAllFiles.c_str(), &wfd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return false;
	}

	std::string strTmp;

	while (bFind)
	{
		if ('.' != wfd.cFileName[0])
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//通过文件属性判断是文件夹还是文件
			{
				strTmp = newDesDir + wfd.cFileName + '\\';
				ConfirmDir(strTmp);
				bRes = bRes & CopyDir(newSrcDir + wfd.cFileName + '\\', strTmp);
			}//if
			else
			{
				std::string strNewSrcDirTmp, strNewDesDirTmp;
				strNewSrcDirTmp = newSrcDir + wfd.cFileName;
				strNewDesDirTmp = newDesDir + wfd.cFileName;

				bRes = bRes && CopyFile(strNewSrcDirTmp.c_str(), strNewDesDirTmp.c_str(), false);
			}
		}//
		bFind = FindNextFile(hFind, &wfd);
	}//while
	FindClose(hFind);

	return bRes;
}
extern bool DeleteDir( const std::string& dir )
{
	std::string strDir = dir;
	if (*strDir.rbegin() == '\\' || *strDir.rbegin() == '/')
		strDir.erase(strDir.begin() + strDir.size() - 1, strDir.end());

	SHFILEOPSTRUCT FileStruct;
	const int ENDFLAGLEN = 2;
	FileStruct.hwnd = ::GetDesktopWindow();
	FileStruct.wFunc = FO_DELETE;
	char* pBuf;
	pBuf = new char[ strDir.length() + ENDFLAGLEN ];
	::ZeroMemory( pBuf, strDir.length() + ENDFLAGLEN );
	strDir.copy( pBuf,strDir.length() );
	FileStruct.pFrom = pBuf;
	FileStruct.pTo = NULL;
	FileStruct.fFlags = FOF_SILENT|FOF_NOCONFIRMATION|FOF_NOERRORUI;
	//删除文件
	int nResult = ::SHFileOperation( &FileStruct );
	delete[] pBuf;
	return nResult==0 ? true : false;
}