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
#include "DesksShowDialogBar.h"
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
	CStatusBar      m_wndStatusBar;
    //CToolBar    m_wndToolBar2;

	CMyToolBar    m_wndToolBar;

	CMyToolBar    m_wndToolBarSelect;
	CMyToolBar    m_wndToolBarViewConf;
	CMyToolBar    m_wndToolBarModify;
	CMyToolBar    m_wndToolModifView;
	CMyToolBar    m_wndToolRender;
    CMyToolBar    m_wndToolScript;
	CMyToolBar    m_wndToolCompilation;
    CMyToolBar    m_wndToolTypeView;


    CAnimateDialogBar m_wndAnim;
	CMatBrowserDialogBar m_wndMatBrowser;
	CDesksShowDialogBar m_wndDesksBrowser;
	CTVTestDlg	m_DesksBrowser;
    CMyToolBar  m_Plugs;
    unsigned int PlugsIds[50];
    //int nbPlugsIds;
    /*
    CProjectBar     m_wndProjects;

    CCompileBar     m_wndCompile;
    CCompileOut     m_cCompile;
    */
	CTScrollDlg		m_cDialog;
    CAnimate		m_cAnimDlg;
	CMatBrowser		m_MatBrowser;

    //CProjects       m_cProjects;

	CMenu	m_wndMenuBar;

	CFileDialog	*m_FileDiag;




	CImageList		imaLarge, imaSmall;


	//COutBar *m_wndOutBar;
	CModeBar	m_wndMode;
	CFont gSmallFont;
/*
   CWnd  m_wndMDIClient;
   CWnd* m_pWndCurrentChild;

   //HWND m_MDIClient;
   HWND* m_purrentChild;

*/
   MainEdit* GetNextMDIChildWnd();
   int GetCountDesk(MainEdit **cme);
   void RefreshOutBar(void);
   void LoadOptions(void);
    //void myDisplay(char *msg);

// Generated message map functions
public:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnToolbarDropDown(NMTOOLBAR* pnmh, LRESULT* plRes);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnHelpTipoftheday();
	afx_msg void OnToolsOption();
	afx_msg void OnEditSelectCircle();
	afx_msg void OnEditSelectFence();
	afx_msg void OnEditSelectQuad();
	afx_msg void OnEditSelectSingle();
	afx_msg void OnEditScale();
	afx_msg void OnEditRotate();
	afx_msg void OnEditMoveaxe();
	afx_msg void OnEditMove();
	afx_msg void OnEditModeVertex();
	afx_msg void OnEditModeObject();
	afx_msg void OnEditModeFace();
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
	afx_msg void OnViewViewtypes();
	afx_msg void OnUpdateViewViewtypes(CCmdUI* pCmdUI);
	afx_msg void OnToolsPluginsfolders();
	afx_msg void OnEditRedo();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnProperties();
	afx_msg void OnViewMapsbrowser();
	afx_msg void OnUpdateViewMapsbrowser(CCmdUI* pCmdUI);
	afx_msg void OnViewDeskfilebrowser();
	afx_msg void OnUpdateViewDeskfilebrowser(CCmdUI* pCmdUI);
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
	afx_msg void OnViewAnimationbar();
	afx_msg void OnUpdateViewAnimationbar(CCmdUI *pCmdUI);
	afx_msg void OnViewToolbar();
	afx_msg void OnUpdateViewToolbar(CCmdUI *pCmdUI);
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__17961C96_CD41_49EB_9135_9BFA7BC26486__INCLUDED_)
