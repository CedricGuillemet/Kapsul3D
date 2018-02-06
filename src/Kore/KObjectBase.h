// KObjectBase.h: interface for the CKObjectBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KOBJECTBASE_H__67D61AD0_62F7_47FB_B7B3_FD32F94C7B49__INCLUDED_)
#define AFX_KOBJECTBASE_H__67D61AD0_62F7_47FB_B7B3_FD32F94C7B49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class KAPSUL_DESC CKObjectBase  
{
public:
	CKObjectBase();
	virtual ~CKObjectBase();

	//Parent
	CKScene *m_Scene;

	// Unique
	unsigned int Unique;

	// Selection Count
	int RefCount1,RefCount2;

	// Standard values
	CString Name;
	CKHashTable m_Table;
	bool Selected;
	bool Hided;
	int Tag;
	RGB Color;

	// Bounding Box
	Vertex BBMin,BBMax;
	void UpdateBBManual(Vertex &vMin,Vertex &vMax);
	virtual void UpdateBB() =0;

	// Copy
	virtual void IsCopyOf(CKObjectBase *pBase);
};

#endif // !defined(AFX_KOBJECTBASE_H__67D61AD0_62F7_47FB_B7B3_FD32F94C7B49__INCLUDED_)
