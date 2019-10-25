// CityObj.h: interface for the CCityObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CITYOBJ_H__C243A111_5126_11D5_8D63_00B0D081587C__INCLUDED_)
#define AFX_CITYOBJ_H__C243A111_5126_11D5_8D63_00B0D081587C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCityObj  
{
public:
	CCityObj();
	virtual ~CCityObj();

	/////////////////////////////////
	//
	//	ACCESSOR FUNCTIONS
	//
	/////////////////////////////////
	UINT		GetPic() {return m_uPic;}
	DWORD		GetCapacity() {return m_dwCapacity;}
	UINT		GetDim1() {return m_uDim1;}
	UINT		GetDim2() {return m_uDim2;}
	effect_t	GetEffects() {return m_Effect;}
	long		GetUpkeepCost() {return m_lUpkeepCost;}		
	long		GetInitialCost( ) {return m_lInitialCost;}
	
	void		SetEffects(effect_t effect) {m_Effect = effect;}
	void		SetUpkeepCost(long lUpkeepCost);
	void		SetInitialCost(long lInitialCost);
	void		SetDim1( long dim1 );
	void		SetDim2( long dim2 );
	void		SetPic( UINT uPic ) {m_uPic = uPic;}
	void		SetCapacity( DWORD dwCapacity ) {m_dwCapacity = dwCapacity;}
	

private:
	long		m_lInitialCost;
	long		m_lUpkeepCost;
	UINT		m_uPic;
	DWORD		m_dwCapacity;
	effect_t	m_Effect;
	UINT		m_uDim1;
	UINT		m_uDim2;
};

#endif // !defined(AFX_CITYOBJ_H__C243A111_5126_11D5_8D63_00B0D081587C__INCLUDED_)
