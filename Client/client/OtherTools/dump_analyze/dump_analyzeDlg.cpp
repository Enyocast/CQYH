
// dump_analyzeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "dump_analyze.h"
#include "dump_analyzeDlg.h"
#include "afxdialogex.h"
#include "FMiniDump.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern const TCHAR* DAFormat(const TCHAR* fmt, ...)
{
	static TCHAR szBuff[4096] = {0};
	va_list ap;
	va_start(ap,fmt);
	_vstprintf_s(szBuff, fmt, ap);
	va_end(ap);
	return szBuff;
}

// CDumpAnalyzeDlg 对话框
CDumpAnalyzeDlg::CDumpAnalyzeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDumpAnalyzeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDumpAnalyzeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, m_cbLog);
	DDX_Control(pDX, IDC_EDIT_INFO, m_DumpInfo);
	DDX_Control(pDX, IDC_LIST_MOD, m_ModLst);
	DDX_Control(pDX, IDC_LIST_THREAD, m_ThreadLst);
	DDX_Control(pDX, IDC_LIST_CALL, m_ThreadCall);
}

void CDumpAnalyzeDlg::OpenDump(const TCHAR* file)
{
	ClearUI();
	theDump.Close();
	if (!theDump.Open(file, 0, theManWnd(), true))
	{
		AfxMessageBox("分析失败");
		return;
	}

	DUMP_INFO& DI = theDump.nDump;

	const TCHAR* pstr = DAFormat
		(
		"程序信息：\r\n"
		"  -VER：%d.%d.%d.%d\r\n"
		"对方系统：\r\n"
		"  -VER: %d-%d\r\n"
		"  -Build: %d\r\n"
		"  -%s\r\n"
		"崩溃信息：\r\n"
		"  -Code: %.08X\r\n"
		"  -Address: 0x%.08X\r\n"
        "  -Thread: %.08X"
		,
		(int)(DI.m_verExe.dwFileVersionMS>>16),
		(int)(DI.m_verExe.dwFileVersionMS&0xffff),
		(int)(DI.m_verExe.dwFileVersionLS>>16),
		(int)(DI.m_verExe.dwFileVersionLS&0xffff),
		DI.m_ulVerMajor,
		DI.m_ulVerMinor,
		DI.m_ulVerBuild,
		DI.m_sCSDVer,
		DI.m_uExceptionCode,
		(DWORD)DI.m_uExceptionAddress,
		DI.m_uExceptionThreadId
		);
	m_DumpInfo.SetWindowText(pstr);

	for (size_t i = 0; i < DI.m_Modules.size(); ++i)
	{
		pstr = DAFormat
			(
			"%s",
			DI.m_Modules[i].m_sModuleName
			);
		m_ModLst.AddString(pstr);
	}

	for (size_t i = 0; i < DI.m_Threads.size(); ++i)
	{
		pstr = DAFormat
			(
			"%.08X%s",
			DI.m_Threads[i].m_dwThreadId,
			DI.m_Threads[i].m_dwThreadId == DI.m_uExceptionThreadId ? "(Exception)" : "");
		m_ThreadLst.AddString(pstr);
	}
}

void CDumpAnalyzeDlg::ClearUI()
{
	ClearLog();
	m_DumpInfo.Clear();
	m_ModLst.ResetContent();
	m_ThreadLst.ResetContent();
	m_ThreadCall.ResetContent();
}

void CDumpAnalyzeDlg::OnLog(const TCHAR* str)
{
	m_cbLog.SetAnchorIndex(m_cbLog.AddString(DAFormat(">> %s", str)));
}

BEGIN_MESSAGE_MAP(CDumpAnalyzeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST_THREAD, &CDumpAnalyzeDlg::OnLbnSelchangeListThread)
END_MESSAGE_MAP()

// CDumpAnalyzeDlg 消息处理程序
BOOL CDumpAnalyzeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CDumpAnalyzeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDumpAnalyzeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDumpAnalyzeDlg::OnLbnSelchangeListThread()
{
	m_ThreadCall.ResetContent();

	int idx = m_ThreadLst.GetCurSel();
	if (idx == LB_ERR)
		return;

	DUMP_INFO& DI = theDump.nDump;
	if (idx < 0 || idx > (int)DI.m_Threads.size())
		return;

	DUMP_THREAD& DT = DI.m_Threads[idx];

	theDump.StackWalk(DT.m_dwThreadId);

	const TCHAR* pstr = 0;
	for (size_t i = 0; i < DT.m_StackTrace.size(); ++i)
	{
		pstr = DAFormat
			(
			"%s(%d): %s(%s) : 0x%.08X",
			DT.m_StackTrace[i].m_sSrcFileName.IsEmpty() ? "No Src Files" : DT.m_StackTrace[i].m_sSrcFileName,
			DT.m_StackTrace[i].m_nSrcLineNumber,
			DT.m_StackTrace[i].m_nModuleRowID != -1 ? DI.m_Modules[DT.m_StackTrace[i].m_nModuleRowID].m_sModuleName : "No Find Module",
			DT.m_StackTrace[i].m_sSymbolName.IsEmpty() ? "No Find Symbols" : DT.m_StackTrace[i].m_sSymbolName,
			(DWORD)DT.m_StackTrace[i].m_dwAddrPCOffset
			);
		m_ThreadCall.AddString(pstr);
	}
}
