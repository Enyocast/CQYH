#pragma once


// TransparentCaption

class TransparentCaption : public CStatic
{
	DECLARE_DYNAMIC(TransparentCaption)

public:
	TransparentCaption();
	virtual ~TransparentCaption();

	void SetTextAlignFormat(UINT fmt) { _textAlign = fmt; }
	void SetTextColor(COLORREF clr) { _txtColor = clr; }
	void SetBgImage(CBitmap* pBmp, const CRect& rcOnBmp){ _pBgImg = pBmp; _rcOnBgImg = rcOnBmp; }

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();

	CFont _font;
	UINT _textAlign;
	COLORREF _txtColor;
	CBitmap* _pBgImg;
	CRect _rcOnBgImg;
};


