// GridCell.h: interface for the CGridCell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELL_H__6AB78D88_4FAA_11D5_8D63_00B0D081587C__INCLUDED_)
#define AFX_GRIDCELL_H__6AB78D88_4FAA_11D5_8D63_00B0D081587C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CityObj.h"
#include "Building.h"

class CGridCell  
{
public:
	CGridCell();
	virtual ~CGridCell();

	CCityObj	*GetObject( void )	const		{return m_pCellObj;}
	bool		IsDrawingCell( void ) const		{return m_bIsDrawingCell;}
	bool		IsBuildable( void ) const		{return m_bIsBuildable;}
	CELLSTAT	GetCellStat( void ) const		{return m_pCS;}

	//////////////
	// Power
	//
	void		SetPowered();			
	void		SetUnPowered();

	ERC			SetObject(CCityObj* pObj, bool bDrawnCell, cityobjs_t* pCityObjs);
	ERC			SetBuilding(CBuilding* pBuilding, bool bDrawnCell);

	//////////////
	// Pollution
	//
	void		DeltaPollution( double dblPollution ) { m_pCS.dPollution += dblPollution; }
	double		GetPollution( void ) { return m_pCS.dPollution; }

	//////////////
	// Crime
	//
	void		DeltaCrime( double dblCrime ) { m_pCS.dCrime += dblCrime; }
	double		GetCrime( void ) { return m_pCS.dCrime; }
	
	///////////////
	// LandValue
	//
	void		DeltaLandValue( double dblLandValue );
	double		GetLandValue( ) {return m_dblLandValue;}

	//////////////
	// Pics
	//
	UINT		GetPic( void ) {return m_pCellObj->GetPic();}
	void		UpdateRoadPic(cityobjs_t* pObjs, bool bRecursiveCall);
	
	bool		IsRoad(CCityObj* pObj, cityobjs_t* pObjs);

	CGridCell	*pTopCell;
	CGridCell	*pBottomCell;
	CGridCell	*pLeftCell;
	CGridCell	*pRightCell;

	DWORD		dwZoneType;

	long		x;
	long		y;
	
private:
	//
	//InternalModify() is used for 
	//changing road structures, and 
	//cannot be called by other classes.
	
	void		InternalModify(CCityObj* pObj) { m_pCellObj = pObj;}

	CCityObj	*m_pCellObj;
	bool		m_bIsDrawingCell;
	bool		m_bIsBuilding;
	bool		m_bIsBuildable;
	CELLSTAT	m_pCS;
	double		m_dblLandValue;
	
};

#endif // !defined(AFX_GRIDCELL_H__6AB78D88_4FAA_11D5_8D63_00B0D081587C__INCLUDED_)
