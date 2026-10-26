// AwardItemTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AwardItemTest.h"
#include "AwardItemTestDlg.h"
#include "sotsapi.h"
#include "awardinfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern FunRmInitialize          pRmInitialize        ;
extern FunRmTerminate           pRmTerminate         ;
extern FunRmAsynCall            pRmAsynCall          ;
extern FunRmGetSotsUniqueId     pRmGetSotsUniqueId   ;

extern SOTSCLIENTINFO cltinfo;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAwardItemTestDlg dialog

CAwardItemTestDlg::CAwardItemTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAwardItemTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAwardItemTestDlg)
	m_nAwardGrade = 0;
	m_strRoleName = _T("");
	m_nUserGrade = 0;
	m_strUserId = _T("");
	m_strProfession = _T("");
	m_strBatchId = _T("");
	m_strAwardNum = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAwardItemTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAwardItemTestDlg)
	DDX_Control(pDX, IDC_LIST_RESULT, m_lstResult);
	DDX_Text(pDX, IDC_EDIT_AWARD_GRADE, m_nAwardGrade);
	DDV_MinMaxUInt(pDX, m_nAwardGrade, 0, 999999);
	DDX_Text(pDX, IDC_EDIT_ROLE_NAME, m_strRoleName);
	DDX_Text(pDX, IDC_EDIT_USER_GRADE, m_nUserGrade);
	DDV_MinMaxUInt(pDX, m_nUserGrade, 0, 99999);
	DDX_Text(pDX, IDC_EDIT_USER_ID, m_strUserId);
	DDX_Text(pDX, IDC_EDIT_PROFESSION, m_strProfession);
	DDX_Text(pDX, IDC_EDIT_BATCHID, m_strBatchId);
	DDX_Text(pDX, IDC_EDIT_AWARDNUM, m_strAwardNum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAwardItemTestDlg, CDialog)
	//{{AFX_MSG_MAP(CAwardItemTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAwardItemTestDlg message handlers

BOOL CAwardItemTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CButton *pRadioButton = (CButton *)GetDlgItem(IDC_RADIO_GOLDAWARD);
	m_nAwardType = 3;
	pRadioButton->SetCheck(TRUE);
	m_lstResult.SetHorizontalExtent(1000);
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAwardItemTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAwardItemTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAwardItemTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAwardItemTestDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	//
	// Don't change the following code
	//
	char buf[2048];
	GoldAwardAuthenInfoReqDef *p = (GoldAwardAuthenInfoReqDef *)buf;
	MsgHeadDef *pHead = &p->msgHead;
	GoldAwardAuthenReqDef *pMsg = &p->msgBody;
	pHead->msgType = htonl(GOLDAWARDAUTHENREQ);					
	pHead->msgLen = htonl(sizeof(GoldAwardAuthenInfoReqDef));
	pHead->callTime = htonl(time(NULL));
	pHead->version = htonl(MSGVERSION);

	pRmGetSotsUniqueId(pHead->msgId, 33);		// Get unique string
	pRmGetSotsUniqueId(pMsg->orderId, 33);		// Get another unique string

	pMsg->gameId = htonl(cltinfo.gameId);		// Use default value
	pMsg->groupId = htonl(cltinfo.groupId);		// Use default value
	pMsg->areaId = htonl(cltinfo.areaId);		// Use default value
	pMsg->hostId = htonl(cltinfo.hostId);		// Use default value

	pMsg->awardType = htonl(1);					// awardType=3 means you need set awardNum
	pMsg->uidType = htonl(2);					// User account type. 2-Number account
	
	//
	// You must set these field
	//
	strcpy(pMsg->awardNum, (LPCTSTR)m_strAwardNum);	// Set coupon number
	
	pMsg->userGrade = htonl(m_nUserGrade);			// Set user account level
	pMsg->awardGrade = htonl(m_nAwardGrade);		// Which level item do you want
	strcpy(pMsg->userId, (LPCTSTR)m_strUserId);		// Set user account
	strcpy(pMsg->roleName, (LPCTSTR)m_strRoleName);	// Set role name

	CTime tm = CTime::GetCurrentTime();
	CString str = tm.Format("%Y-%m-%d %H:%M:%S");
	strcpy(pMsg->authenTime, (LPCSTR)str);			// Set current time

	strcpy(pMsg->roleProperty, (LPCTSTR)m_strProfession);  // Set role property like "male#warrior"
	strcpy(pMsg->batchId, (LPCTSTR)m_strBatchId);	// Set batch id
	strcpy(pMsg->endpointIp, "1.2.3.4");			// Set player's IP address

	int len = sizeof(GoldAwardAuthenInfoReqDef);
	ULONG	hRpc = pRmAsynCall("SVCAWARD", buf, len, 0);
}

void CAwardItemTestDlg::Append(const char *pszResult)
{
	m_lstResult.AddString(pszResult);
}
