// *************************************************************************************
// 
// 
// 	All Rights Reserved 
// 
// 	Create Date		:		2006-7-11
// *************************************************************************************

#include "StdAfx.h"
#include "Configer.h"
#include "File.h"

using namespace ShowGame_Core;

Configer::Configer(void)
{
}

Configer::~Configer(void)
{
// 	_fileName.Empty();
}

void	Configer::LoadFile(const CString& fileName)
{
	

	_fileName = fileName;
	if(!File::IsFileExist(fileName))
	{
		File::CreateTextFile(_fileName);
	}

	File::RemoveReadonly(_fileName);

	
}

//--------------------------------------------------------------------------------------

void	Configer::SaveFile(const CString& fileName)
{
	

	if(!fileName.IsEmpty())
	{
		File::RemoveReadonly(_fileName);
		_fileName = fileName;
	}

	
}

//--------------------------------------------------------------------------------------

int		Configer::GetIntValue(const CString& section, const CString& key, int defaultVal)
{
	

	CString str;
	GetStringValue(section, key, str);
	if(str.IsEmpty())
	{
		return defaultVal;
	}

	int val = 0;
	_stscanf_s((LPCTSTR)str, _T("%d"), &val);
	return val;

	//return (int)::GetPrivateProfileInt((LPCTSTR)section, (LPCTSTR)key, 0, (LPCTSTR)_fileName);

	
}

//--------------------------------------------------------------------------------------

void	Configer::SetIntValue(const CString& section, const CString& key, int val)
{
	

	CString str;
	str.Format(_T("%d"), val);
	SetStringValue(section, key, str);

	
}

//--------------------------------------------------------------------------------------

bool	Configer::GetBoolValue(const CString& section, const CString& key, bool defaultVal)
{
	

	CString str;
	GetStringValue(section, key, str);
	if(str.IsEmpty())
	{
		return defaultVal;
	}

	str.MakeLower();
	if(str == _T("1")
		|| str == _T("true")
		|| str == _T("on")
		|| str == _T("yes"))
	{
		return true;
	}

	return false;

	
}

//--------------------------------------------------------------------------------------

void	Configer::SetBoolValue(const CString& section, const CString& key, bool val)
{
	

	CString str;
	str.Format(_T("%d"), (int)val);
	SetStringValue(section, key, str);

	
}

//--------------------------------------------------------------------------------------

float	Configer::GetFloatValue(const CString& section, const CString& key, float defaultVal)
{
	

	CString str;
	GetStringValue(section, key, str);
	if(str.IsEmpty())
	{
		return defaultVal;
	}

	float val = 0.0f;
	_stscanf_s((LPCTSTR)str, _T("%f"), &val);
	return val;
	
}

//--------------------------------------------------------------------------------------

void	Configer::SetFloatValue(const CString& section, const CString& key, float val)
{
	

	CString str;
	str.Format(_T("%f"), val);
	SetStringValue(section, key, str);

	
}

//--------------------------------------------------------------------------------------

void Configer::GetStringValue(const CString& section, const CString& key, CString& val)
{
	

	TCHAR buf[256];
	DWORD len = ::GetPrivateProfileString((LPCTSTR)section, (LPCTSTR)key, _T(""), buf, 256, (LPCTSTR)_fileName);
	if (len == 0)
	{
		return;
	}

	val = buf;

	
}

CString Configer::GetStringValue(const CString& section, const CString& key, const CString& defaultStr)
{
	

	TCHAR buf[256];
	DWORD len = ::GetPrivateProfileString((LPCTSTR)section, (LPCTSTR)key, _T(""), buf, 256, (LPCTSTR)_fileName);
	if (len == 0)
	{
		return defaultStr;
	}

	return buf;

	
}

//--------------------------------------------------------------------------------------

void	Configer::SetStringValue(const CString& section, const CString& key, const CString& val)
{
	

	::WritePrivateProfileString((LPCTSTR)section, (LPCTSTR)key, (LPCTSTR)val, (LPCTSTR)_fileName);

	
}


//--------------------------------------------------------------------------------------

void	Configer::Reload()
{
	

	LoadFile(_fileName);

	
}

//--------------------------------------------------------------------------------------
