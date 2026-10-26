
#include "stdafx.h"
#include "DhtmlEdit.h"

IMPLEMENT_DYNCREATE(CDhtmlEdit, CWnd)
IMPLEMENT_DYNCREATE(AdDhtmlEdit, CDhtmlEdit)

//--------------------------------------------------------------------------------------

void CDhtmlEdit::SetHtmlString(const CString& strHTML)
{
	SAFE;

	if(!GetSafeHwnd() || !::IsWindow(GetSafeHwnd()))
	{
		return;
	}
	this->put_DocumentHTML(strHTML);
	
	UNSAFE;
}

//--------------------------------------------------------------------------------------

CString CDhtmlEdit::GetHtmlString()
{
	SAFE;
	
	return this->get_DocumentHTML();

	UNSAFE;
}

//--------------------------------------------------------------------------------------

void CDhtmlEdit::SetReadonly(BOOL readOnly)
{
	SAFE;

	this->put_BrowseMode(readOnly);

	UNSAFE;
}

//--------------------------------------------------------------------------------------

BOOL CDhtmlEdit::IsReadonly()
{
	SAFE;

	return this->get_BrowseMode();

	UNSAFE;
}

//--------------------------------------------------------------------------------------

void AdDhtmlEdit::SetAdURL(const CString& url, const CString& imgUrl)
{
	SAFE;
	
	SetReadonly(TRUE);
	
	_strUrl = url;
	_strImg = imgUrl;

	ResetURL();

	UNSAFE;
}

BEGIN_MESSAGE_MAP(AdDhtmlEdit, CDhtmlEdit)
ON_WM_SIZE()
END_MESSAGE_MAP()

void AdDhtmlEdit::OnSize(UINT nType, int cx, int cy)
{
	CDhtmlEdit::OnSize(nType, cx, cy);

	ResetURL();
}

void AdDhtmlEdit::ResetURL()
{
	SAFE;
	
	// 广告条
	CRect rc;
	GetWindowRect(&rc);
	int iWidth = rc.Width();
	int iHeight = rc.Height();

	CString strADSrcFileExt = _strImg.Right(3);
	CString strADHtml;
	if(strADSrcFileExt == _T("swf"))	// flash广告
	{
		strADHtml.Format(_T("<BODY topmargin=0 leftmargin=0>\
							<OBJECT classid=\"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000\"\
							codebase=\"http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=5,0,0,0\" WIDTH=\"%d\" HEIGHT=\"%d\">\
							<PARAM NAME=movie VALUE=\"%s\">\
							<PARAM NAME=quality VALUE=high>\
							<PARAM NAME=wmode VALUE=opaque>\
							<PARAM NAME=scale VALUE=Exactfit>\
							</OBJECT></BODY>"), iWidth, iHeight, _strImg);
	}
	else if(strADSrcFileExt == _T("htm") || strADSrcFileExt == _T("html"))
	{
		int wo = GetSystemMetrics(SM_CXVSCROLL);
		int ho = GetSystemMetrics(SM_CYHSCROLL);

		strADHtml.Format(_T("<BODY topmargin=0 leftmargin=0><a href=\"%s\"><iframe width=%d height=%d frameborder=0 scrolling=auto src=%s></iframe></a></BODY>"),
			_strUrl, iWidth + wo , iHeight + ho, _strImg);
	}

	else								// 图片广告
	{
		strADHtml.Format(_T("<BODY topmargin=0 leftmargin=0><a href=\"%s\"><IMG border=0 SRC=\"%s\" WIDTH=\"%d\" HEIGHT=\"%d\"/></a></BODY>")
			, _strUrl, _strImg, iWidth, iHeight);
	}

	SetHtmlString(strADHtml);

	UNSAFE;
}