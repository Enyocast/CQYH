
// dump_analyzeDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CDumpAnalyzeDlg 对话框
class CDumpAnalyzeDlg : public CDialogEx, public DUMP_LOG
{
// 构造
public:
	CDumpAnalyzeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DUMP_ANALYZE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	virtual void OnLog(const TCHAR* str);

public:
	void OpenDump(const TCHAR* file);
	void ClearUI();
	void ClearLog(){ m_cbLog.ResetContent(); }

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_cbLog;
	CEdit m_DumpInfo;
	CListBox m_ModLst;
	CListBox m_ThreadLst;
	CListBox m_ThreadCall;
	afx_msg void OnLbnSelchangeListThread();
};
