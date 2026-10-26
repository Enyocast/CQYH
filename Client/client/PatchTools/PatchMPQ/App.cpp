// *************************************************************************************
// 
// 
// 	All Rights Reserved 
// 
// 	Create Date		:		2007-1-14
// *************************************************************************************

#include "StdAfx.h"
#include "App.h"
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

using namespace ShowGame_Core;

CString App::_appPath;

static App g_AppInst;

App::App()
{
	TCHAR buf[MAX_PATH];
	memset(buf, 0, sizeof(MAX_PATH));

	GetModuleFileName(NULL, buf, MAX_PATH - 1);
	::PathRemoveFileSpec(buf);
	CString strT(buf);
	strT += _T("\\");
	_appPath = strT;
}

App::~App(void)
{
}

CString	App::GetAppPath()
{
	return _appPath;
}
