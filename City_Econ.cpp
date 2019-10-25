// City_Econ.cpp: implementation of the CCity_Econ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "City.h"
#include "City_Econ.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCity_Econ::CCity_Econ()
{
	lFunds = 0;
}

CCity_Econ::~CCity_Econ()
{

}

long CCity_Econ::GetFunds() const {return lFunds;}
void CCity_Econ::DoTransact(long lAmt){lFunds += lAmt;}

void CCity_Econ::CollectTaxes(DWORD dwResCap, DWORD dwComCap, DWORD dwIndCap)
{
	float fTaxRate;

	//residential
	fTaxRate = (float)(byRes_tax/100);
	lFunds += (long)(fTaxRate*(dwResCap*1000));

	//commercial
	fTaxRate = (float)(byCom_tax/100);
	lFunds += (long)(fTaxRate*(dwComCap*50));

	//industrial
	fTaxRate = (float)(byInd_tax/100);
	lFunds += (long)(fTaxRate*(dwIndCap*300));
}
