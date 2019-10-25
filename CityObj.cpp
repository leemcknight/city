// CityObj.cpp: implementation of the CCityObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "City.h"
#include "CityObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCityObj::CCityObj()
{
	m_lInitialCost = 0;
	m_dwCapacity = 0;
	m_lUpkeepCost = 0;
	m_uDim1 = 1;
	m_uDim2 = 1;
	m_uPic = IDB_LOT;
}

CCityObj::~CCityObj()
{

}

void CCityObj::SetInitialCost( long lNewCost )
{
	if((lNewCost >= 0) && (m_lInitialCost == 0))
		m_lInitialCost = lNewCost;

}

void CCityObj::SetDim1( long dim1 )
{
	if( dim1 > 0 )
		m_uDim1 = dim1;
}

void CCityObj::SetDim2( long dim2 )
{
	if( dim2 > 0 )
		m_uDim2 = dim2;
}





