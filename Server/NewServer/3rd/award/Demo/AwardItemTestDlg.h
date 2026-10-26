// AwardItemTestDlg.h : header file
//

#if !defined(AFX_AWARDITEMTESTDLG_H__6AEC88E5_C187_4517_A3AC_FB3B8FE40047__INCLUDED_)
#define AFX_AWARDITEMTESTDLG_H__6AEC88E5_C187_4517_A3AC_FB3B8FE40047__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "sotsapi.h"

typedef INT32 (*FunRmInitialize)(const char *configFileName,pSotsMsgHandler handler);
typedef INT32 (*FunRmTerminate)();
typedef ULONG (*FunRmAsynCall)(const char *serviceName, 
						const void* data, INT32 dataLen, UINT32 flags);
typedef INT32 (*FunRmGetSotsUniqueId)(char *orderId,INT32 len);

/////////////////////////////////////////////////////////////////////////////
// CAwardItemTestDlg dialog

class CAwardItemTestDlg : public CDialog
{
// Construction
public:
	int m_nAwardType;
	void Append(const char *pszResult);
	CAwardItemTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAwardItemTestDlg)
	enum { IDD = IDD_AWARDITEMTEST_DIALOG };
	CListBox	m_lstResult;
	UINT	m_nAwardGrade;
	CString	m_strRoleName;
	UINT	m_nUserGrade;
	CString	m_strUserId;
	CString	m_strProfession;
	CString	m_strBatchId;
	CString	m_strAwardNum;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAwardItemTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAwardItemTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AWARDITEMTESTDLG_H__6AEC88E5_C187_4517_A3AC_FB3B8FE40047__INCLUDED_)
