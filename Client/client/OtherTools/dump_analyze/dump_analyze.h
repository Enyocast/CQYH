
// dump_analyze.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CDumpAnalyzeApp:
// 有关此类的实现，请参阅 dump_analyze.cpp
//

class CDumpAnalyzeApp : public CWinApp
{
public:
	CDumpAnalyzeApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOpen();
	afx_msg void OnAnalyze();
	afx_msg void OnReport();

	// .first 目录 / .second 文件列表
	typedef std::vector< std::string > _StrVector;
	typedef std::vector< std::pair< std::string, _StrVector > > _AddVector;
	void __ClearRepeat(const TCHAR* path, _AddVector& vadd, _StrVector& verinfo);
};

extern CDumpAnalyzeApp theApp;