#if !defined(AFX_TOOLWINDOW_H__ACDFB7E1_5057_11D5_8D63_00B0D081587C__INCLUDED_)
#define AFX_TOOLWINDOW_H__ACDFB7E1_5057_11D5_8D63_00B0D081587C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolWindow dialog

class CToolWindow : public CDialog
{
// Construction
public:
	CToolWindow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CToolWindow)
	
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolWindow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	

	
	public:
		long	lRoadType;
// Implementation
protected:

	
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLWINDOW_H__ACDFB7E1_5057_11D5_8D63_00B0D081587C__INCLUDED_)
