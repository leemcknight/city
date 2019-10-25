// ToolBox.cpp : implementation file
//

#include "stdafx.h"
#include "City.h"
#include "ToolBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBox dialog


CToolBox::CToolBox(CWnd* pParent /*=NULL*/)
	//: CDialog(CToolBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CToolBox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
}


void CToolBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolBox)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CToolBox, CDialog)
	//{{AFX_MSG_MAP(CToolBox)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBox message handlers

void CToolBox::OnButton_Road() 
{
	// TODO: Add your control notification handler code here
	
}

void CToolBox::OnButton_Res() 
{
	// TODO: Add your control notification handler code here
	
}

void CToolBox::OnButton_Comm() 
{
	// TODO: Add your control notification handler code here
	
}

void CToolBox::OnButton_Ind() 
{
	// TODO: Add your control notification handler code here
	
}
