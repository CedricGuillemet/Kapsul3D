#pragma once


// CKThumbListView
//#include "PakFile.h"

class KAPSUL_DESC CKThumbListView : public CListCtrl
{
	DECLARE_DYNAMIC(CKThumbListView)

public:
	CKThumbListView();
	virtual ~CKThumbListView();

    CImageList	m_ImageListThumb;		
    HIMAGELIST	m_SmallIcons;		
    HIMAGELIST	m_Icons;	
    int m_TypeView;

	vector<PackListFiles>	m_VectorImageNames;		// vector holding the image names
	int						m_nSelectedItem;

	BOOL  GetImageFileNames();	// gather the image file names
	void  DrawThumbnails();		// draw the thumbnails in list control
    CString	m_strImageDir;
    void Init();
	CString SelectedFile;
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClickListThumb(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownListThumb(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblClickListThumb(NMHDR* pNMHDR, LRESULT* pResult);

//    virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
//    virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
};


