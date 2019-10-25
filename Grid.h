// Grid.h: interface for the CGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRID_H__6AB78D87_4FAA_11D5_8D63_00B0D081587C__INCLUDED_)
#define AFX_GRID_H__6AB78D87_4FAA_11D5_8D63_00B0D081587C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCell.h"

class CGrid  
{
public:
	CGrid();
	virtual		~CGrid();


	CGridCell*	GetFirstCell( void )		{return m_pFirstCell;}
	ZONE_NODE*	GetZoneList()				{return m_pZoneList;}
	ZONE_NODE*	GetLastUnchecked()			{return m_pLastUnchecked;}
	void		ResetLastUnchecked(void)	{m_pLastUnchecked=NULL;}

	void			BuildGrid( long x, long y );
	bool			IsValidCellPos( long x, long y );
	ERC				SetObjectAtCell(long x, long y, CCityObj* pObj);
	bool			IsObjectAtCell(long x, long y);
	void			init_objs(cityobjs_t* pCityObjs);
	CGridCell*		GetCellAtPos(long x, long y);
	long			GetMaxDims(CGridCell* pRefCell);
	ERC				SetBuildingAtCell(long x, long y, CBuilding* pBuilding);
	ERC				RemoveZone(long x, long y);
	void			AddPollutionPoint(long x, long y, double dblPollutionLevel);
	void			AddCrimePoint(long x, long y, double dblCrimeLevel);
	void			AddLandValuePoint(long x, long y, double dblLandValueLevel);
	RadiusNode_t*	GetCellsInRadius(long lRadius, CGridCell* pCell);
	long			DoRadiusDelete( RadiusNode_t* pNode );
	
private:
	
	CGridCell*		MoveToCell(long x, long y);
	ZONE*			InsertZone(long x, long y, DWORD dwZoneType);
	ZONE_NODE*		GetZonePtr(long x, long y) const;
	RadiusNode_t*	AddRadiusCell(RadiusNode_t* pNode);
	RadiusNode_t*	GetCellsAtQuadrant(QUADRANT quad, RadiusNode_t* pNode, CGridCell* pCell, long lRadius);
	

	CGridCell	*m_pFirstCell;
	cityobjs_t	*m_pObjs;
	ZONE_NODE	*m_pZoneList;

	/*
		This is a pointer to the last "unchecked" cell in zone list.
		It's needed becuase the zone list is continually having
		zones removed from it, and this pointer always points
		to the last zone unchecked.  Needed because CCityManager
		has no way of knowing where in the list it needs to be, since
		it's not responsible for removing zones form pZoneList.
	*/

	ZONE_NODE	*m_pLastUnchecked;		

};

#endif // !defined(AFX_GRID_H__6AB78D87_4FAA_11D5_8D63_00B0D081587C__INCLUDED_)
