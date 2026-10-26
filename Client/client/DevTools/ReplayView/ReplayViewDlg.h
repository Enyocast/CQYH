
// ReplayViewDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CReplayViewDlg 对话框
class CReplayViewDlg : public CDialogEx
{
    DECLARE_MESSAGE_MAP()

public:
	CReplayViewDlg(CWnd* pParent = NULL);	// 标准构造函数

	enum { IDD = IDD_REPLAYVIEW_DIALOG };

	HICON m_hIcon;
    CRichEditCtrl m_RichBox;
    net_message_object m_NetMessage;
    CString m_LstReplayFile;

    void ReplayFile(const TCHAR* file);
    void ReBoxSize();

	virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnDropFiles(HDROP hDropInfo);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBnClickedCheckMmove();
    afx_msg void OnBnClickedCheckAxis();
};
