#if !defined(AFX_TOOLBOX_H__D090BAD1_5448_11D5_8D63_00B0D081587C__INCLUDED_)
#define AFX_TOOLBOX_H__D090BAD1_5448_11D5_8D63_00B0D081587C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolBox dialog

class CToolBox : public CDialog
{
// Construction
public:
	CToolBox(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CToolBox)
	
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CToolBox)
	afx_msg void OnButton_Road();
	afx_msg void OnButton_Res();
	afx_msg void OnButton_Comm();
	afx_msg void OnButton_Ind();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBOX_H__D090BAD1_5448_11D5_8D63_00B0D081587C__INCLUDED_)
