#ifndef _CKViewEdit_H
#define _CKViewEdit_H

#include "resource.h"
#include "Kapsul3D.h"
//#include "OGLView.h"
#include "winuser.h"

//#include "Desk.h"
//#include "Maths.h"
//#include "GenericLib.h"
//#include "GLEnabledView.h"


#define ssCtrl 1
#define ssShift 2

extern  int		FunctionID;
extern	CKScene	*CurrentScene;
extern  CKScenePlugin *GCurPlug;

class CKViewEdit : public CView
{
protected:
	DECLARE_DYNCREATE(CKViewEdit)
	CKViewEdit();

public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CKViewEdit)
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	public:
	int ButtonState;

    //OGLView *View;
	CKScene *m_Scene;
	CKRenderer *m_Renderer;


    bool IsMoving;
	CKDirectInput8 m_DInput;

    int dx,dy;
    Vertex huitemp;
	POINT flypos;

	bool Snap,Crossing,Center;
	/*
    void  SetSelectFunc(TSpeedButton * TSP);
    void  SetLoupeFunc(TSpeedButton * TSP);
    void  UpdateCombo(int daPrimitive);
	*/
    
    bool IsDrawAll;
    //void DrawViews(void);
//    Math *Maths;
    //Vertex  GetCoord(int X, int Y);
    //Desk *FirstDesk,*NextDesk;
    //Desk *CurrentDesk;
    //bool  AddDesk();
    //String  NameFromPath(String val);
    int nbDesk;
	CKViewEdit *Next,*Prev;
	/*
    void  DelDesk();
	*/

	Vertex m_ScaleMask;
	MYPOINT m_ScaleSvgSize;
	
	int SvgFunctionID;
	int NewHand;
	int NewHand2;
	int m_Sens;
	int ox,oy;
	int daButs;

    // current color
    //float coRed,coGreen,coBlue;
    //KColor CurrentColor;
	/*
    void  ShowHint(char *daString);
    void  ShowContextMenu(int X,int Y);
    void  SetLib(GenericLib *daGen);
	*/
    CKScenePlugin *tmpPlugin;
    void *PropEnt;
	unsigned int PropType;

    int FrameInd;
    //void SetPlug(int PlugID);
    CKPlan *dap;
    double ngl;
    Vertex Getng,Getng2;

	HWND hWnd;


	Vertex SnapVal;
	int SelectedSel;


// ----------------------------------------------------------------------------

	virtual void KMouseDown(int Button,int X, int Y);
	virtual void KMouseMove(int Shift,int X, int Y);
	virtual void KMouseUp(int Button,int X, int Y);
	virtual BOOL KMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	void DrawViews(void);
	void DrawView(int ViewNb);

	void Paint();

	CKViewEdit(HWND daHwnd);
	~CKViewEdit();

	void KeyDown(int dawParam);
	void KeyUp(int dawParam);

	bool ToggleSnap(void);
	bool ToggleWindow(void);
	bool ToggleCenter(void);
	

	//
	char *TmpName;
	Vertex * CircleHui;
	char *temp;
	char *tmp;
	void UpdateGridInfo();




    // Save/load
    //GenericLib *genSave;
	//{{AFX_MSG(CKViewEdit)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnViewConfig1x2();
	afx_msg void OnViewConfig1x3();
	afx_msg void OnViewConfig2x1();
	afx_msg void OnViewConfig2x2();
	afx_msg void OnViewConfig3x1();
	afx_msg void OnViewConfigFullscreen();
	afx_msg void OnViewExtendsviews();
	afx_msg void OnViewExtendview();
	afx_msg void OnViewTypeBack();
	afx_msg void OnViewTypeBottom();
	afx_msg void OnViewTypeCamera();
	afx_msg void OnViewTypeFront();
	afx_msg void OnViewTypeLeft();
	afx_msg void OnViewTypeRight();
	afx_msg void OnViewTypeTop();
	afx_msg void OnViewMapping();
	afx_msg void OnViewOrthoUser();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnViewRendermodeMapped();
	afx_msg void OnRenderModeFlatShaded();
	afx_msg void OnRenderModeMappedOutline();
	afx_msg void OnFileSaveAs();
    afx_msg void OnFileSave();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
    afx_msg void OnEditDetete();
	afx_msg void OnViewRendermodeWire();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnChildActivate();
    afx_msg void OnKillFocus( CWnd* pNewWnd );
	afx_msg void OnProperties();
	afx_msg void OnViewSelectByName();
	afx_msg void OnSkyBoxLoad();
	afx_msg void OnSkyBoxNone();
	afx_msg void OnEditSelectAll();
	afx_msg void OnViewFly();
	afx_msg void OnViewGridDecreasegrid();
	afx_msg void OnViewGridIncreasegrid();
	afx_msg void OnViewGridVisible();
	afx_msg void OnUpdateViewGridVisible(CCmdUI* pCmdUI);
	afx_msg void OnBackWorldCap(void);
	afx_msg void OnUndoViewChange(void);
	afx_msg void OnRedoViewChange(void);
	//}}AFX_MSG
	afx_msg LRESULT OnWmUnSelectAll(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CView)
	public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	protected:
	//}}AFX_VIRTUAL


public:
	afx_msg void OnUpdateSkyboxLoad(CCmdUI *pCmdUI);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMoveRotateScale();
	afx_msg void OnMoveRotateTaperSquiz();
	afx_msg void OnMoveRotateBend();
	afx_msg void OnHookCameraTarget();
	afx_msg void OnUpdateMoveRotateScale(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMoveRotateTaperSquiz(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMoveRotateBend(CCmdUI* pCmdUI);
	afx_msg void OnViewTypePerspective();

};
#endif
