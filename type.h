////////////////////////////////////////
//
//			TYPE.H
//
//	CITY DEFINITIONS 
//	
//	Lee McKnight
//
//

#ifndef CITYDEF
#define CITYDEF

////////////////////////////////////////////
//
//	BUILDING CODES
//
////////////////////////////////////////////
#define		BC_LOW_CHEAP		0x0000
#define		BC_LOW_MEDIUM		0x0001
#define		BC_LOW_EXPENSIVE	0x0010
#define		BC_MED_CHEAP		0x0100
#define		BC_MED_MEDIUM		0x0101
#define		BC_MED_EXPENSIVE	0x0110
#define		BC_HIGH_CHEAP		0x1000
#define		BC_HIGH_MEDIUM		0x1001
#define		BC_HIGH_EXPENSIVE	0x1010


/////////////////////////////////////////////
//
//	THRESHOLDS FOR BUILDING TYPE LEVELS
//
//////////////////////////////////////////////
#define		TH_MEDIUM			50
#define		TH_HIGH				100

////////////////////////////////////////////
//
//	LAND VALUES
//
////////////////////////////////////////////
#define		LV_LOW				0x0000
#define		LV_MEDIUM			0x0001
#define		LV_HIGH				0x0002

////////////////////////////////////////////////
//
//	BUTTON CODES
//
////////////////////////////////////////////////
#define		BTN_ZOOM_IN			0x0001
#define		BTN_ZOOM_OUT		0x0002
#define		BTN_RESIDENTIAL		0x0003
#define		BTN_COMMERCIAL		0x0004
#define		BTN_INDUSTRIAL		0x0005
#define		BTN_POWERPLANT		0x0006


//////////////////////////////////////////////////
//
//	ROAD CODES
//
///////////////////////////////////////////////////
#define		RC_NORTH			0x0001
#define		RC_SOUTH			0x0010
#define		RC_EAST				0x0100
#define		RC_WEST				0x1000

#define		NW_ROAD( RC ) ( ( RC & RC_NORTH ) | (RC & RC_SOUTH ) )
#define		EW_ROAD( RC ) ( ( RC & RC_EAST ) | (RC & RC_WEST ) )

///////////////////////////////////////////////////
//
//	POLLUTION EFFECTS
//
///////////////////////////////////////////////////
#define		PC_ROAD				5
#define		PC_COALPOWER		100
#define		PC_PARK				-10
#define		PC_IND				0
#define		PC_RES				0
#define		PC_COM				0

///////////////////////////////////////////////////
//
//	CRIME EFFECTS
//
///////////////////////////////////////////////////
#define		CC_POLICE			-100
#define		CC_ROAD				1
#define		CC_IND				5
#define		CC_COM				4
#define		CC_RES				3
#define		CC_COALPOWER		15


///////////////////////////////////////////////////
//
//	LAND VALUE EFFECTS
//
///////////////////////////////////////////////////
#define		LVC_RES				10
#define		LVC_COM				15
#define		LVC_IND				-20
#define		LVC_COALPOWER		-75
#define		LVC_ROAD			5


//////////////////////////////////////////////////
//
//	ZONE TYPES
//
//////////////////////////////////////////////////
#define		ZT_NONE				0
#define		ZT_RESIDENTIAL		1
#define		ZT_COMMERCIAL		2
#define		ZT_INDUSTRIAL		3


///////////////////////////////////////////////////
//
//	MATH CONSTANTS
//
///////////////////////////////////////////////////
#include	"math.h"

#define		PI		3.14159
#define		SIN45	.7071
#define		HYP45	1.414
#define		HYP( x, y ) ( sqrt( (x*x) + (y*y) ) )


//////////////////////////////////////////////////
//
//	CELL DEFINITIONS
//
//////////////////////////////////////////////////
typedef		unsigned int		QUADRANT;			
#define		QUAD_UPPERRIGHT		1
#define		QUAD_UPPERLEFT		2
#define		QUAD_LOWERLEFT		3		
#define		QUAD_LOWERRIGHT		4
#define		UPPERQUAD( x ) ( ( x == QUAD_UPPERRIGHT ) || ( x == QUAD_UPPERLEFT ) )
#define		RIGHTQUAD( x ) ( ( x == QUAD_UPPERRIGHT ) || ( x == QUAD_LOWERRIGHT ) )

//////////////////////////////////////////////////
//
//	ERROR HANDLING
//
//////////////////////////////////////////////////

typedef unsigned long			ERC;

#define E_FAILED( ERC ) ( ERC != E_OK )
#define	E_SUCCEEDED( ERC ) ( ERC == E_OK )

#define	E_OK				0x0000
#define	E_NOFUNDS			0x0001
#define	E_BADCELL			0x0002
#define	E_NOPOWER			0x0004
#define	E_NOROAD			0x0008
#define	E_OBJEXISTS			0x0010
#define	E_NOZONE			0x0020
#define	E_BUILDINGEXISTS	0x0040
#define	E_POLLUTION			0x0080


typedef struct CITY_EFFECTS {
	double		dPollutionEffect;
	double		dCrimeEffect;
	double		dLandValueEffect;
} effect_t;


#include	"cityobj.h"
#include	"building.h"

///////////////////////////////////
//
// Having 1 CITY_OBJECTS struct with 
// a pointer to each type of city object
// makes it easier.  by passing this
// around to functions, the caller
// doesn't need to care which objects
// the function actually needs.
//
typedef struct CITY_OBJECTS{
	CCityObj	*pLot;
	CCityObj	*pEWRoad;
	CCityObj	*pNSRoad;
	CCityObj	*pIntersection;
	CCityObj	*pPolice;
	CCityObj	*pSchool;
	CCityObj	*pSmallPark;
	CCityObj	*pLargePark;
	CCityObj	*pCollege;
	CCityObj	*pBus;
	CCityObj	*pFire;
	CCityObj	*pRes;
	CCityObj	*pComm;
	CCityObj	*pInd;
	CCityObj	*pCoalPP;
} cityobjs_t;

/////////////////////////////////////
//BUILDING_NODE
//there will be 3 linked building lists.
//1 for each industrial, commercial, and
//residential.   
typedef struct BUILDING_NODE{
	CBuilding		*pBuilding;
	BUILDING_NODE*	pNext;
	BUILDING_NODE*	pPrev;
} BuildingNode_t;

//////////////////////////////////////
//CITYDATE
//
typedef struct CITYDATE {
	DWORD			dwYear;
	DWORD			dwMonth;
	DWORD			dwDay;
}	citydate_t;

///////////////////////////////////////////
//
//CELLSTAT
//
typedef struct CELLSTAT {
	double		dPollution;
	double		dCrime;
	DWORD		dwLandValue;
	UINT		uPic;
	BOOL		bIsPowered;
} cellstat_t;


/////////////////////////////////////////////////////////
//
//
//			ZONES
//
// A ZONE is an area of land that has
// been zoned by the user (commercial, residential
// or industrial), but not yet developed.
// a linked list of ZONE elements contains
// ALL zones that are undeveloped.  The struct
// has the position of the zone, and the zone type.
//
///////////////////////////////////////////////////////////

typedef struct ZONE {
	LONG			x;					//x position of zone
	LONG			y;					//y position of zone
	DWORD			zone_type;
} zone_t;

typedef struct ZONE_NODE{
	ZONE		*pZone;
	ZONE_NODE*	pNext;
	ZONE_NODE*	pPrev;
} ZoneNode_t;



////////////////////////////////////////////////////////
//
//
//		CELL RADIUS
//
//
//the RADIUS_NODE contains a cell coord
// and a distance from point of origin.
/////////////////////////////////////////////////////////
typedef struct CELL_RADIUS {
	LONG		x;
	LONG		y;
	double		Dist;
} CellRadius_t;

typedef struct RADIUS_NODE { 
	CellRadius_t* pCell;
	RADIUS_NODE* pNext;
	RADIUS_NODE* pPrev;
} RadiusNode_t;


////////////////////////////////////////
//
//	RCI indicators
//
/////////////////////////////////////////
struct RCI {
	WORD		wRes;
	WORD		wCom;
	WORD		wInd;
}; 

#endif












