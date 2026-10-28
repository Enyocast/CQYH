
// encryptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "encrypt.h"
#include "encryptDlg.h"
#include "afxdialogex.h"
#include "base.h"
#include "zlib.h"

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


// CencryptDlg dialog



CencryptDlg::CencryptDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CencryptDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CencryptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CencryptDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON2, &CencryptDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON1, &CencryptDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CencryptDlg message handlers

BOOL CencryptDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CencryptDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CencryptDlg::OnPaint()
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
HCURSOR CencryptDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



bool GetSourceFileName(const char *pcszInFile, char *pOutName)
{
    if (pcszInFile == 0 || pOutName == 0)
        return false;

    __int32 i = 0;
    __int32 l = 0;
    while (pcszInFile[i] != '\0')
    {
        if (pcszInFile[i] == '\\' || pcszInFile[i] == '/')
            l = i;
        ++i;
    }

    i = l + 1;
    __int32 j = 0;
    while (pcszInFile[i] != '\0' && pcszInFile[i] != '.')
    {
        pOutName[j++] = pcszInFile[i++];
    }

    pOutName[j] = '\0';

    return true;
}

void CencryptDlg::OnBnClickedButton2()
{
    // TODO: Add your control notification handler code here
    CString     csFile;
    char        szFile[512] = { 0 };
    char        szSourceFile[512] = { 0 };
    FILE        *pf = 0;

    __int32     csFileLength = 0;
    __int32     szFileLength = 512;

    GetDlgItemText(IDC_MFCEDITBROWSE1, csFile);
    csFileLength = csFile.GetLength();

    WideCharToMultiByte(CP_ACP, 0, csFile, csFileLength, szFile, szFileLength, 0, 0);

    fopen_s(&pf, szFile, "rb");
    if (pf == NULL)
    {
        return;
    }

    const __int32  INPUT_LENGTH = 1024 * 1024;
    const __int32  OUTPUT_LENGTH = INPUT_LENGTH + 8;

    char *pOutputStr = new char[OUTPUT_LENGTH];
    char *pInputStr = new char[INPUT_LENGTH];
    __int32 nLength = 0;
    __int32 nOLength = OUTPUT_LENGTH;

    fseek(pf, 0, SEEK_END);
    nLength = ftell(pf);
    fseek(pf, 0, SEEK_SET);
    fread(pInputStr, 1, nLength, pf);
    fclose(pf);
    pf = NULL;

    bool bRet = Decrypt(nLength, pInputStr, nOLength, pOutputStr);
    if (bRet == false)
    {
        return;
    }

    //GetSourceFileName(szFile, szSourceFile);

    fopen_s(&pf, szFile, "wb");
    if (pf == NULL)
        return;

    fwrite(pOutputStr, 1, nOLength, pf);
    fclose(pf);
    pf = NULL;

    delete[] pInputStr;
    delete[] pOutputStr;

    CString tmp("解密成功");
    MessageBox(tmp);
}


void CencryptDlg::OnBnClickedButton1()
{
    // TODO: Add your control notification handler code here
    CString     csFile;
    char        szFile[512] = { 0 };
    char        szSourceFile[512] = { 0 };
    char        szFinalFile[512] = { 0 };
    char        cBuffer[512] = { 0 };
    FILE        *pf = 0;

    __int32     csFileLength = 0;
    __int32     szFileLength = 512;

    GetDlgItemText(IDC_MFCEDITBROWSE1, csFile);
    csFileLength = csFile.GetLength();

    WideCharToMultiByte(CP_ACP, 0, csFile, csFileLength, szFile, szFileLength, 0, 0);

    fopen_s(&pf, szFile, "rb");
    if (pf == NULL)
    {
        return;
    }

    const __int32  INPUT_LENGTH = 1024 * 1024;
    const __int32  OUTPUT_LENGTH = INPUT_LENGTH + 8;

    char *pOutputStr = new char[OUTPUT_LENGTH];
    char *pInputStr = new char[INPUT_LENGTH];
    __int32 nLength = 0;
    __int32 nOLength = OUTPUT_LENGTH;

    fseek(pf, 0, SEEK_END);
    nLength = ftell(pf);
    fseek(pf, 0, SEEK_SET);
    fread(pInputStr, 1, nLength, pf);
    fclose(pf);
    pf = NULL;

    bool bRet = Encrypt(nLength, pInputStr, nOLength, pOutputStr);
    if (bRet == false)
    {
        return;
    }

    GetSourceFileName(szFile, szSourceFile);

    unsigned __int32 dwcrc = crc32(0, (Bytef*)szSourceFile, strlen(szSourceFile));
    sprintf_s(szFinalFile, 512, "%u", dwcrc);

    fopen_s(&pf, szFinalFile, "wb");
    if (pf == NULL)
        return;

    fwrite(pOutputStr, 1, nOLength, pf);
    fclose(pf);
    pf = NULL;

    delete[] pInputStr;
    delete[] pOutputStr;

    CString tmp("加密成功");
    MessageBox(tmp);
}
