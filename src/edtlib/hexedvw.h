#ifndef __HEXEDVW_H__INCLUDED__
#define __HEXEDVW_H__INCLUDED__

/////////////////////////////////////////////////////////////////////////////
// CHexEditView window

#define HVW_SHOW_ADDRESS 0x00001
#define HVW_SHOW_ASCII 0x0002
#define HVW_SHOW_HEX 0x0004
#define HVW_WIDE_ADDRESS 0x0008
#define HVW_ALL (HVW_SHOW_ADDRESS|HVW_SHOW_ASCII|HVW_SHOW_HEX|HVW_WIDE_ADDRESS)
#define HVW_EXTENDED (HVW_ALL|HVW_READ_ONLY)

#define HVW_READ_ONLY 0x1000
#define HVW_NO_ADDRESS_CHANGE 0x2000
#define HVW_HALF_PAGE 0x4000
#define HVW_UPDATE 0x8000

class EDITPADC_CLASS CHexEditView : public CView
{
// Construction
public:
  DECLARE_DYNCREATE(CHexEditView)
  CHexEditView();

  enum EDITMODE{  
      EDIT_NONE,
      EDIT_ASCII,
      EDIT_HIGH,
      EDIT_LOW
  } ;
// Attributes
public:
  LPBYTE  *m_pData;      // pointer to data
  int     *m_length;     // length of data
  DWORD   m_dwFlags;
  int     m_topindex;     // offset of first visible byte on screen

  int     m_currentAddress; // address under cursor
  EDITMODE  m_currentMode;    // current editing mode: address/hex/ascii
  int     m_selStart;     // start address of selection
  int     m_selEnd;     // end address of selection

  int     m_bpr;        // byte per row 
  int     m_lpp;        // lines per page
  
  CFont   m_Font;
  int     m_lineHeight;
  int     m_nullWidth;

  int     m_offHex,
        m_offAscii,
        m_offAddress;

  CPoint    m_editPos;

// Operations
public:

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CHexEditView)
  public:
  virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
  protected:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  virtual void OnDraw(CDC* pDC);
  //}}AFX_VIRTUAL

// Implementation
public:
  int GetData(LPBYTE p, int len);
  int GetOrigData(LPBYTE &p);
  void SetData(LPBYTE p, int len);
  void SetOrigData(LPBYTE p, int len);
  CSize GetSel(void);
  void SetSel(int s, int e);
  void SetBPR(int bpr);
  void GetOptions(BOOL &a, BOOL &h, BOOL &c, BOOL &w, BOOL &r);
  void SetOptions(BOOL a, BOOL h, BOOL c, BOOL w, BOOL r);
  void SetOptions(DWORD dwFlags);
  virtual ~CHexEditView();

  // Generated message map functions
protected:
  void    ScrollIntoView(int p);
  void    RepositionCaret(int p);
  void    Move(int x, int y);
  inline BOOL IsSelected(void);
  void    UpdateScrollbars(void);
  void    CreateEditCaret(void);
  void    CreateAddressCaret(void);
  CPoint    CalcPos(int x, int y);
  void    SelInsert(int s, int l);
  void    SelDelete(int s, int e);
  inline void NormalizeSel(void);
  void ResetView ();
  afx_msg void OnContextMenu(CWnd*, CPoint point);
  //{{AFX_MSG(CHexEditView)
  afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKillFocus(CWnd* pNewWnd);
  afx_msg void OnPaint();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg UINT OnGetDlgCode();
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnEditClear();
  afx_msg void OnEditCopy();
  afx_msg void OnEditCut();
  afx_msg void OnEditPaste();
  afx_msg void OnEditSelectAll();
  afx_msg void OnEditUndo();
  afx_msg void OnReadOnly();
  afx_msg void OnUpdateReadOnly (CCmdUI * pCmdUI);
  afx_msg void OnFormatShowAddress();
  afx_msg void OnUpdateFormatShowAddress (CCmdUI * pCmdUI);
  afx_msg void OnFormatShowAscii();
  afx_msg void OnUpdateFormatShowAscii (CCmdUI * pCmdUI);
  afx_msg void OnFormatShowHex();
  afx_msg void OnUpdateFormatShowHex (CCmdUI * pCmdUI);
  afx_msg void OnFormatWideAddress();
  afx_msg void OnUpdateFormatWideAddress (CCmdUI * pCmdUI);
  afx_msg void OnBpr (UINT nCmd);
  afx_msg void OnUpdateBpr (CCmdUI * pCmdUI);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()
};

#endif // __HEXEDVW_H__INCLUDED__
