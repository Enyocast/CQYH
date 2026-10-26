// *************************************************************************************
// 
// 
// 	All Rights Reserved 
// 
// 	Create Date		:		2006-8-28
// *************************************************************************************

#pragma once
#include <vector>
#include <string>
#include <sstream>

#ifndef MAX_PATH
#	define MAX_PATH 260
#endif

#define SAFE
#define UNSAFE
#define Trace
#define Tracef


#ifdef  UNICODE
#	define tchar	wchar_t
#	define tstring std::wstring

#	define tfstream std::wfstream
#	define tifstream std::wifstream
#	define tofstream std::wofstream
#   define tostream std::wostream

#	define tostringstream std::wostringstream

#	define tcout	std::wcout

#else
#	define tchar	char
#	define tstring std::string

#	define tfstream std::fstream
#	define tifstream std::ifstream
#	define tofstream std::ofstream
#   define tostream std::ostream

#	define tostringstream std::ostringstream

#	define tcout	std::cout

#endif

#define tendl _T("\n")

	class TStringList : public std::vector<tstring>
	{
	public:

		virtual ~TStringList(){}
	};

	TStringList Parse2StringList(const tstring& str, const tstring& sepStr);

	class File
	{
	public:

		static bool IsFileExist(const CString& filePath);
		static bool	IsDirExist(const CString& dirPath);

		static CString GetFileNameFromFullPath(const CString& fullPath);
		static CString GetFilePathFromFullPath(const CString& fullPath);
		static CString GetFileWithoutExtNameFromFullPath(const CString& fullPath);
		static CString GetFileExtFromFullPath(const CString& fullPath);
		

		static bool		MakeDir(const CString& dirName);
		static bool		DeleteFile(const CString& fiePath);

		static CString		GetDirFromFullPath(const CString& fullPath);		
		static CString		NormalizePath(const CString& fullPath, const CString& sep = _T("/"));

		static void RemoveReadonly(const CString& fileName);

		static void CreateTextFile(const CString& fileName);

		static CString GetVerMD5FileName(const CString& srcFileName, const CString& md5Code, const CString& verName);
	};

