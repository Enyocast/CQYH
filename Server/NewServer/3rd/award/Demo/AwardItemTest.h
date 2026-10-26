// AwardItemTest.h : main header file for the AWARDITEMTEST application
//

#if !defined(AFX_AWARDITEMTEST_H__DC6965FA_C5C9_46F5_BE39_8CBD074B6506__INCLUDED_)
#define AFX_AWARDITEMTEST_H__DC6965FA_C5C9_46F5_BE39_8CBD074B6506__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAwardItemTestApp:
// See AwardItemTest.cpp for the implementation of this class
//

class CAwardItemTestApp : public CWinApp
{
public:
	CAwardItemTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAwardItemTestApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAwardItemTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AWARDITEMTEST_H__DC6965FA_C5C9_46F5_BE39_8CBD074B6506__INCLUDED_)
