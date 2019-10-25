// CityView.cpp : implementation of the CCityView class
//

#include "stdafx.h"
#include "City.h"

#include "CityDoc.h"
#include "CityView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCityView

IMPLEMENT_DYNCREATE(CCityView, CView)

BEGIN_MESSAGE_MAP(CCityView, CView)
	//{{AFX_MSG_MAP(CCityView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCityView construction/destruction

CCityView::CCityView()
{
	// TODO: add construction code here
	bStart = false;
	zoom_level = 30;
	pButtons = NULL;

}

CCityView::~CCityView()
{
}

BOOL CCityView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCityView drawing

void CCityView::OnDraw(CDC* pDC)
{
	if(!bStart)
	{
		SetTimer(1,2000,NULL);
		pSelectedObject = NULL;	
	}
	ConsoleInit();
	DrawGrid();
	DrawStatusBar();
	bStart = TRUE;

}

/////////////////////////////////////////////////////////////////////////////
// CCityView diagnostics

#ifdef _DEBUG
void CCityView::AssertValid() const
{
	CView::AssertValid();
}

void CCityView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCityDoc* CCityView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCityDoc)));
	return (CCityDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCityView message handlers

void CCityView::DrawGrid()
{
	CCityDoc* pDoc = GetDocument();
	CGrid		*pGrid;
	CGridCell	*pCell;
	
	long x, y;
	
	pGrid = pDoc->pManager->GetGrid();
	pCell = pGrid->GetFirstCell();

	x = 0;
	y = 0;
	while(pCell)
	{	
		pCell = pCell->pRightCell;
		x++;
	}

	pCell = pGrid->GetFirstCell();

	while(pCell)
	{
		pCell = pCell->pBottomCell;
		y++;
	}
	
	for(int i = 0; i <= y - 1; i++)
	{
		
		for(int j = 0; j <= x - 1; j++)
		{
			DrawCell(j,i);	
		}
	}
	
	
	
}

void CCityView::OnMouseMove(UINT nFlags, CPoint point) 
{
	
	//CView::OnMouseMove(nFlags, point);
	long		xCoord, yCoord;
	long		xCoord_new, yCoord_new;
	bool		bNewHasObject;
	bool		bOldHasObject;
	CGrid		*pGrid;
	CCityDoc	*pDoc = GetDocument();

	pGrid = pDoc->pManager->GetGrid();
	

	//get curr cell;
	xCoord = OldMousePoint.x / zoom_level;
	yCoord = OldMousePoint.y / zoom_level;
	
	
	xCoord_new = point.x / zoom_level;
	yCoord_new = point.y / zoom_level;

	
	if((point.x <= (pConsole->x1_leftNav - zoom_level)) &&
		(point.y <= (pConsole->y1 - zoom_level)))
	{
		if (pGrid->IsValidCellPos(xCoord_new, yCoord_new))
		{
			
			if((xCoord_new != xCoord) || (yCoord_new != yCoord))
			{
				CDC *pDC = GetDC();
				
				CBrush lightbrush;
				
				lightbrush.CreateSolidBrush(RGB(180,250,207));
				
				bOldHasObject = pGrid->IsObjectAtCell(xCoord,yCoord);
				bNewHasObject = pGrid->IsObjectAtCell(xCoord_new,yCoord_new);

				//get new screen coords;
				xCoord *= zoom_level;
				yCoord *= zoom_level;
				xCoord_new *= zoom_level;
				yCoord_new *= zoom_level;
				
				if(!bOldHasObject)
					DrawCell(xCoord/zoom_level,yCoord/zoom_level);
				
				if(!bNewHasObject)
				{
					pDC->SelectObject(&lightbrush);
					pDC->Rectangle(xCoord_new,yCoord_new, xCoord_new + zoom_level, yCoord_new + zoom_level);
				}
				pDC->SelectStockObject(WHITE_BRUSH);
				ReleaseDC(pDC);
			}
			OldMousePoint = point;
		}
	}
}



void CCityView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	long xCoord, yCoord;
	CGrid		*pGrid;
	CCityDoc	*pDoc = GetDocument();
	buttonitem_t	*pBtnItem = pButtons;


	pGrid = pDoc->pManager->GetGrid();
	OldPressedPoint = point;

	//
	//any buttons pressed?
	//
	while(pBtnItem)
	{
		if(pBtnItem->pBtn->rectButton.PtInRect(point))
		{
			DrawButton(pBtnItem->pBtn,TRUE);
			ProcessBtn(pBtnItem->pBtn);
			break;
		}
		pBtnItem = pBtnItem->pNext;
	}
	
	//get curr cell;
	xCoord = point.x / zoom_level;
	yCoord = point.y / zoom_level;
	
	if (pGrid->IsValidCellPos(xCoord, yCoord) && pSelectedObject)
	{
		
		if((point.x <= pConsole->x1_leftNav) && 
			(point.y <= pConsole->y1))
		{
			CGridCell *pCell = pGrid->GetCellAtPos(xCoord,yCoord);
			cityobjs_t* pObjs = pDoc->pManager->pCityObjs;
			
			pDoc->pManager->SetObjectAtCell(xCoord,yCoord,pSelectedObject);
			
			DrawCell(xCoord,yCoord);
			DrawCell(xCoord+1,yCoord);
			DrawCell(xCoord,yCoord+1);
			DrawCell(xCoord-1,yCoord);
			DrawCell(xCoord,yCoord-1);
		}
	}

	UpdateMoney();
}

void CCityView::DrawCell(long x, long y)
{
	CCityDoc	*pDoc = GetDocument();
	CGrid		*pGrid;
	CGridCell	*pCell;
	CDC			dcMem;
	CDC			*pDC = GetDC();
	long		xPixel;
	long		yPixel;
	long		xSize;
	long		ySize;
	
	pGrid = pDoc->pManager->GetGrid();

	if (pGrid->IsValidCellPos(x,y))
	{
		CBitmap bitmap;
		BITMAP bm;
		pCell = pGrid->GetCellAtPos(x,y);
		
		if(pCell->IsDrawingCell())
		{
			xPixel = x*zoom_level;
			yPixel = y*zoom_level;
			long	lBitHeight;
			long	lBitWidth;

			if((xPixel <= (pConsole->x1_leftNav - zoom_level)) &&
				(yPixel <= (pConsole->y1 - zoom_level)))
			{
				bitmap.LoadBitmap(pCell->GetPic());

				dcMem.CreateCompatibleDC(pDC);
				dcMem.SelectObject(&bitmap);
				
				if(pCell->GetObject())
				{
					xSize = pCell->GetObject()->GetDim1() * zoom_level;
					ySize = pCell->GetObject()->GetDim2() * zoom_level;
					
				} else {
					xSize = zoom_level;
					ySize = zoom_level;
				}
				
				bitmap.GetBitmap(&bm);
				lBitHeight = bm.bmHeight;
				lBitWidth = bm.bmWidth;

				pDC->StretchBlt(xPixel,yPixel,xSize,ySize,&dcMem,0,0,lBitWidth,lBitHeight,SRCCOPY);
				dcMem.DeleteDC();
			}
		}
	}
	ReleaseDC(pDC);
}


void CCityView::OnTimer(UINT nIDEvent) 
{
	
	//CView::OnTimer(nIDEvent);
	
	CCityDoc* pDoc = GetDocument();
	ZONE_NODE* pZoneNode;


	pDoc->pManager->IncrementDate();
	
	UpdateDate();
	UpdateMoney();
	UpdatePopulation();
	UpdateRCI();

	pZoneNode = pDoc->pManager->DevelopZones();
	
	while(pZoneNode)
	{
		DrawCell(pZoneNode->pZone->x, pZoneNode->pZone->y);
		if(pZoneNode->pNext)
		{
			pZoneNode = pZoneNode->pNext;
			delete pZoneNode->pPrev->pZone;
			delete pZoneNode->pPrev;

		} else {

			delete pZoneNode->pZone;
			delete pZoneNode;
			pZoneNode = NULL;
		}
	}

}

void CCityView::UpdateMoney(void)
{
	CDC *pDC = GetDC();
	CCityDoc *pDoc = GetDocument();
	CFont font;
	CRect rect;
	CString szFunds;
	
	CPen pen (PS_SOLID,1,RGB(255,255,255));
	
	pDC->SelectObject(&pConsole->ConsoleBack);
	pDC->Rectangle(pConsole->MoneyText_x - 2,pConsole->MoneyText_y, pConsole->MoneyText_x + 150, pConsole->MoneyText_y + 25);

	pDC->SelectObject(&pen);
	pDC->MoveTo(pConsole->MoneyText_x - 1,pConsole->MoneyText_y + 25 - 1);
	pDC->LineTo(pConsole->MoneyText_x + 150 - 1, pConsole->MoneyText_y + 25 - 1);
	pDC->LineTo(pConsole->MoneyText_x + 150 - 1,pConsole->MoneyText_y);

	GetClientRect(&rect);
	font.CreatePointFont(140,_T("Arial"));
	
	szFunds.Format(_T("Funds: $%i      "),pDoc->pManager->GetFunds());
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(&pConsole->ConsoleFont);
	
	pDC->TextOut(pConsole->MoneyText_x,pConsole->MoneyText_y ,szFunds);
	
	//
	//Cleanup
	//
	pDC->SelectStockObject(BLACK_PEN);	
	pDC->SelectStockObject(WHITE_BRUSH);
	pDC->SelectStockObject(SYSTEM_FONT);
	ReleaseDC(pDC);
	
}


void CCityView::DrawStatusBar()
{
	CDC* pDC = GetDC();
	CBrush brush;
	buttonitem_t	*pTemp = pButtons;

	brush.CreateSolidBrush(RGB(0,0,255));
	pDC->SelectObject(&brush);
	
	pDC->Rectangle(pConsole->x1,pConsole->y1,pConsole->x2,pConsole->y2);
	pDC->Rectangle(pConsole->x1_leftNav,pConsole->y1_leftNav,pConsole->x2_leftNav,pConsole->y2_leftNav);
	
	while(pTemp)
	{
		DrawButton(pTemp->pBtn,FALSE);
		pTemp = pTemp->pNext;
	}
	
	//cleanup
	pDC->SelectStockObject(WHITE_BRUSH);
	ReleaseDC(pDC);
}

void CCityView::ConsoleInit()
{
	CRect rect;

	GetClientRect(&rect);
	if(!bStart)
		pConsole = new console_t;
	
	//
	//Console dimensions
	//
	pConsole->x1 = 0;
	pConsole->x2 = rect.Width();
	pConsole->y1 = rect.Height() - 100;
	pConsole->y2 = rect.Height();
	pConsole->x1_leftNav = rect.Width() - 100;
	pConsole->x2_leftNav = rect.Width();
	pConsole->y1_leftNav = 0;
	pConsole->y2_leftNav = rect.Height();
	
	//date
	pConsole->DateText_x = 300;
	pConsole->DateText_y = rect.Height() - 60;
	
	//money
	pConsole->MoneyText_x = 100;
	pConsole->MoneyText_y = rect.Height() - 60;

	//population
	pConsole->PopText_x = 500;
	pConsole->PopText_y = rect.Height() - 60;

	//RCI
	pConsole->x1RCI = rect.Width() - 75;
	pConsole->x2RCI = rect.Width() - 25;
	pConsole->y1RCI = rect.Height() - 500;
	pConsole->y2RCI = rect.Height() - 375;
	
	if (!bStart)
	{
		pConsole->RCIfont.CreatePointFont(90,_T("Arial"));
		pConsole->ConsoleBack.CreateSolidBrush(RGB(164,164,251));
		pConsole->ConsoleFont.CreatePointFont(140,_T("Arial"));
		AddButton(_T("Zoom Out"), 1);
		AddButton(_T("Zoom In"), 2);
		AddButton(_T("Road"),7);
		AddButton(_T("Residential"), 3);
		AddButton(_T("Commercial"), 4);
		AddButton(_T("Industrial"), 5);
		AddButton(_T("Power"), 6);
	}

}

void CCityView::UpdateDate(void)
{
	CString szDate;
	citydate_t *pDate;
	CDC *pDC = GetDC();
	CCityDoc* pDoc = GetDocument();
	CBrush brush;
	CPen pen (PS_SOLID,1,RGB(255,255,255));
	
	pDC->SelectObject(&pConsole->ConsoleBack);
	pDC->Rectangle(pConsole->DateText_x - 2,pConsole->DateText_y, pConsole->DateText_x + 150, pConsole->DateText_y + 25);
	
	
	pDC->SelectObject(&pen);
	pDC->MoveTo(pConsole->DateText_x - 1,pConsole->DateText_y + 25 - 1);
	pDC->LineTo(pConsole->DateText_x + 150 - 1, pConsole->DateText_y + 25 - 1);
	pDC->LineTo(pConsole->DateText_x + 150 - 1,pConsole->DateText_y);

	pDate = pDoc->pManager->GetDate();
	pDC->SelectObject(&pConsole->ConsoleFont);
	pDC->SetBkMode(TRANSPARENT);
	szDate.Format(_T("Date: %i/%i/%i   "),pDate->dwMonth,pDate->dwDay,pDate->dwYear);
	pDC->TextOut(pConsole->DateText_x,pConsole->DateText_y,szDate);
	

	//cleanup
	pDC->SelectStockObject(BLACK_PEN);	
	pDC->SelectStockObject(WHITE_BRUSH);
	pDC->SelectStockObject(SYSTEM_FONT);
	ReleaseDC(pDC);
}

void CCityView::UpdatePopulation(void)
{
	CString szPopulation;
	CCityDoc* pDoc = GetDocument();
	CDC *pDC = GetDC();
	CPen pen (PS_SOLID,1,RGB(255,255,255));

	pDC->SelectObject(&pConsole->ConsoleBack);
	pDC->Rectangle(pConsole->PopText_x - 2,pConsole->PopText_y, pConsole->PopText_x + 150, pConsole->PopText_y + 25);

	pDC->SelectObject(&pen);
	pDC->MoveTo(pConsole->PopText_x - 1,pConsole->PopText_y + 25 - 1);
	pDC->LineTo(pConsole->PopText_x + 150 - 1, pConsole->PopText_y + 25 - 1);
	pDC->LineTo(pConsole->PopText_x + 150 - 1,pConsole->PopText_y);

	pDC->SelectObject(&pConsole->ConsoleFont);
	pDC->SetBkMode(TRANSPARENT);
	szPopulation.Format(_T("Population: %i  "),pDoc->pManager->GetPopulation());
	pDC->TextOut(pConsole->PopText_x,pConsole->PopText_y,szPopulation);
	
	//cleanup
	pDC->SelectStockObject(BLACK_PEN);	
	pDC->SelectStockObject(WHITE_BRUSH);
	pDC->SelectStockObject(SYSTEM_FONT);
	ReleaseDC(pDC);
}

void CCityView::UpdateRCI(void)
{

	CCityDoc* pDoc = GetDocument();
	CDC *pDC = GetDC();
	CString szRCI;
	CBrush	brush;
	CBrush	resBrush;
	CBrush	comBrush;
	CBrush	indBrush;
	RCI		*rci;
	long	x1RCI, x2RCI, y1RCI, y2RCI;
	long	lRes,lCom,lInd;


	rci = &pDoc->pManager->GetRCI();

	lRes = rci->wRes - 50;
	lCom = rci->wCom - 50;
	lInd = rci->wInd - 50;

	//delete rci;

	pDC->SelectObject(&pConsole->ConsoleBack);
	pDC->Rectangle(pConsole->x1RCI, pConsole->y1RCI, pConsole->x2RCI, pConsole->y2RCI);
	
	szRCI = _T("R C I");
	pDC->SelectObject(&pConsole->RCIfont);
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(pConsole->x1RCI + 10, pConsole->y1RCI + 62, szRCI);
	
	resBrush.CreateSolidBrush(RGB(0,255,0));
	comBrush.CreateSolidBrush(RGB(0,0,255));
	indBrush.CreateSolidBrush(RGB(255,255,165));
	
	//Residential line
	pDC->SelectObject(&resBrush);
	x1RCI = pConsole->x1RCI + 10;
	x2RCI = x1RCI + 5;
	y2RCI = pConsole->y2RCI - ((pConsole->y2RCI - pConsole->y1RCI)/ 2);
	y1RCI = y2RCI - lRes;
	pDC->Rectangle(x1RCI,y1RCI,x2RCI,y2RCI);
	
	//Commercial line
	pDC->SelectObject(&comBrush);
	x1RCI = x2RCI + 5;
	x2RCI = x1RCI + 5;
	y1RCI = y2RCI - lCom;
	pDC->Rectangle(x1RCI,y1RCI,x2RCI,y2RCI);
	
	//Industrial line
	pDC->SelectObject(&indBrush);
	x1RCI = x2RCI + 5;
	x2RCI = x1RCI + 5;
	y1RCI = y2RCI - lInd;
	pDC->Rectangle(x1RCI,y1RCI,x2RCI,y2RCI);

	//cleanup
	pDC->SelectStockObject(BLACK_PEN);	
	pDC->SelectStockObject(WHITE_BRUSH);
	pDC->SelectStockObject(SYSTEM_FONT);
	ReleaseDC(pDC);
}

void CCityView::DrawButton(button_t *pBtn, bool bPressed)
{
	CDC* pDC = GetDC();
	CPen pen(PS_SOLID,1,RGB(255,255,255));
	
	pDC->SelectObject(&pConsole->ConsoleBack);
	pDC->Rectangle((LPRECT)pBtn->rectButton);

	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(pBtn->rectButton.left + 5,pBtn->rectButton.top + 5,pBtn->szButtonText);
	pDC->SelectObject(&pen);
	pDC->MoveTo(pBtn->rectButton.left,pBtn->rectButton.bottom - 1);

	if (bPressed)
	{
		pDC->LineTo(pBtn->rectButton.right - 1,pBtn->rectButton.bottom - 1);
		pDC->LineTo(pBtn->rectButton.right - 1,pBtn->rectButton.top);

	} else {

		pDC->LineTo(pBtn->rectButton.left,pBtn->rectButton.top);
		pDC->LineTo(pBtn->rectButton.right,pBtn->rectButton.top);
	}
	
	//cleanup
	pDC->SelectStockObject(BLACK_PEN);	
	pDC->SelectStockObject(WHITE_BRUSH);
	ReleaseDC(pDC);
}

void CCityView::ZoomOut()
{
	if (zoom_level > 10)
	{
		zoom_level -= 10;
		ClearScreen();
		DrawGrid();
	}
}

void CCityView::ZoomIn()
{
	if(zoom_level < 300)
	{
		zoom_level += 10;
		ClearScreen();
		DrawGrid();
	}
}

void CCityView::OnLButtonUp(UINT nFlags, CPoint point) 
{

	//CView::OnLButtonUp(nFlags, point);
	buttonitem_t	*pButtonItem = pButtons;

	while(pButtonItem)
	{
		if(pButtonItem->pBtn->rectButton.PtInRect(OldPressedPoint))
		{
			DrawButton(pButtonItem->pBtn, FALSE);
			break;
		}
		pButtonItem = pButtonItem->pNext;
	}
	
}

void CCityView::AddButton(CString szBtnText, long ID)
{
	buttonitem_t	*pTemp;
	static long	yStart = 20;

	if (!pButtons)
	{
		pButtons = new buttonitem_t;
		pButtons->pNext = NULL;
		pButtons->pPrev = NULL;
		pTemp = pButtons;

	} else {
		
		pTemp = pButtons;
		while(pTemp->pNext)
			pTemp = pTemp->pNext;

		pTemp->pNext = new buttonitem_t;
		pTemp = pTemp->pNext;
		pTemp->pNext = NULL;
	}
	
	pTemp->pBtn = new button_t;
	pTemp->pBtn->szButtonText = szBtnText;
	pTemp->pBtn->rectButton.top = yStart;
	pTemp->pBtn->rectButton.bottom = yStart + 30;
	pTemp->pBtn->rectButton.left = pConsole->x1_leftNav + 10;
	pTemp->pBtn->rectButton.right = pConsole->x2_leftNav - 10;
	pTemp->pBtn->BTN_ID = ID;

	yStart += 50;

}

void CCityView::ProcessBtn(button_t *pButton)
{
	CCityDoc *pDoc = GetDocument();
	
	switch(pButton->BTN_ID)
	{
		case 1:
			ZoomOut();
			break;
		case 2:
			ZoomIn();
			break;
		case 3:
			pSelectedObject = pDoc->pManager->pCityObjs->pRes;
			break;
		case 4:
			pSelectedObject = pDoc->pManager->pCityObjs->pComm;
			break;
		case 5:
			pSelectedObject = pDoc->pManager->pCityObjs->pInd;
			break;
		case 6:
			pSelectedObject = pDoc->pManager->pCityObjs->pCoalPP;
			break;
		case 7:
			pSelectedObject = pDoc->pManager->pCityObjs->pNSRoad;
			break;
		
	}

}

void CCityView::ClearScreen()
{
	CDC* pDC = GetDC();

	CBrush brush;
	brush.CreateSolidBrush(RGB(255,255,255));

	pDC->SetBkMode(OPAQUE);
	pDC->SelectObject(&brush);
	
	pDC->Rectangle(0,0,pConsole->x1_leftNav,pConsole->y1);

	pDC->SelectStockObject(BLACK_BRUSH);
	ReleaseDC(pDC);
}
