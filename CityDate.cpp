// CityDate.cpp: implementation of the CCityDate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "City.h"
#include "CityDate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCityDate::CCityDate()
{
	m_pDate = new citydate_t;
	m_pDate->dwDay = 1;
	m_pDate->dwMonth = 1;
	m_pDate->dwYear = 1900;
}

CCityDate::~CCityDate()
{

}

/******************************************
IncrementDate()
	returns TRUE if it's a new year,
	FALSE otherwise.
******************************************/
bool CCityDate::IncrementDate()
{
	
	if(m_pDate->dwDay == 31)
	{
		m_pDate->dwDay = 1;

		if(m_pDate->dwMonth == 12)
		{
			m_pDate->dwMonth = 1;
			m_pDate->dwYear++;
			return TRUE;
		}
		else
			m_pDate->dwMonth++;
	}
	else
		m_pDate->dwDay++;

	return FALSE;
}
