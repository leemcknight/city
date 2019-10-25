// Building.h: interface for the CBuilding class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUILDING_H__5FB5D6B1_59CA_11D5_8D63_00B0D081587C__INCLUDED_)
#define AFX_BUILDING_H__5FB5D6B1_59CA_11D5_8D63_00B0D081587C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBuilding : public CCityObj
{
public:
	CBuilding();
	virtual ~CBuilding();
	void	SetBuildingType(UINT uType) {m_uType = uType;};
	UINT	GetBuildingType() {return m_uType;}

private:
	UINT	m_uType;
	
};

#endif // !defined(AFX_BUILDING_H__5FB5D6B1_59CA_11D5_8D63_00B0D081587C__INCLUDED_)
