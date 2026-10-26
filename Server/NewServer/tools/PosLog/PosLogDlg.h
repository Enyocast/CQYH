
// PosLogDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "common_log.h"

// CPosLogDlg dialog
class CPosLogDlg : public CDialogEx
{
// Construction
public:
	CPosLogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_POSLOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	static CPosLogDlg& GetInstance(void) { return m_sInstance;  }

	static bool ProcessField(int field_idx, int line_idx, const char* field_value, line_data* ld, log_context* context);
	static bool ProcessLine(int line_idx, const line_data* ld, log_context* context);
	static bool ProcessOver(log_context* context);

	INT32 InsertPos(const line_data* ld);


	// Implementation
protected:
	HICON m_hIcon;

	static CPosLogDlg m_sInstance;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_SceneList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_DrawCanvas;
	BOOL m_bLoadFinished;

	struct Pos
	{
		int x;
		int y;
	};

	typedef std::list<Pos> TPosList;
	typedef std::map<INT32, TPosList> TPosMap;

	TPosMap m_PosMap;
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_PicSize;
	afx_msg void OnCbnSelchangeCombo1();
	CButton m_SaveAsBmp;

	int m_nBmpSize;
	int m_nKey;
	afx_msg void OnBnClickedSaveBmp();
};
