/*====================================================================
	Created Date  :		2005-10-24
	
	Specification :  
====================================================================*/
#pragma once


class CheckServerDlg : public CDialog
{
	DECLARE_DYNAMIC(CheckServerDlg)

public:
	CheckServerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CheckServerDlg();

	enum { IDD = IDD_DIALOG_CONNECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
