/*====================================================================
	Created Date  :		2005-7-3
	
	Specification :  
====================================================================*/
#pragma once

#include <string>

class BmpRgnButton : public CButton
{
// Construction
public:
	BmpRgnButton();

	void Set4In1Bitmap(UINT uID, COLORREF refTrans = RGB(255, 0, 255));
	void Set4In1Bitmap(CBitmap* p, COLORREF refTrans = RGB(255, 0, 255));

	void SetDrawTrans(BOOL b, COLORREF refTrans = RGB(255, 0, 255))
	{
		_bDrawTrans = b;
		_refDrawTrans = refTrans;
	}
	
	bool IsVerticalCaption(){ return _bIsVerticalCaption; }
	void SetToVerticalCaption(bool on){ _bIsVerticalCaption = on; }
	void SetCaption(const CString& strCap){ _strCaption = strCap; }
	
	std::string			_strSoundFile;

protected:

	CString			_strCaption;
	HCURSOR			_hCursor;
	BOOL			_bMouseHover;

	CBitmap*		_pBmp;
	COLORREF		_refTrans;
	UINT			_uBmpItemWidth;
	UINT			_uBmpItemHeight;
	BOOL			_bRgnCreated;
	CRgn			_RgnWnd;

	BOOL			_bDrawTrans;
	COLORREF		_refDrawTrans;
	bool			_bIsVerticalCaption;

	void SetupRegion(CDC *pDC, CBitmap &cBitmap, COLORREF TransColor);
	void AdjustSize();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyClass)
	public:
		virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~BmpRgnButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyClass)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};
