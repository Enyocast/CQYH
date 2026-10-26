
#pragma once

#include <vector>
#include <tlhelp32.h>

struct SVersionInfo
{
	SVersionInfo()
	{
		_isMatched			 = FALSE;
		_relatedPathName	 = _T("");
		_contentType		 = _T("Unknow");
		_originLen			 = 0;
		_timeModify			 = 0;
		_codeMD5			 = _T("#####");
		_isMatched			 = FALSE;
		_costWeight			 = 0;
		_codeMD5OnServerFile = _T("");
	}

	CString			_fullPathName;
	CString			_relatedPathName;	// Data\DouDiZhu\Sound\PASSŮ.wav, ddzcardtablelib.dll
	CString			_contentType;				// "File" / "Dir"
	unsigned int	_originLen;			// 0 : for no compress, > 0 for existing compressed file
	time_t			_timeModify;			// Modify time, Only used in Version1(.vi)
	CString			_codeMD5;
	CString			_codeMD5OnServerFile;
	BOOL			_isMatched;
	unsigned int	_costWeight;
};
typedef std::vector<SVersionInfo>	VersionInfoes;
typedef std::vector<SVersionInfo*>	VersionInfoePtrs;

enum EPatchOperation
{
	EPO_None = 0,
	EPO_Patch = 1,
	EPO_Remove = 2,
	EPO_Install = 3,
};

struct SLocalVersionInfo : public SVersionInfo
{
	SLocalVersionInfo()
	{
		_iOperation = EPO_None;
	}

	EPatchOperation _iOperation;		// 0 : Do not touch
										// 1 : Patch
										// 2 : Remove( Only for file )

};
typedef std::vector<SLocalVersionInfo>	LocalVersionInfoes;

struct SFilePatch
{
	SFilePatch()
	{
		Clear();
	}

	BOOL					_bShouldUpdateViFile;
	BOOL					_bCheckServerViSuccess;
	CString					_strViFileName;				// client_bin.vi2
	CString					_strLocalViFilePathName;	// C:\client_bin\client_bin.vi2
	CString					_strServerSubDir;			// client_bin/
	CString					_strServerFileSuffix;		// client_bin/client_bin.vi2, client_bin/MMOGame.exe
	LocalVersionInfoes		_vectorLocalViInfoes;
	VersionInfoes			_vectorServerViInfoes;
	int						_iPatchCount;

	void Clear()
	{
		_bShouldUpdateViFile	= FALSE;
		_bCheckServerViSuccess	= TRUE;
		_iPatchCount			= 0;

		_strViFileName = _T("");
		_strLocalViFilePathName = _T("");
		_strServerSubDir = _T("");
		_strServerFileSuffix = _T("");
		_vectorLocalViInfoes.clear();
		_vectorServerViInfoes.clear();
	}
};

