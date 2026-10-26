/*====================================================================
	Created Date  :		2005-10-24
	
	Specification :  
====================================================================*/

#include "stdafx.h"
#include "PatchMPQ.h"
#include "CheckServerDlg.h"


// CheckServerDlg dialog

IMPLEMENT_DYNAMIC(CheckServerDlg, CDialog)
CheckServerDlg::CheckServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CheckServerDlg::IDD, pParent)
{
}

CheckServerDlg::~CheckServerDlg()
{
}

void CheckServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CheckServerDlg, CDialog)
END_MESSAGE_MAP()


// CheckServerDlg message handlers
