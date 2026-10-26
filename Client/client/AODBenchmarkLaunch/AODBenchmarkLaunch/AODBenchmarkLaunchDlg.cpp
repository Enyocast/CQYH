
// AODBenchmarkLaunchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AODBenchmarkLaunch.h"
#include "AODBenchmarkLaunchDlg.h"
#include "afxdialogex.h"
#include <map>
#include <fstream>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAODBenchmarkLaunchDlg dialog




CAODBenchmarkLaunchDlg::CAODBenchmarkLaunchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAODBenchmarkLaunchDlg::IDD, pParent)
	, _selectedResolution(_T(""))
	, _enablePhysX(TRUE)
	, _enableAA(TRUE)
	, _enableTess(TRUE)
	, _selectedMap(_T(""))
	, _use64Bit(FALSE)
	, _loopPlay(TRUE)
	, _quitOnComplete(FALSE)
	, _playType(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAODBenchmarkLaunchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, _resComboList);
	DDX_CBString(pDX, IDC_COMBO_RESOLUTION, _selectedResolution);
	DDX_Check(pDX, IDC_CHECK_PHYSX, _enablePhysX);
	DDX_Check(pDX, IDC_CHECK_AA, _enableAA);
	DDX_Check(pDX, IDC_CHECK_TESS, _enableTess);
	DDX_CBString(pDX, IDC_COMBO_MAP, _selectedMap);
	DDX_Control(pDX, IDC_COMBO_MAP, _selMapComboList);
	DDX_Control(pDX, IDC_CHECK_64, _launch64Bit);
	DDX_Check(pDX, IDC_CHECK_64, _use64Bit);
	//DDX_Control(pDX, IDC_CHECK_LOOP, _btnLoop);
	//DDX_Check(pDX, IDC_CHECK_LOOP, _loopPlay);
	//DDX_Control(pDX, IDC_CHECK_QUIT_ON_COMPLETE, _btnQuitOnComplete);
	//DDX_Check(pDX, IDC_CHECK_QUIT_ON_COMPLETE, _quitOnComplete);
	DDX_Control(pDX, IDC_CHECK_PHYSX, _btnEnablePhysX);
	DDX_Radio(pDX, IDC_RADIO_PLAYCTRL_LOOP, _playType);
}

BEGIN_MESSAGE_MAP(CAODBenchmarkLaunchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAODBenchmarkLaunchDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_LOOP, &CAODBenchmarkLaunchDlg::OnBnClickedCheckLoop)
	ON_BN_CLICKED(IDC_CHECK_QUIT_ON_COMPLETE, &CAODBenchmarkLaunchDlg::OnBnClickedCheckQuitOnComplete)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_PLAYCTRL_LOOP, IDC_RADIO_PLAYCTRL_QUITONCOMPLETE, OnChangedSel)
END_MESSAGE_MAP()


// CAODBenchmarkLaunchDlg message handlers

BOOL CAODBenchmarkLaunchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//((CButton*)GetDlgItem(IDC_CHECK_PHYSX))->SetCheck(0);
	//GetDlgItem(IDC_CHECK_PHYSX)->EnableWindow(FALSE);
	//_btnEnablePhysX.EnableWindow(FALSE);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	DEVMODE DisplayMode;
	UINT ModeIndex = 0;
	CString dataString;

	struct FDisplayResolution
	{
		INT Width;
		INT Height;
	};

	typedef std::map<INT, FDisplayResolution> ResolutionMap;
	ResolutionMap tmpResMap;

	INT idx = 0;
	INT selIdx = 0;
	while(EnumDisplaySettings(NULL, ModeIndex++, &DisplayMode))
	{
		if(DisplayMode.dmPelsWidth >= 1280)
		{
			if(tmpResMap.find(DisplayMode.dmPelsWidth) == tmpResMap.end())
			{
				FDisplayResolution res;
				res.Width = DisplayMode.dmPelsWidth;
				res.Height = DisplayMode.dmPelsHeight;
				tmpResMap.insert(std::make_pair(res.Width, res));			

				dataString.Format(TEXT("%dx%d"), res.Width, res.Height);
				_resComboList.AddString(dataString);

				++idx;
			}
		}
	}

	_resComboList.SetCurSel(0);

	std::wifstream mapFile;
	mapFile.open(TEXT("benchmarkmap.txt"));
	if(mapFile.good())
	{		
		wchar_t buff[MAX_PATH];

		while(!mapFile.eof())
		{
			mapFile.getline(buff, MAX_PATH);
			_selMapComboList.AddString(buff);
		}
	}

	_selMapComboList.SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAODBenchmarkLaunchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAODBenchmarkLaunchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAODBenchmarkLaunchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAODBenchmarkLaunchDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CString str;
	str.Format(TEXT("%s -physx=%d -aa=%d -tess=%d -dx11 -MMOBENCHMARK"),
		_selectedMap.GetString(),  _enablePhysX, _enableAA, _enableTess);

	if(_quitOnComplete)
	{
		str += TEXT(" -QUITMMOBENCHMARKONCOMPLETE");
	}
	else if(_loopPlay)
	{
		str += TEXT(" -LOOPMMOBENCHMARK");
	}

	CString exeFile = _use64Bit ? TEXT("Win64\\MMOGame.exe") : TEXT("Win32\\MMOGame.exe");
	::ShellExecute(NULL, TEXT("open"), exeFile.GetString(), str.GetString(), TEXT("."), SW_SHOWNORMAL);

	CDialogEx::OnOK();

}


void CAODBenchmarkLaunchDlg::OnBnClickedCheckLoop()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	_btnQuitOnComplete.EnableWindow(!_loopPlay);
}


void CAODBenchmarkLaunchDlg::OnBnClickedCheckQuitOnComplete()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	_btnLoop.EnableWindow(!_quitOnComplete);
}

void CAODBenchmarkLaunchDlg::OnChangedSel(UINT nID)
{
	UpdateData(TRUE);

	_playType = nID;
	if(_playType == IDC_RADIO_PLAYCTRL_LOOP)
	{
		_loopPlay = TRUE;
		_quitOnComplete = FALSE;
	}
	else if(_playType == IDC_RADIO_PLAYCTRL_QUITONCOMPLETE)
	{
		_loopPlay = FALSE;
		_quitOnComplete = TRUE;
	}
}