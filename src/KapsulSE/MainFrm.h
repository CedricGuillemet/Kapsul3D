// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__17961C96_CD41_49EB_9135_9BFA7BC26486__INCLUDED_)
#define AFX_MAINFRM_H__17961C96_CD41_49EB_9135_9BFA7BC26486__INCLUDED_
	
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MatBrowserDialogBar.h"
#include "MatBrowser.h"

#include "DeskBrowser.h"
//#include "DesksShowDialogBar.h"
#include "FOToolBar.h"
#include "AnimOutput.h"
#include "MyDeskBar.h"
#include "MyAnimateBar.h"
#include "BCMenu.h"
#include "MyStatusBar.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	//CStatusBar      m_wndStatusBar;

	CMyToolBar    m_wndToolBar;
	CFOToolBar    m_wndToolBarDesk;

	CMyAnimBar m_wndAnim;
	CMyStatusBar m_wndStatus;
	CMyDeskBar m_wndDesksBrowser;
	
	HMENU NewMenu();
	HMENU NewDefaultMenu();
	BCMenu m_menu,m_default;

	
	
    CMyToolBar  m_Plugs;
	CMyToolBar  m_Primitives;

    unsigned int PlugsIds[50];
	unsigned int PrimitivesIds[500];

	int indprim;

	CImageList PlugImageList;
	CImageList PlugImageListHot;
	CImageList PrimitivesImageList;
	CImageList PrimitivesImageListHot;


	CFileDialog	*m_FileDiag;

	CImageList		imaLarge, imaSmall;

	CFont gSmallFont;

	CKViewEdit* GetNextMDIChildWnd();
	int GetCountDesk(CKViewEdit **cme);
	void RefreshOutBar(void);
	void AttachToolbarImages (CFOToolBar *m_TBDest,UINT inNormalImageID,
                                      UINT inDisabledImageID,
                                      UINT inHotImageID,
									  CImageList &m_Hot,CImageList &m_Disabled,CImageList &m_Normal);

	void AttachToolbarImages (CMyToolBar *m_TBDest,UINT inNormalImageID,
                                      UINT inDisabledImageID,
                                      UINT inHotImageID,
									  CImageList &m_Hot,CImageList &m_Disabled,CImageList &m_Normal);

    //void myDisplay(char *msg);
	CImageList m_ToolbarImagesDisabledMain;
	CImageList m_ToolbarImagesHotMain;
	CImageList m_ToolbarImagesMain;

	CImageList m_ToolbarImagesDisabledDesk;
	CImageList m_ToolbarImagesHotDesk;
	CImageList m_ToolbarImagesDesk;

	BOOL VerifyBarState(LPCTSTR lpszProfileName);
// Generated message map functions
public:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnHelpTipoftheday();
	afx_msg void OnToolsOption();
	afx_msg void OnEditSelectCircle();
	afx_msg void OnEditSelectFence();
	afx_msg void OnEditSelectQuad();
	afx_msg void OnEditDelete();
	afx_msg void OnViewMovespan();
	afx_msg void OnViewRegionfit();
	afx_msg void OnViewRotate();
	afx_msg void OnViewZoominout();
	afx_msg void OnViewExtendsviews();
	afx_msg void OnViewExtendview();
	afx_msg void OnViewBuildbar();
	afx_msg void OnViewPluginbar();
	afx_msg void OnViewModify();
	afx_msg void OnViewModifyview();
	afx_msg void OnUpdateViewBuildbar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewModify(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewModifyview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewPluginbar(CCmdUI* pCmdUI);
	afx_msg void OnViewSelection();
	afx_msg void OnUpdateViewSelection(CCmdUI* pCmdUI);
	afx_msg void OnViewViewconfiguration();
	afx_msg void OnUpdateViewViewconfiguration(CCmdUI* pCmdUI);
	afx_msg void OnViewEditmode();
	afx_msg void OnUpdateViewEditmode(CCmdUI* pCmdUI);
	afx_msg void OnViewRendermodeMapped();
	afx_msg void OnViewRendermodeWire();
	afx_msg void OnViewRendermode();
	afx_msg void OnUpdateViewRendermode(CCmdUI* pCmdUI);
	afx_msg void OnBuildCentered();
	afx_msg void OnBuildCrossing();
	afx_msg void OnBuildSnap();
	afx_msg void OnUpdateBuildCentered(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBuildCrossing(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBuildSnap(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditModeFace(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditModeObject(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditModeVertex(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnToolsSkyboxeditor();
	afx_msg void OnToolsPluginsfolders();
	afx_msg void OnEditRedo();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnViewMapsbrowser();
	afx_msg void OnUpdateViewMapsbrowser(CCmdUI* pCmdUI);
	afx_msg void OnAppAbout();
	afx_msg void OnAboutKapsul();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnCreateprim();
	afx_msg void OnViewAnimationbar();
	afx_msg void OnUpdateViewAnimationbar(CCmdUI* pCmdUI);
	afx_msg void OnViewDockbar();
	afx_msg void OnUpdateViewDockbar(CCmdUI* pCmdUI);
	afx_msg void OnViewEditbar();
	afx_msg void OnUpdateViewEditbar(CCmdUI* pCmdUI);
	afx_msg void OnEditDoselect();
	afx_msg void OnUpdateEditDoselect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCreateprim(CCmdUI* pCmdUI);
	afx_msg void OnEditChoosemode();
	afx_msg void OnUpdateEditSelectCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditSelectFence(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditSelectQuad(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBuildCentroid();
	afx_msg void OnUpdateBuildCentroid(CCmdUI* pCmdUI);
	afx_msg void OnFileNewproject();
	afx_msg void OnFileOpenproject();
	afx_msg void OnFileCloseproject();
	afx_msg void OnFileCloseall();
	afx_msg void OnViewStatusBar();
	afx_msg void OnUpdateViewStatusBar(CCmdUI* pCmdUI);
	afx_msg void OnViewPrimitivebar();
	afx_msg void OnUpdateViewPrimitivebar(CCmdUI* pCmdUI);
	afx_msg void OnToolsMaterialeditor();
	afx_msg void OnBuildAnglesnap();
	afx_msg void OnUpdateBuildAnglesnap(CCmdUI* pCmdUI);
	afx_msg void OnToolsNetupdate();
	afx_msg void OnToolsRenderer();
	//}}AFX_MSG
	afx_msg LRESULT OnWmSetStatus(WPARAM, LPARAM);
	afx_msg LRESULT OnWmDrawScene(WPARAM wParam, LPARAM lParam) ;
    afx_msg LRESULT OnWmSetPlugin(WPARAM, LPARAM);
    afx_msg LRESULT OnWmSetMouseCursor(WPARAM, LPARAM);
    afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

	
public:
	afx_msg void OnToolsEntitymanager();
	afx_msg void OnViewCompilationtools();
	afx_msg void OnUpdateViewCompilationtools(CCmdUI *pCmdUI);
	afx_msg void OnViewToolbar();
	afx_msg void OnUpdateViewToolbar(CCmdUI *pCmdUI);
	afx_msg void OnMoveRotateScale();
	afx_msg void OnMoveRotateTaperSquiz();
	afx_msg void OnMoveRotateBend();
	afx_msg void OnUpdateMoveRotateScale(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMoveRotateTaperSquiz(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMoveRotateBend(CCmdUI* pCmdUI);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnToolsRenderingOptions();

};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__17961C96_CD41_49EB_9135_9BFA7BC26486__INCLUDED_)
