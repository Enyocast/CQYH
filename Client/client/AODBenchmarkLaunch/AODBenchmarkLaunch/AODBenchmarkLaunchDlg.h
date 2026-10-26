
// AODBenchmarkLaunchDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CAODBenchmarkLaunchDlg dialog
class CAODBenchmarkLaunchDlg : public CDialogEx
{
// Construction
public:
	CAODBenchmarkLaunchDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_AODBENCHMARKLAUNCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox _resComboList;
	CString _selectedResolution;
	BOOL _enablePhysX;
	BOOL _enableAA;
	BOOL _enableTess;
	afx_msg void OnBnClickedOk();
	CString _selectedMap;
	CComboBox _selMapComboList;
	CButton _launch64Bit;
	BOOL _use64Bit;
	CButton _btnLoop;
	BOOL _loopPlay;
	CButton _btnQuitOnComplete;
	BOOL _quitOnComplete;
	CButton _btnEnablePhysX;
	int     _playType;
	afx_msg void OnBnClickedCheckLoop();
	afx_msg void OnBnClickedCheckQuitOnComplete();
	afx_msg void OnChangedSel(UINT nID);
};
