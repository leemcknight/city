// CityDoc.cpp : implementation of the CCityDoc class
//

#include "stdafx.h"
#include "City.h"

#include "CityDoc.h"
#include "toolbox.h"
#include "CityView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCityDoc

IMPLEMENT_DYNCREATE(CCityDoc, CDocument)

BEGIN_MESSAGE_MAP(CCityDoc, CDocument)
	//{{AFX_MSG_MAP(CCityDoc)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCityDoc construction/destruction

CCityDoc::CCityDoc()
{
	// TODO: add one-time construction code here
	pManager = new CCityManager;
	pManager->Initialize();

}

CCityDoc::~CCityDoc()
{
}

BOOL CCityDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	
	//CCityView::DrawGrid();
	
	
	return TRUE;

}



/////////////////////////////////////////////////////////////////////////////
// CCityDoc serialization

void CCityDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCityDoc diagnostics

#ifdef _DEBUG
void CCityDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCityDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCityDoc commands


void CCityDoc::OnFileNew() 
{
	// TODO: Add your command handler code here


}

