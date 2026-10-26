// *************************************************************************************
// 
// 
// 	All Rights Reserved 
// 
// 	Create Date		:		2006-8-28
// *************************************************************************************

#include "StdAfx.h"
#include "File.h"

#include <direct.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <io.h>

TStringList Parse2StringList(const tstring& str, const tstring& sepStr)
{
	SAFE;

	TStringList strList;
	// <string0><sepStr><string1>...
	if(!str.empty())
	{
		size_t first = str.find_first_of(sepStr);
		size_t pos = 0;
		while(first != tstring::npos)
		{
			strList.push_back(str.substr(pos, first-pos));
			pos = first + 1;
			first = str.find(sepStr, pos);
		}
		tostringstream os;
		os << *(str.end() - 1);
		if(os.str() != sepStr)		// Push the last one
		{
			strList.push_back(str.substr(pos, str.size() - pos));
		}
	}
	return strList;

	UNSAFE;
}



bool File::IsFileExist(const CString& filePath)
{
	return _taccess((LPCTSTR)filePath, 0) != -1;
}

CString File::GetFileNameFromFullPath(const CString& fullPath)
{
	TCHAR driveName[MAX_PATH];
	TCHAR dirName[MAX_PATH];
	TCHAR fileName[MAX_PATH];
	TCHAR fileExt[MAX_PATH];
	_tsplitpath_s((LPCTSTR)fullPath, driveName, MAX_PATH,
		dirName, MAX_PATH, fileName, MAX_PATH, fileExt, MAX_PATH);
	CString fileNameEx = CString(fileName) + CString(fileExt);
	return fileNameEx;
}


CString File::GetFileWithoutExtNameFromFullPath(const CString& fullPath)
{
	TCHAR driveName[MAX_PATH];
	TCHAR dirName[MAX_PATH];
	TCHAR fileName[MAX_PATH];
	TCHAR fileExt[MAX_PATH];
	_tsplitpath_s((LPCTSTR)fullPath, driveName, MAX_PATH,
		dirName, MAX_PATH, fileName, MAX_PATH, fileExt, MAX_PATH);
	return fileName;
}

CString File::GetFileExtFromFullPath(const CString& fullPath)
{
	TCHAR driveName[MAX_PATH];
	TCHAR dirName[MAX_PATH];
	TCHAR fileName[MAX_PATH];
	TCHAR fileExt[MAX_PATH];
	_tsplitpath_s((LPCTSTR)fullPath, driveName, MAX_PATH,
		dirName, MAX_PATH, fileName, MAX_PATH, fileExt, MAX_PATH);
	CString fileNameEx = CString(fileExt);
	return fileNameEx;
}


//--------------------------------------------------------------------------------------

bool File::IsDirExist(const CString& dirPath)
{
	return _taccess((LPCTSTR)dirPath, 0) != -1;
}

//--------------------------------------------------------------------------------------

bool File::MakeDir(const CString& dirName)
{
	TCHAR strDir[MAX_PATH];
	TCHAR strPath[MAX_PATH];
	TCHAR strName[MAX_PATH];
	TCHAR strExt[MAX_PATH];
	_tsplitpath_s(dirName, strDir, strPath, strName, strExt);

	TStringList dirList = Parse2StringList(strPath, _T("\\"));

	TStringList::iterator it = dirList.begin();
	while (it != dirList.end())
	{
		tstring str = *it;
		if(str.empty())
		{
			it = dirList.erase(it);
		}
		else
		{
			++it;
		}
	}

	size_t cnt = dirList.size();
	
	for (size_t i = 0; i < cnt; ++i)
	{
		tstring tmpDir = tstring(strDir) + _T("\\");
		for(size_t j = 0; j <= i; ++j)
		{
			tmpDir += dirList[j] + _T("\\");
		}
		
		if(!IsDirExist(tmpDir.c_str()))
		{
			//tmpDir = _T("\"") + tmpDir + _T("\"");
			_tmkdir(tmpDir.c_str());
		}
	}

	return IsDirExist(dirName);
}

//--------------------------------------------------------------------------------------

CString File::NormalizePath(const CString& fullPath, const CString& sep)
{
	if(fullPath.IsEmpty())
	{
		return _T("");
	}

	// TODO:
	tstring strTmp = (LPCTSTR)fullPath;
	tstring lasTCHAR = strTmp.substr(strTmp.length() - 1, 1);
	if(lasTCHAR != _T("\\") && lasTCHAR != _T("/"))
	{
		strTmp += sep;
	}

	return strTmp.c_str();
}

//--------------------------------------------------------------------------------------

bool File::DeleteFile(const CString& fiePath)
{
	return _tremove((LPCTSTR)fiePath) == 0;
}

//--------------------------------------------------------------------------------------

CString File::GetDirFromFullPath(const CString& fullPath)
{
	TCHAR strDir[256];
	TCHAR strPath[256];
	TCHAR strName[256];
	TCHAR strExt[256];
	_tsplitpath_s((LPCTSTR)fullPath, strDir, strPath, strName, strExt);

	CString strDirPath = strDir;
	strDirPath += strPath;
	strDirPath = NormalizePath(strDirPath);
	return strDirPath;
}

void File::RemoveReadonly(const CString& fileName)
{
	DWORD attr = ::GetFileAttributes((LPCTSTR)fileName);
	attr &= ~FILE_ATTRIBUTE_READONLY;
	::SetFileAttributes((LPCTSTR)fileName, attr);
}

void File::CreateTextFile(const CString& file)
{
	if(!File::IsDirExist(file))
	{
		CStdioFile file(file, CFile::modeCreate | CFile::typeText | CFile::modeWrite);
		file.Close();
	}
}


CString File::GetFilePathFromFullPath(const CString& fullPath)
{
	TCHAR driveName[MAX_PATH];
	TCHAR dirName[MAX_PATH];
	TCHAR fileName[MAX_PATH];
	TCHAR fileExt[MAX_PATH];
	_tsplitpath_s((LPCTSTR)fullPath, driveName, MAX_PATH,
		dirName, MAX_PATH, fileName, MAX_PATH, fileExt, MAX_PATH);
	CString fileNameEx = CString(driveName) + CString(dirName);
	return fileNameEx;
}

CString File::GetVerMD5FileName(const CString& srcFileName, const CString& md5Code, const CString& /*verName*/)
{
	CString targFileName = File::GetFilePathFromFullPath(srcFileName)
		//+ verName + _T("_") + md5Code;
		+ md5Code;
	return targFileName;
}