// CityView.h : interface of the CCityView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CITYVIEW_H__6AB78D7D_4FAA_11D5_8D63_00B0D081587C__INCLUDED_)
#define AFX_CITYVIEW_H__6AB78D7D_4FAA_11D5_8D63_00B0D081587C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


typedef struct CONSOLE{

	//navbar coords
	long	x1;
	long	x2;
	long	y1;
	long	y2;
	long	x1_leftNav;
	long	x2_leftNav;
	long	y1_leftNav;
	long	y2_leftNav;

	//moneybox coords
	long	MoneyText_x;
	long	MoneyText_y;

	//populationbox coords
	long	PopText_x;
	long	PopText_y;

	//date coords
	long	DateText_x;
	long	DateText_y;

	//RCI coords
	long	x1RCI;
	long	x2RCI;
	long	y1RCI;
	long	y2RCI;
	CFont	RCIfont;

	CFont	ConsoleFont;
	CBrush	ConsoleBack;

} console_t;

typedef struct BUTTON{

	CRect		rectButton;
	CString		szButtonText;
	long		BTN_ID;
	
} button_t;


typedef struct BUTTON_NODE{

	BUTTON	*pBtn;
	BUTTON_NODE	*pNext;
	BUTTON_NODE	*pPrev;
	
} buttonitem_t;

class CCityView : public CView
{
protected: // create from serialization only
	CCityView();
	DECLARE_DYNCREATE(CCityView)

// Attributes
public:
	CCityDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCityView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCityView();
	void		DrawGrid(void);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CCityObj	*pSelectedObject;

private:
	CPoint		OldMousePoint;
	CPoint		OldPressedPoint;
	int			zoom_level;
	void		DrawCell(long x, long y);
	bool		bStart;
	void		UpdateMoney(void);
	void		UpdateDate(void);
	void		DrawStatusBar();
	console_t	*pConsole;
	void		ConsoleInit();
	void		UpdatePopulation();
	void		UpdateRCI(void);
	void		DrawButton(button_t *pBtn, bool bPress);
	void		ZoomOut();
	void		ZoomIn();
	void		AddButton(CString szBtnText, long ID);
	buttonitem_t	*pButtons;
	void		ProcessBtn(button_t *pButton);
	void		ClearScreen();


// Generated message map functions
protected:
	//{{AFX_MSG(CCityView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CityView.cpp
inline CCityDoc* CCityView::GetDocument()
   { return (CCityDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CITYVIEW_H__6AB78D7D_4FAA_11D5_8D63_00B0D081587C__INCLUDED_)
