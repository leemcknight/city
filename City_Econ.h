// City_Econ.h: interface for the CCity_Econ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CITY_ECON_H__C243A112_5126_11D5_8D63_00B0D081587C__INCLUDED_)
#define AFX_CITY_ECON_H__C243A112_5126_11D5_8D63_00B0D081587C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCity_Econ  
{
public:
	CCity_Econ();
	virtual ~CCity_Econ();
	long	GetFunds() const;
	void	DoTransact(long lAmt);
	void	CollectTaxes(DWORD dwResCap, DWORD dwComCap, DWORD dwIndCap);

private:
	long	lFunds;
	BYTE	byRes_tax;
	BYTE	byCom_tax;
	BYTE	byInd_tax;

};

#endif // !defined(AFX_CITY_ECON_H__C243A112_5126_11D5_8D63_00B0D081587C__INCLUDED_)
