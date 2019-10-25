// City.h : main header file for the CITY application
//

#if !defined(AFX_CITY_H__6AB78D75_4FAA_11D5_8D63_00B0D081587C__INCLUDED_)
#define AFX_CITY_H__6AB78D75_4FAA_11D5_8D63_00B0D081587C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "type.h"
#include "CityManager.h"

/////////////////////////////////////////////////////////////////////////////
// CCityApp:
// See City.cpp for the implementation of this class
//

class CCityApp : public CWinApp
{
public:
	CCityApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCityApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCityApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CITY_H__6AB78D75_4FAA_11D5_8D63_00B0D081587C__INCLUDED_)
