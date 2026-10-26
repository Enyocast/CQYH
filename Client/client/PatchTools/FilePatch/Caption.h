// *************************************************************************************
// 
// 
// 	All Rights Reserved 
// 
// 	Create Date		:		2006-10-11
// *************************************************************************************

#pragma once
#include "Controls.h"

class Caption : public CStatic
{
	// Construction
public:
	Caption();
	virtual ~Caption();

	void SetCaptionFont(int iHeight, LPCTSTR lpszFamilyName
		, COLORREF clr = RGB(0, 0, 0), EFontStyle e = eFontStyleNormal
		);
	void SetCaptionText(LPCTSTR lpszString, HICON hIcon=NULL, int iIconSize = 32);

	void SetTextColor(COLORREF clr);
	void SetBgImage(CBitmap* pBmp, const CRect& rcOnBmp){ _pBgImg = pBmp; _rcOnBgImg = rcOnBmp; }
	void SetTextAlignFormat(UINT fmt) { _textAlign = fmt; }


protected:
	COLORREF		m_clrFont;
	HICON			m_hIcon;
	int				_iIconSize;
	UINT			_iFontHeight;
	CString			_strFontFamily;
	EFontStyle		_eFontStyle;

	CBitmap* _pBgImg;
	CRect _rcOnBgImg;

	UINT _textAlign;
	CDC _memDC;

	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

