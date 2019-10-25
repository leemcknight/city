// ToolWindow.cpp : implementation file
//

#include "stdafx.h"
#include "City.h"
#include "ToolWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolWindow dialog


CToolWindow::CToolWindow(CWnd* pParent /*=NULL*/)
	: CDialog(CToolWindow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CToolWindow)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CToolWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolWindow)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CToolWindow, CDialog)
	//{{AFX_MSG_MAP(CToolWindow)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton_Road)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolWindow message handlers

void CToolWindow::OnButton_Road() 
{
	// TODO: Add your control notification handler code here

	lRoadType = 1;
	
}
