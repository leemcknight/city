// Grid.cpp: implementation of the CGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "City.h"
#include "Grid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGrid::CGrid()
{
	m_pFirstCell = NULL;
	m_pZoneList = NULL;
	m_pLastUnchecked = NULL;
	m_pObjs = NULL;
}

CGrid::~CGrid()
{

}

/*
================================
==
==	m_BuildGrid()
==
==  creates a grid with dims
==  x,y. 
==
==  can only be called once.
==
=================================
*/
void CGrid::BuildGrid(long x, long y)
{
	if (!m_pFirstCell)
	{
		CGridCell *pCurCell = NULL;

		for (int i = 0; i <= y - 1; i++)
		{
			//build the row
			for (int j = 0; j <= x - 1; j++)
			{
				CGridCell *pCell = new CGridCell;
				pCell->x			= j;
				pCell->y			= i;
				pCell->dwZoneType	= ZT_NONE;
				pCell->SetObject( m_pObjs->pLot, TRUE, m_pObjs );
				
				if (!pCurCell)
				{
					pCurCell = pCell;
					m_pFirstCell = pCell;
				}

				else if (j == 0)
				{
					//first cell in row
					pCell->pTopCell = pCurCell;
					pCurCell->pBottomCell = pCell;

				} else {
					pCell->pLeftCell = pCurCell;
					pCurCell->pRightCell = pCell;
				}
				
				pCell->GetObject()->SetPic( IDB_LOT );
				if(pCurCell->pTopCell && pCurCell->pTopCell->pRightCell && j != 0)
				{
					pCell->pTopCell = pCurCell->pTopCell->pRightCell;
					pCell->pTopCell->pBottomCell = pCell;
				}

				pCurCell = pCell;
			
			}

			
			while(pCurCell->pLeftCell)
				pCurCell = pCurCell->pLeftCell;
				
		}
	}
}



/*
===============================
==
==	IsValidCellPos
==
==  returns :
==  TRUE - cell at x,y
==  FALSE - no cell at x,y
==
===============================
*/
bool CGrid::IsValidCellPos( long x, long y )
{
	CGridCell	*pTempCell = m_pFirstCell;

	for(int i = 0; i <= y; i ++)
	{
		pTempCell = pTempCell->pBottomCell;
		if (!pTempCell)
			return FALSE;
		
	}

	for(int j = 0; j <= x; j++)
	{
		pTempCell = pTempCell->pRightCell;
		if(!pTempCell)
			return FALSE;
	}

	return TRUE;

}

/*
===================================
==
==	SetObjectAtCell
==
==  params: x,y (loc of cell)
==		  *pObj (pointer to object)
==
==  places pObj at cell(x,y), if 
==  legal, and modifys surrounding
==  cells as need be.
==
===================================
*/
ERC CGrid::SetObjectAtCell(long x, long y, CCityObj* pObj)
{
	CGridCell *pTempCell;
	effect_t effect;
	RadiusNode_t*	pNode;
	
	pTempCell = MoveToCell(x,y);
	if(pTempCell)	//valid cell?
	{
		for(UINT i = 0; i <= pObj->GetDim1() - 1; i++)
		{
			if ( pTempCell )
			{
				for(UINT j = 0; j <= pObj->GetDim1() - 1; j++)
				{
					
					if( (pTempCell != NULL )  && ( pTempCell->IsBuildable() ) )
						pTempCell = pTempCell->pRightCell;
					else 
						return E_BUILDINGEXISTS;
				}

				pTempCell = MoveToCell( x, pTempCell->y );
				pTempCell = pTempCell->pBottomCell;
			} else 
				return E_BADCELL;
		}

		pTempCell = MoveToCell(x,y);
		if ( E_SUCCEEDED ( pTempCell->SetObject(pObj,TRUE, m_pObjs) ) ) 
		{
			effect = pObj->GetEffects();
			AddPollutionPoint( x, y, effect.dPollutionEffect );
			AddCrimePoint( x, y, effect.dCrimeEffect );
			AddLandValuePoint( x, y, effect.dLandValueEffect );

			RemoveZone(x, y);

			if (pObj == m_pObjs->pRes)
				InsertZone(x,y, ZT_RESIDENTIAL);
			else if (pObj == m_pObjs->pInd)
				InsertZone(x,y, ZT_INDUSTRIAL);
			else if (pObj == m_pObjs->pComm)
				InsertZone(x,y, ZT_COMMERCIAL);
			else if (pObj == m_pObjs->pCoalPP)
			{
				bool bDraw = true;
				for(UINT i = 0; i <= pObj->GetDim1() - 1; i++)
				{
					for(UINT j = 0; j <= pObj->GetDim1() - 1; j++)
					{
						pTempCell->SetObject(pObj,bDraw, m_pObjs);
						pTempCell = pTempCell->pRightCell;
						bDraw = false;
					}

					for(UINT j = 0; j<= pObj->GetDim1() - 1; j++)
						pTempCell = pTempCell->pLeftCell;

					pTempCell = pTempCell->pBottomCell;
					
				}
				//power the cells
				pNode = GetCellsInRadius(20,pTempCell);
				while(pNode)
				{
					pTempCell = GetCellAtPos( pNode->pCell->x, pNode->pCell->y );
					pTempCell->SetPowered();
					if( pNode->pNext )
					{
						pNode = pNode->pNext;
						delete pNode->pPrev->pCell;
						delete pNode->pPrev;
					} else {

						delete pNode->pCell;
						delete pNode;
						pNode = NULL;
					}
				}
			}
			
		} 	
	}
	else
		return E_BADCELL;
	
	return E_OK;

}

/*
===============================
==
==	MoveToCell()
==
==	returns a pointer to the
==	cell corresponding to the
==	coordinates x,y
==
==============================
*/
CGridCell* CGrid::MoveToCell(long x, long y)
{
	CGridCell	*pTempCell = m_pFirstCell;

	for(int i = 0; i <= y - 1 ; i ++)
	{
		pTempCell = pTempCell->pBottomCell;
		if (!pTempCell)
			return NULL;
		
	}

	for(int j = 0; j <= x - 1; j++)
	{
		pTempCell = pTempCell->pRightCell;
		if(!pTempCell)
			return NULL;
	}

	return pTempCell;
}

/*
========================================
==
==IsObjectAtCell()
==returns:
==	TRUE - any object at cell 
==			(including undeveloped zones)
==	FALSE - nothing at cell
==
=========================================
*/
bool CGrid::IsObjectAtCell(long x, long y)
{
	CGridCell	*pTempCell;

	pTempCell = MoveToCell(x,y);

	if (!pTempCell)
		return FALSE;

	if(pTempCell->GetObject() != m_pObjs->pLot)
		return TRUE;
	else	
		return FALSE;
}

void CGrid::init_objs(cityobjs_t* pCityObjs)
{
	if (NULL == m_pObjs)
		m_pObjs = pCityObjs;
}

/*
=============================
==
==	GetCellAtPos()
==
=============================
*/
CGridCell* CGrid::GetCellAtPos(long x, long y)
{
	CGridCell* pCell = MoveToCell(x,y);
	return pCell;
	
}

/*
====================================
==
==	GetMaxDims()
==
==	returns a (long) with the max grid
==	size a building can occupy using the
==	ref cell as the upper left cell of 
==	the building.
==
====================================
*/
long CGrid::GetMaxDims(CGridCell* pRefCell)
{
	CGridCell* pTempCell;
	bool	b_OK = TRUE;
	int	iCurDim;	//current dimension we're trying
	int i;
	int j;
	
	pTempCell = pRefCell;
	iCurDim = 2;
	while(b_OK)
	{
		for(j = 1; j <= iCurDim; j++)
		{
			for(i = 1; i <= iCurDim; i++)
			{
				if(!pTempCell)
					b_OK = FALSE;
				else {

					if (pTempCell->GetObject() != pRefCell->GetObject()) 
					{
						b_OK = FALSE;
					}
					pTempCell = pTempCell->pRightCell;
				}
				
			}
			pTempCell = GetCellAtPos(pRefCell->x,pTempCell->y);
			pTempCell = pTempCell->pBottomCell;
		}

		if (b_OK)
		{
			iCurDim++;
			pTempCell = pRefCell;
		}
	}

	return (iCurDim - 1);
	
}

/*
==================================
==
==	SetBuildingAtCell()
==
==	places at building at pos(x,y)
==	and all the cells within the 
==	building's dimensions.  
==	upper left cell is drawing cell.
==
==================================
*/
ERC CGrid::SetBuildingAtCell(long x, long y, CBuilding* pBuilding)
{
	int iX, iY;
	CGridCell* pCell;
	bool bFirstCell = TRUE;
	
	pCell = GetCellAtPos(x,y);
	iX = pBuilding->GetDim1();
	iY = pBuilding->GetDim2();

	for(int i = 1; i <= iY; i++)
	{
		for(int j = 1; j <= iX; j++)
		{
			if( E_FAILED ( pCell->SetBuilding(pBuilding,bFirstCell) ) )
				return FALSE;
			else {

				if((!m_pLastUnchecked) || (m_pLastUnchecked == GetZonePtr(pCell->x,pCell->y)))
					m_pLastUnchecked = GetZonePtr(pCell->x,pCell->y)->pNext;
				if ( E_FAILED ( RemoveZone(pCell->x, pCell->y)  )  )
					return E_NOZONE;
				pCell = pCell->pRightCell;
			}
			bFirstCell = FALSE;
		}
		pCell = MoveToCell(x,pCell->y);
		pCell = pCell->pBottomCell;
	}

	return E_OK;
}

/*
====================================
==
==	InsertZone()
==
==	adds a undeveloped zone on the
==	list of "buildable" zones. 
==
===================================
*/
zone_t* CGrid::InsertZone(long x, long y, DWORD dwZoneType)
{
	ZoneNode_t* pTemplist;
	ZoneNode_t* pReturnNode;

	// first see if the x,y coords already exist
	pReturnNode = GetZonePtr(x,y);
	if (!pReturnNode)
	{
		if (m_pZoneList == NULL)
		{
			m_pZoneList = new ZoneNode_t;
			m_pZoneList->pZone = new zone_t;
			m_pZoneList->pNext = NULL;
			m_pZoneList->pPrev = NULL;
			m_pZoneList->pZone->x = x;
			m_pZoneList->pZone->y = y;
			m_pZoneList->pZone->zone_type = dwZoneType;
			m_pLastUnchecked = m_pZoneList;
			return m_pZoneList->pZone;
		}
		
		else {

			pTemplist = m_pZoneList;
			
			
			while(pTemplist->pNext)
				pTemplist = pTemplist->pNext;

			ZoneNode_t* pNewList = new ZoneNode_t;
			pNewList->pZone = new zone_t;
			pNewList->pNext = NULL;
			pNewList->pPrev = pTemplist;

			pTemplist->pNext = pNewList;
			pNewList->pZone->x = x;
			pNewList->pZone->y = y;
			pNewList->pZone->zone_type = dwZoneType;			
			return pNewList->pZone;
		}
	}
	else
		return pReturnNode->pZone;
}



/*
=================================
==
==	RemoveZone()
==
==  removes the zone (x,y) from
==  the available pool of 
==  "buildable" zones
==
=================================
*/
ERC CGrid::RemoveZone(long x, long y)
{
	ZoneNode_t* pTemplist = m_pZoneList;
	
	if(pTemplist)
	{
		pTemplist = GetZonePtr(x,y);
		
		if (!pTemplist)
			return E_NOZONE;


		if((pTemplist->pNext == NULL) && (pTemplist->pPrev == NULL))
		{
			//only zone in the list.
			m_pZoneList = NULL;
			delete pTemplist->pZone;
			delete pTemplist;

		} else {
		
			if(pTemplist->pPrev)
				pTemplist->pPrev->pNext = pTemplist->pNext;

			else {
				//removing first in list
				pTemplist->pNext->pPrev = NULL;
				m_pZoneList = pTemplist->pNext;	
			}

			if(pTemplist->pNext)
				pTemplist->pNext->pPrev = pTemplist->pPrev;
			 else 
				pTemplist->pPrev->pNext = NULL;
			delete pTemplist->pZone;
			delete pTemplist;

		}

		return E_OK;
	}

	return E_NOZONE;
}

/*
================================
==
==	GetZonePtr()
==
==  returns a pointer to the zone
==  in the list corresponding 
==  to the coords(x,y)
==
================================
*/
ZoneNode_t* CGrid::GetZonePtr(long x, long y) const 
{
	ZoneNode_t* pRetList;

	pRetList = m_pZoneList;
	while((pRetList) && ((pRetList->pZone->x != x) || (pRetList->pZone->y !=y)))
		pRetList = pRetList->pNext;
		
	return pRetList;
}

/*
======================================
==
==	AddPollutionPoint()
==
==	given an x,y cell and a 
==	pollution index, modifies
==	the pollution property of 
==	all surrounding cells
==
=======================================
*/
void CGrid::AddPollutionPoint(long x, long y, double dblPollutionLevel)
{
	CGridCell* pCell = NULL;
	RadiusNode_t*	pNode;
	RadiusNode_t*	pFirstNode;
	double			dRad;
	double			dblPollution;
	long			lNodes = 0;
	long			lDeletedNodes = 0;

	//figure out the radius of the affected area.
	dRad = dblPollutionLevel/20;
	
	//get the cells in the radius
	pCell = GetCellAtPos( x, y );
	
	pNode = pFirstNode = GetCellsInRadius( abs( ( long )dRad ), pCell );
	
	while(pNode)
	{
		pCell = GetCellAtPos( pNode->pCell->x, pNode->pCell->y );
		dblPollution =  dblPollutionLevel - ( dblPollutionLevel * (pNode->pCell->Dist/dRad) );
		pCell->DeltaPollution( dblPollution );
		pNode = pNode->pNext;
		lNodes++;
	}

	lDeletedNodes = DoRadiusDelete( pFirstNode );

}

/*
============================================
==
==	AddCrimePoint()
==
============================================
*/
void CGrid::AddCrimePoint(long x, long y, double dblCrimeLevel)
{
	CGridCell* pCell = NULL;
	RadiusNode_t*	pNode;
	RadiusNode_t*	pFirstNode;
	double			dRad;
	double			dblCrime;
	long			lNodes = 0;
	long			lDeletedNodes = 0;

	//figure out the radius of the affected area.
	dRad = dblCrimeLevel/20;
	
	//get the cells in the radius
	pCell = GetCellAtPos( x, y );
	
	pNode = pFirstNode =  GetCellsInRadius( abs( ( long )dRad  ), pCell);
	
	while(pNode)
	{
		pCell = GetCellAtPos( pNode->pCell->x, pNode->pCell->y );
		dblCrime =  dblCrime  - (dblCrime * (pNode->pCell->Dist/dRad) );
		pCell->DeltaCrime( dblCrime );
		pNode = pNode->pNext;
		lNodes++;
	}

	lDeletedNodes = DoRadiusDelete( pFirstNode );

}

/*
==============================================
==
==	AddLandValuePoint()
==
==============================================
*/
void CGrid::AddLandValuePoint(long x, long y, double dblLandValueLevel)
{
	CGridCell* pCell = NULL;
	RadiusNode_t*	pNode;
	RadiusNode_t*	pFirstNode;
	double			dRad;
	double			dblLandValue;
	long			lNodes = 0;
	long			lDeletedNodes = 0;

	//figure out the radius of the affected area.
	dRad = dblLandValueLevel/20;
	
	//get the cells in the radius
	pCell = GetCellAtPos( x, y );
	
	pFirstNode = pNode = GetCellsInRadius( abs( ( long )dRad  ), pCell);
	
	while(pNode)
	{
		pCell = GetCellAtPos( pNode->pCell->x, pNode->pCell->y );
		dblLandValue =  dblLandValue  - (pNode->pCell->Dist/dRad);
		pCell->DeltaLandValue( dblLandValue );
		pNode = pNode->pNext;
		lNodes++;
	}

	lDeletedNodes = DoRadiusDelete( pFirstNode );

	if( lDeletedNodes != lNodes )
		lDeletedNodes = lDeletedNodes;
}


/*
=====================================
==
==	GetCellsInRadius()
==
======================================
*/
RadiusNode_t* CGrid::GetCellsInRadius(long lRadius, CGridCell* pCell)
{
	RadiusNode_t* pNode = NULL;
	CGridCell*	  pRadiusCell = NULL;
	
	if(lRadius == 0)
		return NULL;

	pNode = GetCellsAtQuadrant(QUAD_UPPERLEFT, pNode, pCell, lRadius);
	pNode = GetCellsAtQuadrant(QUAD_UPPERRIGHT, pNode, pCell, lRadius);
	pNode = GetCellsAtQuadrant(QUAD_LOWERLEFT, pNode, pCell, lRadius);
	pNode = GetCellsAtQuadrant(QUAD_LOWERRIGHT, pNode, pCell, lRadius);

	//move pointer to beginning of list
	while(pNode && pNode->pPrev)
		pNode = pNode->pPrev;

	return pNode;

}


/*
===================
==
==	AddRadiusCell()
==	in: a node in the list
==		to add the new node to
==
==	out: pointer to the new node
===================
*/
RadiusNode_t* CGrid::AddRadiusCell(RadiusNode_t* pNode)
{

	RadiusNode_t*	pNewNode;

	pNewNode = new RadiusNode_t;
	pNewNode->pNext = NULL;
	pNewNode->pCell = new CellRadius_t;

	if(pNode)
	{
		while(pNode->pNext)
			pNode = pNode->pNext;
		pNode->pNext = pNewNode;
		pNode->pNext->pPrev = pNode;
		pNode = pNode->pNext;
		
	} else {

		pNode = pNewNode;
		pNode->pPrev = NULL;
	}

	return pNode;
}


/*
=======================
==
==	GetCellsAtQuadrant()
==
=======================
*/
RadiusNode_t* CGrid::GetCellsAtQuadrant(QUADRANT quad, RadiusNode_t* pNode, CGridCell* pCell, long lRadius)
{
	CGridCell* pRadiusCell = pCell;

	for( int nYoffset = 0; nYoffset <= (lRadius - 1); nYoffset++ )
	{
		for (int nXoffset = 0; nXoffset <= (lRadius -1); nXoffset++ )
		{
			if( nYoffset || nXoffset )
			{
				if (HYP( nYoffset, nXoffset ) <= lRadius)
				{
					pNode = AddRadiusCell( pNode );
					pNode->pCell->Dist = HYP( nYoffset, nXoffset );
					pNode->pCell->x = pRadiusCell->x;
					pNode->pCell->y = pRadiusCell->y;
				}
			}
			if ( RIGHTQUAD( quad ) )
			{
				if (pRadiusCell->pRightCell)
					pRadiusCell = pRadiusCell->pRightCell;
				else
					break;
			} else {

				if(pRadiusCell->pLeftCell)
					pRadiusCell = pRadiusCell->pLeftCell;
				else
					break;
			}
		}
		pRadiusCell = GetCellAtPos( pCell->x,pRadiusCell->y );

		if( UPPERQUAD( quad ) )
		{
			if( pRadiusCell->pTopCell )
				pRadiusCell = pRadiusCell->pTopCell;
			else
				break;
		} else {
			if( pRadiusCell->pBottomCell )
				pRadiusCell = pRadiusCell->pBottomCell;
			else
				break;
		}
		
	}	

	return pNode;
}


/*
==============================
==
==	DoRadiusDelete()
== 
==	for debugging purposes, 
==	returns the number of 
==	deleted nodes.  If there's
==	a memory leak, chances are
==	this isn't being called
==	when it's supposed to!
==
==============================
*/
long CGrid::DoRadiusDelete( RadiusNode_t* pNode )
{
	long n = 0;

	if (!pNode)
		return n;

	while(pNode->pPrev)
		pNode = pNode->pPrev;

	while ( pNode )
	{
		if ( pNode->pNext )
		{
			pNode = pNode->pNext;
			delete pNode->pPrev->pCell;
			delete pNode->pPrev;
			n++;
		} else {
			delete pNode->pCell;
			delete pNode;
			pNode = NULL;
			n++;
		}
	}

	return n;
}