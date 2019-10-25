// CityDate.h: interface for the CCityDate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CITYDATE_H__8049BD01_550E_11D5_8D63_00B0D081587C__INCLUDED_)
#define AFX_CITYDATE_H__8049BD01_550E_11D5_8D63_00B0D081587C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCityDate  
{
public:
	CCityDate();
	virtual ~CCityDate();
	citydate_t*	GetDate() {return m_pDate;}
	bool	IncrementDate();

private:

	citydate_t	*m_pDate;
	

};

#endif // !defined(AFX_CITYDATE_H__8049BD01_550E_11D5_8D63_00B0D081587C__INCLUDED_)
