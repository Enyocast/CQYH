/*====================================================================
	Created Date  :		2005-8-25
	
	Specification :  
====================================================================*/
#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h”
#endif

#include "resource.h"		// 主符号

class CFilePatchApp : public CWinApp
{
public:
	CFilePatchApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CFilePatchApp theApp;
