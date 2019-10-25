// CityDoc.h : interface of the CCityDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CITYDOC_H__6AB78D7B_4FAA_11D5_8D63_00B0D081587C__INCLUDED_)
#define AFX_CITYDOC_H__6AB78D7B_4FAA_11D5_8D63_00B0D081587C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCityDoc : public CDocument
{
protected: // create from serialization only
	CCityDoc();
	DECLARE_DYNCREATE(CCityDoc)

// Attributes
public:

// Operations
public:
	CGrid	*GetGrid();
	cityobjs_t	*GetCityObjs();
	citydate_t*	GetDate();
	void	CityInit();
	CCityManager	*pManager;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCityDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCityDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCityDoc)
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CITYDOC_H__6AB78D7B_4FAA_11D5_8D63_00B0D081587C__INCLUDED_)
