// CityManager.cpp: implementation of the CCityManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "City.h"
#include "CityManager.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCityManager::CCityManager()
{
}

CCityManager::~CCityManager()
{

}

void CCityManager::IncrementDate( void )
{
	if (m_pCityDate->IncrementDate())
		m_pEcon->CollectTaxes(m_dwPopulation,m_dwComCapacity,m_dwIndCapacity);

}


ERC CCityManager::Initialize(void)
{
	
	//////////////////////////////
	//city objs
	//
	pCityObjs = new cityobjs_t;

	pCityObjs->pEWRoad = new CCityObj;
	pCityObjs->pNSRoad = new CCityObj;
	pCityObjs->pIntersection = new CCityObj;
	pCityObjs->pRes	= new CCityObj;
	pCityObjs->pComm = new CCityObj;
	pCityObjs->pInd = new CCityObj;
	pCityObjs->pCoalPP = new CCityObj;
	pCityObjs->pLot = new CCityObj;

	pCityObjs->pInd->SetInitialCost(200);
	pCityObjs->pRes->SetInitialCost(200);
	pCityObjs->pComm->SetInitialCost(200);
	pCityObjs->pNSRoad->SetInitialCost(50);
	pCityObjs->pCoalPP->SetInitialCost(5000);

	pCityObjs->pCoalPP->SetPic( IDB_POWERPLANT_COAL );
	pCityObjs->pNSRoad->SetPic( IDB_ROAD_1);
	pCityObjs->pEWRoad->SetPic( IDB_ROAD_2);
	pCityObjs->pIntersection->SetPic( IDB_ROAD_3 );
	pCityObjs->pRes->SetPic( IDB_RES_ZONE );
	pCityObjs->pComm->SetPic( IDB_COMM_ZONE );
	pCityObjs->pInd->SetPic( IDB_IND_ZONE );

	effect_t	effect;
	effect.dCrimeEffect = CC_IND;
	effect.dLandValueEffect = LVC_IND;
	effect.dPollutionEffect = PC_IND;
	pCityObjs->pInd->SetEffects( effect );

	effect.dCrimeEffect = CC_RES;
	effect.dLandValueEffect = LVC_RES;
	effect.dPollutionEffect = PC_RES;
	pCityObjs->pRes->SetEffects( effect );
	
	effect.dCrimeEffect = CC_COM;
	effect.dLandValueEffect = LVC_COM;
	effect.dPollutionEffect = PC_COM;
	pCityObjs->pComm->SetEffects( effect );
	
	effect.dCrimeEffect = CC_ROAD;
	effect.dLandValueEffect = LVC_ROAD;
	effect.dPollutionEffect = PC_ROAD;
	pCityObjs->pNSRoad->SetEffects( effect );
	pCityObjs->pEWRoad->SetEffects( effect );
	pCityObjs->pIntersection->SetEffects( effect );
	
	effect.dCrimeEffect = CC_COALPOWER;
	effect.dLandValueEffect = LVC_COALPOWER;
	effect.dPollutionEffect = PC_COALPOWER;
	pCityObjs->pCoalPP->SetEffects( effect );
	
	
	//////////////////////////
	//grid
	//
	m_pGrid = new CGrid;

	m_pGrid->init_objs(pCityObjs);
	m_pGrid->BuildGrid(50,50);
	
	pCityObjs->pCoalPP->SetDim1( 3 );
	pCityObjs->pCoalPP->SetDim2( 3 );

	//////////////////////////////
	//econ
	//
	m_pEcon = new CCity_Econ;
	m_pEcon->DoTransact(50000);

	///////////////////////////
	//date
	//
	m_pCityDate = new CCityDate;

	//////////////////////////////
	//zone needs
	//
	m_RCIStatus.wCom = 100;
	m_RCIStatus.wInd = 100;
	m_RCIStatus.wRes = 100;
	
	////////////////////////////////
	//population
	//
	m_dwPopulation = 0;
	m_dwIndCapacity = 0;
	m_dwComCapacity = 0;

	/////////////////////////////////
	//buildings
	m_pResList = new BuildingNode_t;
	m_pIndList = new BuildingNode_t;
	m_pComList = new BuildingNode_t;

	m_pResList->pBuilding = new CBuilding;
	
	m_pResList->pBuilding->SetPic( IDB_HOUSE_1 );
	m_pResList->pBuilding->SetCapacity( 7 );
	m_pResList->pBuilding->SetBuildingType( BC_LOW_CHEAP );
	m_pResList->pBuilding->SetDim1( 1 );
	m_pResList->pBuilding->SetDim2( 1 );
	m_pResList->pNext = NULL;

	AddBuildingToList(m_pResList,IDB_HOUSE_2,1,7,0x0000);
	AddBuildingToList(m_pResList,IDB_CONDO_1,2,150,0x0100);
	AddBuildingToList(m_pResList,IDB_APARTMENT_1,3,1000,0x1000);
	
	m_pIndList->pBuilding = new CBuilding;
	m_pIndList->pBuilding->SetPic( IDB_FACTORY_1 );
	m_pIndList->pBuilding->SetCapacity( 50 );
	m_pIndList->pBuilding->SetBuildingType( BC_LOW_CHEAP );
	m_pIndList->pBuilding->SetDim1( 1 );
	m_pIndList->pBuilding->SetDim2( 1 );
	m_pIndList->pNext = NULL;
	

	m_pComList->pBuilding = new CBuilding;
	m_pComList->pBuilding->SetPic( IDB_STORE_1 );
	m_pComList->pBuilding->SetCapacity( 100 );
	m_pComList->pBuilding->SetBuildingType( BC_LOW_CHEAP );
	m_pComList->pBuilding->SetDim1( 1 );
	m_pComList->pBuilding->SetDim2( 1 );
	m_pComList->pNext = NULL;

	AddBuildingToList(m_pComList,IDB_BUSINESS_1,2, 200, 0x0100);
	AddBuildingToList(m_pComList,IDB_HIRISE_1,3, 200, 0x1000);
	
	return E_OK;
}




/*
==============================
==
==	SetObjectAtCell()
==
==  Does a little validation
==  and funds reduction before
==  passing the object to the
==  CGrid
==
===============================
*/
ERC CCityManager::SetObjectAtCell(long x, long y, CCityObj* pObj)
{
	long lCost = 0;
	ZONE *pZone = NULL;
	ERC	erc;
	
	lCost = pObj->GetInitialCost();

	if(lCost <= m_pEcon->GetFunds())
	{
		if (E_SUCCEEDED( erc = m_pGrid->SetObjectAtCell(x,y,pObj) ) )
		{
			m_pEcon->DoTransact(0 - pObj->GetInitialCost());
			CalcRCI();
			return E_OK;
		} else
			return ( erc );
	}
	else
		return E_NOFUNDS;
}


/*
==========================================
==
==AssignBuildingToZone()
==
==  takes a zone_t
==  and finds the best building to build
==  there based on land value, population,
==  and area to work with.
==
===========================================
*/
void CCityManager::AssignBuildingToZone(zone_t* pZone)
{
	BuildingNode_t* pFirst;
	BuildingNode_t* pCopy;
	CGridCell* pCell;
	UINT	uDensity;
	UINT	uFinal;
	long	lCount = 0;
	int		iRand;
	long	lMaxDim;

	
	pCell = m_pGrid->GetCellAtPos( pZone->x, pZone->y );
	lMaxDim = m_pGrid->GetMaxDims(pCell);
	pFirst = GetBuildingListForZone( pZone );
	pCopy = pFirst;
	
	if ((m_dwPopulation >= TH_HIGH) && (lMaxDim >= 3))
		uDensity = 0x1000;		
	else if ((m_dwPopulation >= TH_MEDIUM) && (lMaxDim >= 2))
		uDensity = 0x0100;
	else
		uDensity = 0;

	uFinal = uDensity | pCell->GetCellStat().dwLandValue;

	//find the first corresponding building type
	while(pCopy->pNext && (pCopy->pBuilding->GetBuildingType() != uFinal))
		pCopy = pCopy->pNext;

	if(pCopy)
	{
		pFirst = pCopy;	//placeholder for first building type
		
		while(pCopy && (pCopy->pBuilding->GetBuildingType() == uFinal))
		{
			lCount++;
			pCopy = pCopy->pNext;
		}

		//now we have a count of the number of buildings in the 
		//list of that "type".  Pick a random one.

		if(lCount > 0)
		{
			srand(time(NULL));
			iRand = rand()%lCount;
		}

		pCopy = pFirst;	//reset the copy to the first building of that type
		
		if(iRand > 0)
		{
			for(int i = 0; i <= iRand - 1; i++)
				pCopy = pCopy->pNext;
		}

		m_pGrid->SetBuildingAtCell(pCell->x, pCell->y, pCopy->pBuilding);		

		//update capacities
		switch( pCell->dwZoneType )
		{
			case ZT_COMMERCIAL:
				m_dwComCapacity += pCopy->pBuilding->GetCapacity();
				break;
			case ZT_RESIDENTIAL:
				srand(time(NULL));
				m_dwPopulation += rand()%pCopy->pBuilding->GetCapacity();
				break;
			case ZT_INDUSTRIAL:
				m_dwIndCapacity += pCopy->pBuilding->GetCapacity();
				break;
		}
		
	}
	
}

/*
=================================
==
==	bDevelop()
==
==  checks certain base conditions
==  for developing a zone. 
==  returns TRUE if zone can develop
==  FALSE otherwise
==
==================================
*/
bool CCityManager::bDevelop(  zone_t* pZone  )
{
	CGridCell*		pCell;
	RadiusNode_t*	pRadiusNode;
	RadiusNode_t*	pNodeCopy;		//save a copy for deletion
	cellstat_t		cs;
	bool			bRoad = FALSE;
	long			lNeed;
	long			lIDX = 0;
	long			lRand;
	
	
	pCell = m_pGrid->GetCellAtPos( pZone->x, pZone->y );

	lNeed = GetNeedForZone( pZone );
	cs = pCell->GetCellStat();
	
	//power
	if ( FALSE == cs.bIsPowered )
		return FALSE;

	//roads
	pRadiusNode = pNodeCopy =  m_pGrid->GetCellsInRadius( 4, pCell );
	while( pRadiusNode && !bRoad )
	{
		pCell = m_pGrid->GetCellAtPos( pRadiusNode->pCell->x,
										   pRadiusNode->pCell->y );

		if( pCell->IsRoad( pCell->GetObject(), pCityObjs ) )
			bRoad = true;
		pRadiusNode = pRadiusNode->pNext;
	}

	m_pGrid->DoRadiusDelete( pNodeCopy );
	if ( !bRoad )
		return FALSE;		//no roads. stop right here.
	
	//if it's industry, we don't 
	//care about pollution.
	if( pZone->zone_type != ZT_INDUSTRIAL )
		lIDX +=  ( long )cs.dPollution;
	
	lIDX += ( long )cs.dCrime;
	
	//lIDX now contains the "bad" index.
	lIDX += (120 - lNeed) ;
	
	if (lIDX == 0)
		return TRUE;	//nothing bad here, and 100 Need!

	if ((lNeed <= 75) && (lIDX >= 100))
		return FALSE;		//not enough need to warrant developing

	srand( time( NULL ) );		//see if the zone can develop
	lRand = rand()%lIDX;

	if(lRand >= 20)
		return FALSE;

	return TRUE;				//can be developed.
}

/*
===================================
==
==	AddBuildingToList()
==
==  Called during init to add all the
==  building object to the appropriate 
==  lists.
==
===================================
*/
void CCityManager::AddBuildingToList( BuildingNode_t* pNode, UINT pic,
									short size, long Capacity, UINT type )
{
	while(pNode->pNext)
		pNode = pNode->pNext;

	pNode->pNext = new BuildingNode_t;
	pNode->pNext->pPrev = pNode;
	pNode = pNode->pNext;
	pNode->pBuilding = new CBuilding;
	pNode->pBuilding->SetPic( pic );
	pNode->pBuilding->SetCapacity( Capacity );
	pNode->pBuilding->SetBuildingType( type );
	pNode->pBuilding->SetDim1( size );
	pNode->pBuilding->SetDim2( size );
	pNode->pNext = NULL;
}

/*
======================================
==
==	DevelopZones()
==
======================================
*/
ZoneNode_t* CCityManager::DevelopZones( void )
{
	ZoneNode_t*		pUpdateNode = NULL;					//pointer to the first node to update
	ZoneNode_t*		pZoneNode = m_pGrid->GetZoneList();	//current zone node we're checking
	ZoneNode_t*		pFirstNode = NULL;					//pointer to the first zone node
	CGridCell*		pCell;	
	BOOL			bMove = TRUE;
	
	CalcRCI();

	while(pZoneNode)
	{
		pCell = m_pGrid->GetCellAtPos(pZoneNode->pZone->x,pZoneNode->pZone->y);
		bMove = TRUE;

		if( bDevelop( pZoneNode->pZone ) )
		{			
			AssignBuildingToZone( pZoneNode->pZone );
			if(pUpdateNode == NULL)
			{
				pUpdateNode = new ZoneNode_t;
				pFirstNode = pUpdateNode;	//set the first node ptr

				//no need to call initzone() on this zone_t, since
				//all the caller cares about is the x,y pos.
				pUpdateNode->pZone = new zone_t;	
				pUpdateNode->pZone->x = pCell->x;
				pUpdateNode->pZone->y = pCell->y;
				pUpdateNode->pPrev = NULL;
				
			} else {
				
				pUpdateNode->pNext = new ZoneNode_t;
				pUpdateNode->pNext->pZone = new zone_t;
				pUpdateNode->pNext->pPrev = pUpdateNode;
				pUpdateNode->pNext->pZone->x = pCell->x;
				pUpdateNode->pNext->pZone->y = pCell->y;
				pUpdateNode = pUpdateNode->pNext;
			}
			
			pUpdateNode->pNext = NULL;
			pZoneNode = m_pGrid->GetLastUnchecked();
			m_pGrid->ResetLastUnchecked();	
			CalcRCI();
			bMove = FALSE;					
		}

		if(pZoneNode && bMove)
			pZoneNode = pZoneNode->pNext;
	}
	return pFirstNode;
}

/*
====================================
==
==CalcRCI()
==
====================================
*/
void CCityManager::CalcRCI()
{
	int		iResCalc = 0;
	int		iComCalc = 0;
	int		iIndCalc = 0;
	double	dblIndPerc = 0;
	double	dblComPerc = 0;
	double	dblTemp	 = 0.0f;
	long	lAdjustedPerc	= 0;		// % capacity of x adjusted on a int scale
	long	lRand = 0;


	/////////////////////////////////////////////////////////////////////
	//
	//		INDUSTRIAL/RESIDENTIAL 
	//
	/////////////////////////////////////////////////////////////////////////
	if((m_dwIndCapacity == 0) && (m_dwComCapacity ==0) && (m_dwPopulation ==0))
		return;

	if ((m_dwPopulation != 0) || (m_dwIndCapacity != 0))
	{
		if(m_dwIndCapacity != 0)
			dblIndPerc = (float)((float)m_dwPopulation/(float)m_dwIndCapacity);
		else
			dblIndPerc = 2.0f;

		if (dblIndPerc >= 1.0f)
		{
			//////////////////////////////////////////////////////////////////////
			//running over 100% industrial capacity.  
			//need more industry/less people
			lAdjustedPerc = (long)(dblIndPerc * 100);	//convert to whole number
			lAdjustedPerc -= 100;
			lAdjustedPerc -= (2*lAdjustedPerc);

		} else {

			///////////////////////////////////////////////
			//less people than ind capacity.
			//need more people/less industry.
			lAdjustedPerc = (long)((1.0f - dblIndPerc) * 100);	
		}


		iResCalc += lAdjustedPerc;		//new amount to increase res demand (negative at this point)
		iIndCalc -= lAdjustedPerc;		//increase the industrial demand by the same amount.
	}

	
	////////////////////////////////////////////////////////////////
	//
	//	COMMERCIAL/RESIDENTIAL
	//
	////////////////////////////////////////////////////////////////

	if ((m_dwPopulation != 0) || (m_dwComCapacity != 0))
	{
		if(m_dwComCapacity != 0)
			dblComPerc = (float)((float)m_dwPopulation/(float)m_dwComCapacity);
		else
			dblComPerc = 2.0f;

		if (dblComPerc >= 1.0f)
		{
			//////////////////////////////////////////////
			//running over 100% commercial capacity.
			//need more commercial structures.
			
			lAdjustedPerc = (long)(dblComPerc * 100);
			lAdjustedPerc -= 100;
			lAdjustedPerc -= (2*lAdjustedPerc);
		} else {

			lAdjustedPerc = (long)((1.0f - dblComPerc) * 100);
		}

		//
		//residential demand isn't affected by 
		//commercial demand.
		iComCalc -= lAdjustedPerc;	
	}



	//////////////////////////////////////////////////////////////
	//
	//		INDUSTRIAL/COMMERCIAL
	//
	//////////////////////////////////////////////////////////////////

	if ((m_dwIndCapacity != 0) || (m_dwComCapacity != 0))
	{
		if(m_dwComCapacity != 0)
			dblComPerc = (float)((float)m_dwIndCapacity/(float)m_dwComCapacity);
		else
			dblComPerc = 2.0f;

		if (dblComPerc >= 1.0f)
		{
			//////////////////////////////////////////////
			//running over 100% commercial capacity.
			//need more commercial structures and fewer
			//industrial ones.
			
			lAdjustedPerc = (long)(dblComPerc * 100);
			lAdjustedPerc -= 100;
			lAdjustedPerc -= (2*lAdjustedPerc);
		} else {

			lAdjustedPerc = (long)((1.0f - dblComPerc) * 100);
		}

		iIndCalc += lAdjustedPerc;
		iComCalc -= lAdjustedPerc;
	}


	//
	//scale the numbers
	//
	
	
	if(iComCalc < 0)
	{
		iComCalc = 50 - (abs(iComCalc) / 2);
		if (iComCalc < 2)
			iComCalc = 3;
	} else	{
		iComCalc = 50 + iComCalc/2;
		if (iComCalc > 100)
			iComCalc = 100;
	}

	if(iResCalc < 0)
	{
		iResCalc = 50 - (abs(iResCalc) / 2);
		if (iResCalc < 2)
			iResCalc = 3;
	} else {
		iResCalc = 50 + iResCalc/2;
		if (iResCalc > 100)
			iResCalc = 100;
	}

	if(iIndCalc < 0)
	{
		iIndCalc = 50 - (abs(iIndCalc) / 2);
		if (iIndCalc < 2)
			iIndCalc = 3;

	} else{
		
		iIndCalc = 50 + iIndCalc/2;
		if (iIndCalc > 100)
			iIndCalc = 100;
	}



	m_RCIStatus.wCom = iComCalc;
	m_RCIStatus.wInd = iIndCalc;
	m_RCIStatus.wRes = iResCalc;

}

/*
=========================
==
==	GetNeedForZone()
==
=========================
*/
long CCityManager::GetNeedForZone(zone_t* pZone)
{
	switch( pZone->zone_type )
	{
		case ZT_RESIDENTIAL:
			return m_RCIStatus.wRes;
			break;
		case ZT_COMMERCIAL:
			return m_RCIStatus.wCom;
			break;
		case ZT_INDUSTRIAL:
			return m_RCIStatus.wInd;
			break;
		default:
			return 0;
	}
}

/*
===========================
==
==	GetBuildingListForZone()
==
===========================
*/
BuildingNode_t* CCityManager::GetBuildingListForZone( zone_t* pZone )
{
	switch( pZone->zone_type )
	{
		case ZT_RESIDENTIAL:
			return m_pResList;
			break;
		case ZT_COMMERCIAL:
			return m_pComList;
			break;
		case ZT_INDUSTRIAL:
			return m_pIndList;
			break;
		default:
			return 0;
	}
}

