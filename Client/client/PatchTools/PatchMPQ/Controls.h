/*====================================================================
	Created Date  :		2005-7-3
	
	Specification :  
====================================================================*/
#pragma once

	enum EFontStyle
	{
		eFontStyleNormal	= 0x0,
		eFontStyleBold		= 0x1,
		eFontStyleItalic	= 0x2,
		eFontStyleUnderline	= 0x4,
		eFontStyleStrikeOut	= 0x8,
		eFontStyleMax = eFontStyleBold | eFontStyleItalic | eFontStyleUnderline | eFontStyleStrikeOut
	};

	enum EImageStyle
	{
		eImageStyle_TopLeft,		//no stretch nor scale nor tiled
		eImageStyle_TopRight,		//no stretch nor scale nor tiled
		eImageStyle_Center,			//no stretch nor scale nor tiled
		eImageStyle_BottomLeft,		//no stretch nor scale nor tiled
		eImageStyle_BottomRight,	//no stretch nor scale nor tiled
		eImageStyle_Stretched,		//stretch to full
		eImageStyle_Scaled,			//U, V keep same ratio
		eImageStyle_Tiled,
		eImageStyle_Max
	};


typedef BOOL (WINAPI* LPTRANSPARENTBLT)(HDC, int, int, int, int, HDC, int, int, int, int, UINT); 
extern LPTRANSPARENTBLT g_pTransparentBlt;

	void  CU_SetupRegion(CRgn& rgn, CDC *pDC
								, CBitmap &cBitmap, COLORREF TransColor
								, UINT uTilesX = 1, UINT uOffsetX = 0
								, UINT uTilesY = 1, UINT uOffsetY = 0
								);
	
	void  CU_TransBlt( HDC hdcDest,      // 目标DC
						 int nXOriginDest,   // 目标X偏移
						 int nYOriginDest,   // 目标Y偏移
						 int nWidthDest,     // 目标宽度
						 int nHeightDest,    // 目标高度
						 HDC hdcSrc,         // 源DC
						 int nXOriginSrc,    // 源X起点
						 int nYOriginSrc,    // 源Y起点
						 int nWidthSrc,      // 源宽度
						 int nHeightSrc,     // 源高度
						 UINT crTransparent  // 透明色,COLORREF类型
						 );
	

	void  CU_TransparentBlt(CDC *pDC, CBitmap &cBitmap
										, CPoint ptStart = CPoint(0, 0)
										, CSize szExtend = CSize(0, 0)
										, BOOL bTrans = FALSE
										, COLORREF TransColor = RGB(0, 0, 0)
										, UINT uTilesX = 1
										, UINT uOffsetX = 0
										, UINT uTilesY = 1
										, UINT uOffsetY = 0
										, DWORD bltMode = SRCCOPY);


	SIZE CU_GetBitmapSize(CBitmap& bmp);

	void CU_Blt(CDC* pdcDest,
		CBitmap& srcBmp,
		int destX,
		int destY,
		int destCX,
		int destCY,
		int srcX = 0,
		int srcY = 0,
		DWORD bltMode = SRCCOPY);

	void CU_DrawIconCaption(CDC *pDC
		, UINT txtAlignFmt
		, CPoint ptStart, CSize szExtend
		, HICON hIcon, UINT uIconSize
		, LPCTSTR lpText
		, LPCTSTR lpFontFamily, UINT uFontHeight, COLORREF refFontColor, EFontStyle e = eFontStyleNormal
		, UINT uSpaceIconText = 0
		, LPCTSTR lpText2 = 0
		, LPCTSTR lpFontFamily2 = 0, UINT uFontHeight2 = 0, COLORREF refFontColor2 = 0, EFontStyle e2 = eFontStyleNormal
		, UINT uSpaceTextText2 = 0);