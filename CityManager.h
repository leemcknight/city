// CityManager.h: interface for the CCityManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CITYMANAGER_H__6AB78D86_4FAA_11D5_8D63_00B0D081587C__INCLUDED_)
#define AFX_CITYMANAGER_H__6AB78D86_4FAA_11D5_8D63_00B0D081587C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Grid.h"
#include "City_Econ.h"
#include "CityDate.h"

class CCityManager  
{
public:
	CCityManager();
	virtual			~CCityManager();

	/////////////////////////////////////////////////////////////////////////
	//
	//	ACCESSOR FUNCTIONS
	CGrid			*GetGrid( void )		{return m_pGrid;}
	citydate_t*		GetDate( void )			{return m_pCityDate->GetDate();}
	DWORD			GetFunds( void )		{return m_pEcon->GetFunds();}
	DWORD			GetPopulation( void )	{return m_dwPopulation;}
	RCI				GetRCI( void ) const	{return m_RCIStatus;}


	ERC				Initialize( void );
	cityobjs_t		*pCityObjs;
	ERC				SetObjectAtCell(long x, long y, CCityObj *pObj);
	ZoneNode_t*		DevelopZones( void );
	
	void			IncrementDate( void );
	
private:
	//////////////////////////////////////////
	//
	//		FUNCTIONS
	//
	//////////////////////////////////////////
	void			AssignBuildingToZone( zone_t* pZone );
	void			AddBuildingToList( BuildingNode_t* pList, UINT pic, short size, long Capacity, UINT type);
	BuildingNode_t*	GetBuildingListForZone( zone_t* pZone );
	bool			bDevelop( zone_t* pZone );
	void			CalcRCI( void );
	long			GetNeedForZone( zone_t* pZone );

	/////////////////////////////////////////
	//
	//		VARIABLES
	//
	/////////////////////////////////////////
	CGrid			*m_pGrid;				//pointer to the Grid
	CCity_Econ		*m_pEcon;				//City Economy
	CCityDate		*m_pCityDate;			//City Date
	DWORD			m_dwPopulation;			//population (aka Residential Capacity)
	DWORD			m_dwIndCapacity;		//Industrial Capacity
	DWORD			m_dwComCapacity;		//Commercial Capacity
	RCI				m_RCIStatus;
	////////////////////////////////////////////
	//These variables contain pointers to 
	//lists of buildings for each zone type.
	//They are sorted from least density, low value 
	//to highest density, highest value.
	BUILDING_NODE*	m_pResList;
	BUILDING_NODE*	m_pIndList;
	BUILDING_NODE*	m_pComList;

};

#endif // !defined(AFX_CITYMANAGER_H__6AB78D86_4FAA_11D5_8D63_00B0D081587C__INCLUDED_)
