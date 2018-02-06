#ifndef _MAINEDIT_H
#define _MAINEDIT_H

#include "resource.h"
#include <headers.h>
//#include "OGLView.h"
#include "winuser.h"

//#include "Desk.h"
//#include "Maths.h"
//#include "GenericLib.h"
//#include "GLEnabledView.h"


#define ssCtrl 1
#define ssShift 2

extern  int		FunctionID;
extern	Desk	*CurrentDesk;
extern  GenericLib *gen;

class MainEdit : public CView
{
protected:
	DECLARE_DYNCREATE(MainEdit)
	MainEdit();

public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(MainEdit)
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	public:
	int ButtonState;

    //OGLView *View;
	Desk *dk;


    bool IsMoving;

    int dx,dy;
    Vertex huitemp;

	bool Snap,Crossing,Center;
	/*
    void  SetSelectFunc(TSpeedButton * TSP);
    void  SetLoupeFunc(TSpeedButton * TSP);
    void  UpdateCombo(int daPrimitive);
	*/
    
    bool IsDrawAll;
    //void DrawViews(void);
    Math *Maths;
    //Vertex  GetCoord(int X, int Y);
    //Desk *FirstDesk,*NextDesk;
    //Desk *CurrentDesk;
    //bool  AddDesk();
    //String  NameFromPath(String val);
    int nbDesk;
	MainEdit *Next,*Prev;
	/*
    void  DelDesk();
	*/


    // current color
    //float coRed,coGreen,coBlue;
    //KColor CurrentColor;
	/*
    void  ShowHint(char *daString);
    void  ShowContextMenu(int X,int Y);
    void  SetLib(GenericLib *daGen);
	*/
    GenericLib *tmpGen;
    void *PropEnt;

    int FrameInd;
    //void SetPlug(int PlugID);
    Plan *dap;
    double ngl;
    Vertex Getng,Getng2;

	HWND hWnd;


	Vertex SnapVal;
	int SelectedSel;


// ----------------------------------------------------------------------------

	void FormMouseDown(int Button,int X, int Y);
	void FormMouseMove(int Shift,int X, int Y);
	void FormMouseUp(int Button,int X, int Y);
	void DrawViews(void);

	void Paint();

	MainEdit(HWND daHwnd);
	~MainEdit();

	void KeyDown(int dawParam);
	void KeyUp(int dawParam);
	void SetFunc(int daFunctionID);
	bool ToggleSnap(void);
	bool ToggleWindow(void);
	bool ToggleCenter(void);
	void ShowContextMenu(int X,int Y);


	//
	char *TmpName;
	Vertex * CircleHui;
	char *temp;
	char *tmp;

    // Save/load
    //GenericLib *genSave;
	//{{AFX_MSG(MainEdit)
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
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnViewRendermodeMapped();
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
	//}}AFX_MSG
	afx_msg LRESULT OnWmUnSelectAll(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
    CDC* m_pCDC;	// WinGDI Device Context
    HGLRC m_hRC;	// OpenGL Rendering Context
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
};
#endif
