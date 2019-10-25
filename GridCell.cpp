// GridCell.cpp: implementation of the CGridCell class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "City.h"
#include "GridCell.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridCell::CGridCell()
{
	//init cells around 
	pBottomCell = NULL;
	pLeftCell = NULL;
	pRightCell = NULL;
	pTopCell = NULL;
	m_pCellObj = NULL;
	m_bIsDrawingCell = TRUE;
	m_bIsBuilding	= FALSE;
	m_bIsBuildable =	TRUE;
	dwZoneType = ZT_NONE;

	m_pCS.bIsPowered	= FALSE;
	m_pCS.dCrime		= 0;
	m_pCS.dwLandValue	= LV_LOW;
	m_pCS.dPollution	= 0;
	
		
}

CGridCell::~CGridCell()
{

}

/*
========================
=
=	SetObject()
=
========================
*/
ERC CGridCell::SetObject(CCityObj* pObj, bool bDrawnCell, cityobjs_t *pCityObjs)
{
	if((m_pCellObj == pCityObjs->pRes) ||
		(m_pCellObj == pCityObjs->pInd) ||
		(m_pCellObj == pCityObjs->pComm) ||
		(m_pCellObj == pCityObjs->pLot) || 
		(m_pCellObj == NULL))
	{
		m_pCellObj = pObj;
		m_bIsDrawingCell = bDrawnCell;

		if (pObj == pCityObjs->pComm)
			dwZoneType = ZT_COMMERCIAL;
		else if (pObj == pCityObjs->pInd)
			dwZoneType = ZT_INDUSTRIAL;
		else if (pObj == pCityObjs->pRes)
			dwZoneType = ZT_RESIDENTIAL;
		else
			dwZoneType = ZT_NONE;

		if( IsRoad( pObj, pCityObjs ) )
			UpdateRoadPic(pCityObjs, FALSE);

		if((pObj == pCityObjs->pRes) ||
			(pObj == pCityObjs->pInd) ||
			(pObj == pCityObjs->pComm) ||
			(pObj == pCityObjs->pLot))
			return E_OK;
		else {
			m_bIsBuildable = FALSE;
			return E_OK;
		}
	}
	else 
		return E_BUILDINGEXISTS;
	
}


/*
===========================
=
=SetBuilding()
=
===========================
*/
ERC CGridCell::SetBuilding(CBuilding* pNewBuilding, bool bDrawnCell)
{
	if(m_bIsBuilding)
		return E_BUILDINGEXISTS;
	else {
		m_bIsBuilding = TRUE;
		m_pCellObj = pNewBuilding;
		m_bIsDrawingCell = bDrawnCell;
		m_bIsBuildable = FALSE;
		return E_OK;
	}

}

/*
======================================
==
==SetPowered()
==
======================================
*/
void CGridCell::SetPowered( void )
{
	m_pCS.bIsPowered = TRUE;
}

/*
=======================================
==
==SetUnPowered()
==
======================================
*/
void CGridCell::SetUnPowered( void )
{
	m_pCS.bIsPowered = FALSE;
}


/*
========================================
==
==	DeltaLandValue()
==
========================================
*/
void CGridCell::DeltaLandValue( double dblLandValue )
{
	m_dblLandValue += dblLandValue;
	
	if (m_dblLandValue < 20)
		m_pCS.dwLandValue = LV_LOW;
	else if (m_dblLandValue < 50)
		m_pCS.dwLandValue = LV_MEDIUM;
	else
		m_pCS.dwLandValue = LV_HIGH;
}

/*
==========================================
==
==	UpdateRoadPic()
==
==========================================
*/
void CGridCell::UpdateRoadPic(cityobjs_t* pObjs, bool bRecursiveCall)
{
	DWORD	dwRoad = 0;
	bool	bChanged = !bRecursiveCall;
	
	if ( IsRoad( m_pCellObj, pObjs ) )
	{

		if ( pTopCell && IsRoad( pTopCell->GetObject(), pObjs) )
			dwRoad |= RC_NORTH;
		if ( pBottomCell && IsRoad( pBottomCell->GetObject(), pObjs) )
			dwRoad |= RC_SOUTH;
		if ( pRightCell && IsRoad( pRightCell->GetObject(), pObjs) )
			dwRoad |= RC_EAST;
		if ( pLeftCell && IsRoad( pLeftCell->GetObject(), pObjs) )
			dwRoad |= RC_WEST;


		if(NW_ROAD( dwRoad ) && EW_ROAD( dwRoad ) )
		{
			if( m_pCellObj != pObjs->pIntersection )
			{
				m_pCellObj = pObjs->pIntersection;
				bChanged = TRUE;
			}
		}
		else if (EW_ROAD( dwRoad ) ) 	
		{
			if( m_pCellObj != pObjs->pEWRoad )
			{
				m_pCellObj = pObjs->pEWRoad;
				bChanged = TRUE;
			}
		}

		if( bChanged )
		{
			pTopCell->UpdateRoadPic( pObjs, TRUE );
			pBottomCell->UpdateRoadPic( pObjs, TRUE );
			pRightCell->UpdateRoadPic( pObjs, TRUE );
			pLeftCell->UpdateRoadPic( pObjs, TRUE );
		}

	}
	
}

/*
==========================================
==
==	IsRoad()
==
==========================================
*/
bool CGridCell::IsRoad(CCityObj* pObj, cityobjs_t* pObjs)
{
	if(pObj == pObjs->pIntersection)
		return TRUE;
	else if (pObj == pObjs->pNSRoad)
		return TRUE;
	else if (pObj == pObjs->pEWRoad)
		return TRUE;
	return FALSE;
}




