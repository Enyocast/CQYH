
// PosLogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PosLog.h"
#include "PosLogDlg.h"
#include "afxdialogex.h"
#include "bmp_file.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPosLogDlg dialog

CPosLogDlg CPosLogDlg::m_sInstance;

CPosLogDlg::CPosLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPosLogDlg::IDD, pParent)
{
//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPosLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_SceneList);
	DDX_Control(pDX, IDC_BUTTON3, m_DrawCanvas);
	DDX_Control(pDX, IDC_COMBO1, m_PicSize);
	DDX_Control(pDX, IDC_SAVE_BMP, m_SaveAsBmp);
}

BEGIN_MESSAGE_MAP(CPosLogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPosLogDlg::OnBnClickedButton1)
ON_NOTIFY(NM_CLICK, IDC_LIST2, &CPosLogDlg::OnNMClickList2)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CPosLogDlg::OnLvnItemchangedList2)
ON_CBN_SELCHANGE(IDC_COMBO1, &CPosLogDlg::OnCbnSelchangeCombo1)
ON_BN_CLICKED(IDC_SAVE_BMP, &CPosLogDlg::OnBnClickedSaveBmp)
END_MESSAGE_MAP()


// CPosLogDlg message handlers

BOOL CPosLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_bLoadFinished = FALSE;
	m_nBmpSize = 0;
	m_nKey = 0;

	DWORD dwStyle = m_SceneList.GetExtendedStyle();

	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;

	m_SceneList.SetExtendedStyle(dwStyle);

	m_SceneList.InsertColumn(0, L"Time", LVCFMT_LEFT, 50);
	m_SceneList.InsertColumn(1, L"SceneTempID", LVCFMT_LEFT, 100);
	m_SceneList.InsertColumn(2, L"Count", LVCFMT_LEFT, 50);

	m_PicSize.InsertString(0, L"512*512");
	m_PicSize.InsertString(1, L"1024*1024");

	m_PicSize.SetItemData(0, 512);
	m_PicSize.SetItemData(1, 1024);

	m_SaveAsBmp.EnableWindow(FALSE);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPosLogDlg::OnPaint()
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
HCURSOR CPosLogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPosLogDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, L"log");
	dlg.DoModal();

	m_PosMap.clear();

	m_SceneList.DeleteAllItems();

	CString path = dlg.GetPathName();

	log_context ctx;
	ctx._field_func = CPosLogDlg::ProcessField;
	ctx._line_func = CPosLogDlg::ProcessLine;
	ctx._over_func = CPosLogDlg::ProcessOver;

	char szFile[512] = { 0 };

	WideCharToMultiByte(CP_ACP, 0, path, path.GetLength(), szFile, 512, 0, 0);

	m_bLoadFinished = FALSE;

	load_file(szFile, &ctx);

	m_bLoadFinished = TRUE;

	SetDlgItemText(IDC_STATIC_FILE, path);

}

bool CPosLogDlg::ProcessField(int field_idx, int line_idx, const char* field_value, line_data* ld, log_context* context)
{
	if (field_idx == lfSceneTempID)
		ld->scene_temp_id = atoi(field_value);

	if (field_idx == lfTime)
	{
		int tm_fld_idx = 0;
		char val[8] = { 0 };
		int k = 0;

		for (int i = 0; i <= strlen(field_value); i++)
		{
			if (field_value[i] == ' ' || field_value[i] == '-' || field_value[i] == ':' || field_value[i] == 0)
			{
				ld->time_value[tm_fld_idx] = atoi(val);
				memset(val, 0, sizeof(val));
				tm_fld_idx++;
				k = 0;
			}
			else
				val[k++] = field_value[i];
		}
	}

	if (field_idx == lfX)
	{
		ld->x = _atoi64(field_value);
	}

	if (field_idx == lfY)
	{
		ld->y = _atoi64(field_value);
	}

	return true;
}

inline INT32 MakeKey(INT32 nHour, INT32 nMin, INT32 nSec, INT32 nTempID)
{
//	return (nHour << 24) + (nMin << 16) + (nSec << 8) + nTempID;
	return (nHour << 24) + nTempID;
}

inline void SplitKey(INT32 nKey, INT32& nHour, INT32& nMin, INT32& nSec, INT32& nTempID)
{
	nHour = ((nKey & 0xff000000) >> 24);
//	nMin = ((nKey & 0x00ff0000) >> 16);
//	nSec = ((nKey & 0x0000ff00) >> 16);
	nTempID = (nKey & 0x000000ff);
}

bool CPosLogDlg::ProcessLine(int line_idx, const line_data* ld, log_context* context)
{
	CPosLogDlg::GetInstance().InsertPos(ld);
	return true;
}

#define POINT_PER_CM			                (1LL << 10)									///< @line (unit: point)
#define MAX_SCENE_WIDTH			                (POINT_PER_CM * 128 * 2048)					///< @line (unit: point)
#define MAX_SCENE_WIDTH_CONV					(153600)

inline void ConvertCoordN2O(INT32& rnX, INT32& rnY)
{
	const INT64 k = 70710;
	const INT64 b = 100000;
	INT64 llX = rnX - MAX_SCENE_WIDTH / POINT_PER_CM / 2;
	INT64 llY = rnY;
	rnX = (INT32)((llX * k + llY * k) / b);
	rnY = (INT32)((-llX * k + llY * k) / b);
}

void CPosLogDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{

}

INT32 CPosLogDlg::InsertPos(const line_data* ld)
{
	INT32 x = ld->x / POINT_PER_CM;
	INT32 y = ld->y / POINT_PER_CM;

	if (ld->x > MAX_SCENE_WIDTH || ld->y > MAX_SCENE_WIDTH)
		return 0;

	ConvertCoordN2O(x, y);

	Pos pos;
	pos.x = x;
	pos.y = y;

	INT32 nKey = MakeKey(ld->time_value[tfHour], ld->time_value[tfMin], ld->time_value[tfSec], ld->scene_temp_id);

	TPosMap::iterator itr = m_PosMap.find(nKey);

	if (itr == m_PosMap.end())
	{
		TPosList NewList;
		NewList.push_back(pos);
		m_PosMap.insert(std::make_pair(nKey, NewList));
	}
	else
	{
		TPosList& list = itr->second;
		list.push_back(pos);
	}

	return nKey;
}

bool CPosLogDlg::ProcessOver(log_context* context)
{
	INT32 i = 0;
	CString strID;
	CString strTime;
	CString strCount;

	for (TPosMap::iterator itr = CPosLogDlg::GetInstance().m_PosMap.begin(); itr != CPosLogDlg::GetInstance().m_PosMap.end(); ++itr)
	{
		INT32 nHour = 0, nMin = 0, nSec = 0, nTempID = 0;
		SplitKey(itr->first, nHour, nMin, nSec, nTempID);

		strID.Format(L"%d", nTempID);
		strTime.Format(L"%d:00", nHour);
		strCount.Format(L"%d", itr->second.size());

		CPosLogDlg::GetInstance().m_SceneList.InsertItem(i, L"");
		CPosLogDlg::GetInstance().m_SceneList.SetItemText(i, 0, strTime);
		CPosLogDlg::GetInstance().m_SceneList.SetItemText(i, 1, strID);
		CPosLogDlg::GetInstance().m_SceneList.SetItemText(i, 2, strCount);
		CPosLogDlg::GetInstance().m_SceneList.SetItemData(i, itr->first);
	}

	return true;
}


void CPosLogDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMItemActivate = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if (!m_bLoadFinished)
		return;

	CClientDC dc(&m_DrawCanvas); // device context for painting
	COLORREF clr = RGB(0xff, 0, 0);

	m_DrawCanvas.RedrawWindow();

	RECT rc;
	m_DrawCanvas.GetClientRect(&rc);

//	INT32 nMaxSceneWidth = MAX_SCENE_WIDTH / POINT_PER_CM;
//	nMaxSceneWidth = (INT32)nMaxSceneWidth * 1.0f / 1.414f;

	m_nKey = m_SceneList.GetItemData(pNMItemActivate->iItem);

	{
		TPosMap::iterator itr = m_PosMap.find(m_nKey);
		if (itr == m_PosMap.end())
			return;

		TPosList& list = itr->second;

		for (TPosList::iterator listItr = list.begin(); listItr != list.end(); ++listItr)
		{
			INT32 y = (INT32)((INT64)listItr->x * rc.right / MAX_SCENE_WIDTH_CONV);
			INT32 x = (INT32)((INT64)listItr->y * rc.bottom / MAX_SCENE_WIDTH_CONV);

			dc.SetPixel(x, rc.bottom - y, clr);
		}
	}
}


void CPosLogDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	int sel = m_PicSize.GetCurSel();
	m_nBmpSize = m_PicSize.GetItemData(sel);

	m_SaveAsBmp.EnableWindow(TRUE);
}


void CPosLogDlg::OnBnClickedSaveBmp()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER, L"BMP file(*.bmp)|*.bmp|");

	if (dlg.DoModal() == IDCANCEL)
		return;

	CString strPath = dlg.GetPathName() + L".bmp";

	char szFile[MAX_PATH] = { 0 };
	WideCharToMultiByte(CP_ACP, 0, strPath, strPath.GetLength(), szFile, MAX_PATH, 0, 0);

	bmp_file_context ctx;

	bmp_prepare_file(szFile, &ctx);

	ctx._file_header._type = 0x4d42;
	ctx._file_header._off_bits = sizeof(bmp_file_header) + sizeof(bmp_info_header);

	ctx._info_header._size = sizeof(bmp_info_header);
	ctx._info_header._width = m_nBmpSize;
	ctx._info_header._height = m_nBmpSize;
	ctx._info_header._planes = 1;
	ctx._info_header._bit_count = 24;
	ctx._info_header._size_image = ctx._info_header._width * ctx._info_header._height * sizeof(bmp_rgb);

	ctx._file_header._file_size = sizeof(bmp_file_header) + sizeof(bmp_info_header) + ctx._info_header._size_image;

	bmp_write_header(&ctx);

	{
		ctx._rgb_data = new bmp_rgb[ctx._info_header._width * ctx._info_header._height];

		memset(ctx._rgb_data, 0, ctx._info_header._size_image);

		TPosMap::iterator itr = m_PosMap.find(m_nKey);
		if (itr == m_PosMap.end())
			return;

		TPosList& list = itr->second;

		for (TPosList::iterator listItr = list.begin(); listItr != list.end(); ++listItr)
		{
			INT32 y = (INT32)((INT64)listItr->x * ctx._info_header._width / MAX_SCENE_WIDTH_CONV);
			INT32 x = (INT32)((INT64)listItr->y * ctx._info_header._height / MAX_SCENE_WIDTH_CONV);

			ctx._rgb_data[y * ctx._info_header._width + x]._r = 0xff;
		}
	}

	bmp_write_color(&ctx);

	delete[] ctx._rgb_data;
	ctx._rgb_data = NULL;

	bmp_write_over(&ctx);
}
