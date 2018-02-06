// hexedvw.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "editcmd.h"
#include "hexedvw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TCHAR hextable[16] = {_T ('0'), _T ('1'), _T ('2'), _T ('3'), _T ('4'), _T ('5'), _T ('6'), _T ('7'),
                     _T ('8'), _T ('9'), _T ('A'), _T ('B'), _T ('C'), _T ('D'), _T ('E'), _T ('F')};
#define TOHEX(a, b) {*b++ = hextable[a >> 4];*b++ = hextable[a&0xf];}
/////////////////////////////////////////////////////////////////////////////
// CHexEditView
#define DEMO
IMPLEMENT_DYNCREATE(CHexEditView, CView)

static LPBYTE s_pData = NULL;      // pointer to data
static int s_length = 0;     // length of data

CHexEditView::CHexEditView()
{
  m_pData = &s_pData;
  m_length = &s_length;
  m_topindex    = 0;
  m_bpr     = 16;    // byte per row 
  m_lpp     = 1;

  m_dwFlags = (HVW_SHOW_ADDRESS|HVW_SHOW_ASCII|HVW_SHOW_HEX|HVW_WIDE_ADDRESS);

  m_offAddress  = 0;
  m_offHex    = 0;
  m_offAscii    = 0;

  m_dwFlags |= HVW_UPDATE;     // update font info
  m_currentMode = EDIT_NONE;

  m_editPos.x = m_editPos.y = 0;
  m_currentAddress = 0;
  m_dwFlags |= HVW_HALF_PAGE;

  m_selStart  = 0xffffffff;
  m_selEnd  = 0xffffffff;

  m_Font.CreateFont(-12, 0,0,0,0,0,0,0,0,0,0,0,0, _T ("Courier New"));
}

CHexEditView::~CHexEditView()
{
}


BEGIN_MESSAGE_MAP(CHexEditView, CView)
  ON_WM_CONTEXTMENU()
  //{{AFX_MSG_MAP(CHexEditView)
  ON_WM_CHAR()
  ON_WM_KILLFOCUS()
  ON_WM_PAINT()
  ON_WM_SETFOCUS()
  ON_WM_SIZE()
  ON_WM_VSCROLL()
  ON_WM_HSCROLL()
  ON_WM_GETDLGCODE()
  ON_WM_ERASEBKGND()
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONDBLCLK()
  ON_WM_MOUSEMOVE()
  ON_WM_LBUTTONUP()
  ON_WM_KEYDOWN()
  ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
  ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
  ON_COMMAND(ID_EDIT_CUT, OnEditCut)
  ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
  ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
  ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
  ON_COMMAND (ID_READ_ONLY, OnReadOnly)
  ON_UPDATE_COMMAND_UI (ID_READ_ONLY, OnReadOnly)
  ON_COMMAND (ID_FORMAT_SHOW_ADDRESS, OnFormatShowAddress)
  ON_UPDATE_COMMAND_UI (ID_FORMAT_SHOW_ADDRESS, OnUpdateFormatShowAddress)
  ON_COMMAND (ID_FORMAT_SHOW_ASCII, OnFormatShowAscii)
  ON_UPDATE_COMMAND_UI (ID_FORMAT_SHOW_ASCII, OnUpdateFormatShowAscii)
  ON_COMMAND (ID_FORMAT_SHOW_HEX, OnFormatShowHex)
  ON_UPDATE_COMMAND_UI (ID_FORMAT_SHOW_HEX, OnUpdateFormatShowHex)
  ON_COMMAND (ID_FORMAT_WIDE_ADDRESS, OnFormatWideAddress)
  ON_UPDATE_COMMAND_UI (ID_FORMAT_WIDE_ADDRESS, OnUpdateFormatWideAddress)
  ON_COMMAND_RANGE (ID_FORMAT_BPR_FIRST, ID_FORMAT_BPR_LAST, OnBpr)
  ON_UPDATE_COMMAND_UI_RANGE (ID_FORMAT_BPR_FIRST, ID_FORMAT_BPR_LAST, OnUpdateBpr)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexEditView message handlers

void CHexEditView::OnDraw(CDC* pDC)
{
  CDocument* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  // TODO: add draw code for native data here
}

void CHexEditView::OnPaint() 
{
  CPaintDC pdc(this); // device context for painting

  CRect rc;
  GetClientRect(rc);
  
  CDC dc;
  dc.CreateCompatibleDC(CDC::FromHandle(pdc.m_ps.hdc));
  CBitmap bm;

  bm.CreateCompatibleBitmap(CDC::FromHandle(pdc.m_ps.hdc), rc.Width(), rc.Height());
  dc.SelectObject(bm);

  CBrush b;
  b.CreateSolidBrush(RGB(0xff,0xff,0xff));
  dc.FillRect(rc, &b);

  ASSERT(m_currentAddress >= 0);
  ASSERT(m_topindex >= 0);

  dc.SelectObject(m_Font);
  int   height    = 0;
  int   x,y;
  TCHAR  buf[256];

  x = rc.TopLeft().x;
  y = rc.TopLeft().y;

  dc.SetBoundsRect(&rc, DCB_DISABLE);

  if(m_pData && *m_pData)
  {
    //
    // get char dimensions
    //
    if(m_dwFlags & HVW_UPDATE)
    {
      dc.GetCharWidth(_T ('0'), _T ('0'), &m_nullWidth);
      CSize sz = dc.GetTextExtent(_T ("0"), 1);
      m_lineHeight = sz.cy;
      
      m_offHex  = m_dwFlags & HVW_SHOW_ADDRESS ? (m_dwFlags & HVW_WIDE_ADDRESS ? m_nullWidth * 9 : m_nullWidth * 5) : 0;
      m_offAscii  = m_dwFlags & HVW_SHOW_ADDRESS ? (m_dwFlags & HVW_WIDE_ADDRESS ? m_nullWidth * 9 : m_nullWidth * 5) : 0;
      m_offAscii += m_dwFlags & HVW_SHOW_HEX ? (m_bpr * 3 * m_nullWidth) : 0;

      m_lpp = rc.Height() / m_lineHeight;
      m_dwFlags &= ~HVW_HALF_PAGE;
      if(m_lpp * m_bpr > *m_length)
      {
        m_lpp = (*m_length + (m_bpr/2)) / m_bpr ;
        if(*m_length % m_bpr != 0)
        {
          m_dwFlags |= HVW_HALF_PAGE;
          m_lpp++;
        }
      }
      m_dwFlags &= ~HVW_UPDATE;
      UpdateScrollbars();
    }

    TRACE(_T ("%i %i\n"), m_topindex, m_selStart);
    
    height = rc.Height() / m_lineHeight;
    height *= m_lineHeight;

    if(m_dwFlags & HVW_SHOW_ADDRESS)
    {
      TCHAR fmt[8] = {_T ('%'), _T ('0'), _T ('8'), _T ('l'), _T ('X')};
      fmt[2] = m_dwFlags & HVW_WIDE_ADDRESS ? _T ('8') : _T ('4');
      int w = m_dwFlags & HVW_WIDE_ADDRESS ? 8 : 4;
      y = 0;
      CRect rcd = rc;
      rcd.TopLeft().x = m_offAddress;
      for(int  i = m_topindex; (i < *m_length) && (rcd.TopLeft().y < height); i+= m_bpr)
      {
        _stprintf(buf, fmt, i);
        dc.DrawText(buf, w, rcd, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOPREFIX);
        rcd.TopLeft().y += m_lineHeight;
      }
    }
    if(m_dwFlags & HVW_SHOW_HEX)
    {
      y = 0;
      CRect rcd = rc;
      rcd.TopLeft().x = x = m_offHex;

      if(m_selStart != 0xffffffff && (m_currentMode == EDIT_HIGH || m_currentMode == EDIT_LOW))
      {
        int  i;
        int  n = 0;
        int  selStart = m_selStart, selEnd = m_selEnd;
        if(selStart > selEnd)
          selStart ^= selEnd ^= selStart ^= selEnd;

        for(i = m_topindex; (i < selStart) && (y < height); i++)
        {
          LPTSTR p = buf;
          TOHEX((*m_pData)[i], p);
          *p++ = _T (' ');
          dc.TextOut(x, y, buf, 3);
          x += m_nullWidth * 3;
          n++;
          if(n == m_bpr)
          {
            n = 0;
            x = m_offHex;
            y += m_lineHeight;
          }
        }
        dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
        dc.SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
        for(; (i < selEnd) && (i < *m_length) && (y < height); i++)
        {
          LPTSTR p = buf;
          TOHEX((*m_pData)[i], p);
          *p++ = _T (' ');
          dc.TextOut(x, y, buf, 3);
          x += m_nullWidth * 3;
          n++;
          if(n == m_bpr)
          {
            n = 0;
            x = m_offHex;
            y += m_lineHeight;
          }
        }
        dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
        dc.SetBkColor(GetSysColor(COLOR_WINDOW));
        for(; (i < *m_length) && (y < height); i++)
        {
          LPTSTR p = buf;
          TOHEX((*m_pData)[i], p);
          *p++ = _T (' ');
          dc.TextOut(x, y, buf, 3);
          x += m_nullWidth * 3;
          n++;
          if(n == m_bpr)
          {
            n = 0;
            x = m_offHex;
            y += m_lineHeight;
          }
        }
      }
      else
      {
        for(int  i = m_topindex; (i < *m_length) && (rcd.TopLeft().y < height);)
        {
          LPTSTR p = buf;
          for(int  n = 0; (n < m_bpr) && (i < *m_length); n++)
          {
            TOHEX((*m_pData)[i], p);
            *p++ = _T (' ');
            i++;
          }
          while(n < m_bpr)
          {
            *p++ = _T (' '); *p++ = _T (' '); *p++ = _T (' ');
            n++;
          }

          dc.DrawText(buf, m_bpr*3, rcd, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOPREFIX);
          rcd.TopLeft().y += m_lineHeight;
        }
      }
    }
    if(m_dwFlags & HVW_SHOW_ASCII)
    {
      y = 0;
      CRect rcd = rc;
      rcd.TopLeft().x = x = m_offAscii;
      if(m_selStart != 0xffffffff && m_currentMode == EDIT_ASCII)
      {
        int  i;
        int  n = 0;
        int  selStart = m_selStart, selEnd = m_selEnd;
        if(selStart > selEnd)
          selStart ^= selEnd ^= selStart ^= selEnd;

        for(i = m_topindex; (i < selStart) && (y < height); i++)
        {
          buf[0] = isprint((*m_pData)[i]) ? (*m_pData)[i] : _T ('.');
          dc.TextOut(x, y, buf, 1);
          x += m_nullWidth;
          n++;
          if(n == m_bpr)
          {
            n = 0;
            x = m_offAscii;
            y += m_lineHeight;
          }
        }
        dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
        dc.SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
        for(; (i < selEnd) && (y < height); i++)
        {
          buf[0] = isprint((*m_pData)[i]) ? (*m_pData)[i] : _T ('.');
          dc.TextOut(x, y, buf, 1);
          x += m_nullWidth;
          n++;
          if(n == m_bpr)
          {
            n = 0;
            x = m_offAscii;
            y += m_lineHeight;
          }
        }
        dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
        dc.SetBkColor(GetSysColor(COLOR_WINDOW));
        for(; (i < *m_length) && y < height; i++)
        {
          buf[0] = isprint((*m_pData)[i]) ? (*m_pData)[i] : _T ('.');
          dc.TextOut(x, y, buf, 1);
          x += m_nullWidth;
          n++;
          if(n == m_bpr)
          {
            n = 0;
            x = m_offAscii;
            y += m_lineHeight;
          }
        }
      }
      else
      {
        for(int  i = m_topindex; (i < *m_length) && (rcd.TopLeft().y < height);)
        {
          LPTSTR p = buf;
          for(int  n = 0; (n < m_bpr) && (i < *m_length); n++)
          {
            *p++ = isprint((*m_pData)[i]) ? (*m_pData)[i] : _T ('.');
            i++;
          }
          dc.DrawText(buf, n, rcd, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOPREFIX);
          rcd.TopLeft().y += m_lineHeight;
        }
      }
    }
  }
  pdc.BitBlt(0, 0, rc.Width(), rc.Height(), &dc, 0, 0, SRCCOPY);
}

void CHexEditView::OnSetFocus(CWnd* pOldWnd) 
{
  if(m_pData && *m_pData && !IsSelected())
  {
    if(m_editPos.x == 0 && (m_dwFlags & HVW_SHOW_ADDRESS))
      CreateAddressCaret();
    else
      CreateEditCaret();
    SetCaretPos(m_editPos);
    ShowCaret();
  }
  CWnd::OnSetFocus(pOldWnd);
}

void CHexEditView::OnKillFocus(CWnd* pNewWnd) 
{
  DestroyCaret();
  CWnd::OnKillFocus(pNewWnd);
}

void CHexEditView::OnSize(UINT nType, int cx, int cy) 
{
  CView::OnSize(nType, cx, cy);
}

void CHexEditView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  pScrollBar;
  if(!m_pData || !*m_pData)
    return;

  int oa = m_topindex;
  switch(nSBCode)
  {
    case SB_LINEDOWN:
      if(m_topindex < *m_length - m_lpp*m_bpr)
      {
        //ScrollWindow(0, -m_lineHeight, rc);
        m_topindex += m_bpr;
        RedrawWindow();
      }
      break;
    
    case SB_LINEUP:
      if(m_topindex > 0)
      {
        //ScrollWindow(0, m_lineHeight, rc);
        m_topindex -= m_bpr;
        RedrawWindow();
      }
      break;
    
    case SB_PAGEDOWN:
      if(m_topindex < *m_length - m_lpp*m_bpr)
      {
        m_topindex += m_bpr * m_lpp;
        if(m_topindex > *m_length - m_lpp*m_bpr)
          m_topindex = *m_length - m_lpp*m_bpr;
        RedrawWindow();
      }
      break;

    case SB_PAGEUP:
      if(m_topindex > 0)
      {
        m_topindex -= m_bpr * m_lpp;
        if(m_topindex < 0)
          m_topindex = 0;
        RedrawWindow();
      }
      break;

    case SB_THUMBTRACK:
      m_topindex = nPos * m_bpr;
      RedrawWindow();
      break;
  }
  ::SetScrollPos(this->m_hWnd, SB_VERT, m_topindex / m_bpr, TRUE);
  if(!(m_dwFlags & HVW_NO_ADDRESS_CHANGE))
    m_currentAddress += (m_topindex - oa);
  RepositionCaret(m_currentAddress);
}

void CHexEditView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  nSBCode;nPos; pScrollBar;
}

UINT CHexEditView::OnGetDlgCode() 
{
  return DLGC_WANTALLKEYS;
}

BOOL CHexEditView::PreCreateWindow(CREATESTRUCT& cs) 
{
  // cs.style |= WS_HSCROLL|WS_VSCROLL;
  // cs.style &= ~(WS_HSCROLL|WS_VSCROLL);
  return CView::PreCreateWindow(cs);
}

BOOL CHexEditView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
  // dwStyle |= WS_HSCROLL|WS_VSCROLL;
  dwStyle &= ~(WS_HSCROLL|WS_VSCROLL);
  BOOL bRet = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
  if(bRet)
    SetFont(&m_Font);
  return bRet;
}

BOOL CHexEditView::OnEraseBkgnd(CDC* pDC) 
{
  pDC;
  return TRUE;
}

void CHexEditView::GetOptions(BOOL &a, BOOL &h, BOOL &c, BOOL &w, BOOL &r)
{
  a = (m_dwFlags & HVW_SHOW_ADDRESS) != 0;
  h = (m_dwFlags & HVW_SHOW_HEX) != 0;
  c = (m_dwFlags & HVW_SHOW_ASCII) != 0;
  w = (m_dwFlags & HVW_WIDE_ADDRESS) != 0;
  r = (m_dwFlags & HVW_READ_ONLY) != 0;
}

void CHexEditView::SetOptions(BOOL a, BOOL h, BOOL c, BOOL w, BOOL r)
{
  if (a)
    m_dwFlags |= HVW_SHOW_ADDRESS;
  else
    m_dwFlags &= ~HVW_SHOW_ADDRESS;
  if (h)
    m_dwFlags |= HVW_SHOW_HEX;
  else
    m_dwFlags &= ~HVW_SHOW_HEX;
  if (c)
    m_dwFlags |= HVW_SHOW_ASCII;
  else
    m_dwFlags &= ~HVW_SHOW_ASCII;
  if (w)
    m_dwFlags |= HVW_WIDE_ADDRESS;
  else
    m_dwFlags &= ~HVW_WIDE_ADDRESS;
  if (r)
    m_dwFlags |= HVW_READ_ONLY;
  else
    m_dwFlags &= ~HVW_READ_ONLY;
  m_dwFlags |= HVW_UPDATE;
}

void CHexEditView::SetOptions(DWORD dwFlags)
{
  m_dwFlags &= HVW_EXTENDED;
  m_dwFlags |= (dwFlags & HVW_EXTENDED) | HVW_UPDATE;
}

void CHexEditView::SetBPR(int bpr)
{
  m_bpr = bpr;
  m_dwFlags |= HVW_UPDATE;
}

void CHexEditView::OnLButtonDown(UINT nFlags, CPoint point) 
{
  SetFocus();
  if(!m_pData || !*m_pData)
    return;

  if(nFlags & MK_SHIFT)
  {
    m_selStart = m_currentAddress;
  }
  CPoint pt = CalcPos(point.x, point.y);
  if(pt.x > -1)
  {
    m_editPos = pt;
    pt.x *= m_nullWidth;
    pt.y *= m_lineHeight;
    
    if(pt.x == 0 && (m_dwFlags & HVW_SHOW_ADDRESS))
      CreateAddressCaret();
    else
      CreateEditCaret();

    SetCaretPos(pt);
    if(nFlags & MK_SHIFT)
    {
      m_selEnd = m_currentAddress;
      if(m_currentMode == EDIT_HIGH || m_currentMode == EDIT_LOW)
        m_selEnd++;
      RedrawWindow();
    }
  }
  if(!(nFlags & MK_SHIFT))
  {
    if(DragDetect(this->m_hWnd, point))
    {
      m_selStart = m_currentAddress;
      m_selEnd   = m_selStart;
      SetCapture();
    }
    else
    {
      BOOL bsel = m_selStart != 0xffffffff;

      m_selStart = 0xffffffff;
      m_selEnd   = 0xffffffff;
      if(bsel)
        RedrawWindow();
    }
  }
  if(!IsSelected())
  {
    ShowCaret();
  }
}

void CHexEditView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
  nFlags; point;
}

CPoint CHexEditView::CalcPos(int x, int y)
{
  y /= m_lineHeight;
  if(y < 0 || y > m_lpp)
    return CPoint(-1, -1);

  if(y * m_bpr > *m_length)
    return CPoint(-1, -1);

  x += m_nullWidth;
  x /= m_nullWidth;

  int xp;

  if((m_dwFlags & HVW_SHOW_ADDRESS) && x <= (m_dwFlags & HVW_WIDE_ADDRESS ? 8 : 4))
  {
    m_currentAddress = m_topindex + (m_bpr * y);
    m_currentMode = EDIT_NONE;
    return CPoint(0, y);
  }

  xp = (m_offHex  / m_nullWidth) + m_bpr * 3;
  if((m_dwFlags & HVW_SHOW_HEX) && x < xp)
  {
    if(x%3)
      x--;
    m_currentAddress = m_topindex + (m_bpr * y) + (x - (m_offHex  / m_nullWidth)) / 3;
    m_currentMode =  ((x%3) & 0x01) ? EDIT_LOW : EDIT_HIGH;
    return CPoint(x, y);
  }

  xp = (m_offAscii  / m_nullWidth) + m_bpr;
  if((m_dwFlags & HVW_SHOW_ASCII) && x <= xp)
  {
    m_currentAddress = m_topindex + (m_bpr * y) + (x - (m_offAscii  / m_nullWidth));
    m_currentMode = EDIT_ASCII;
    return CPoint(x, y);
  }

  return CPoint(-1,-1);
}

void CHexEditView::CreateAddressCaret()
{
  DestroyCaret();
  CreateSolidCaret(m_nullWidth * (m_dwFlags & HVW_WIDE_ADDRESS ? 8 : 4), m_lineHeight);
}

void CHexEditView::CreateEditCaret()
{
  DestroyCaret();
  CreateSolidCaret(m_nullWidth, m_lineHeight);
}

void CHexEditView::OnMouseMove(UINT nFlags, CPoint point) 
{
  if(!m_pData || !*m_pData)
    return;

  if(nFlags & MK_LBUTTON && m_selStart != 0xffffffff)
  {
    CRect rc;
    GetClientRect(&rc);
    if(!rc.PtInRect(point))
    {
      if(point.y < 0)
      {
        OnVScroll(SB_LINEUP, 0, NULL);
        point.y = 0;
      }
      else if(point.y > rc.Height())
      {
        OnVScroll(SB_LINEDOWN, 0, NULL);
        point.y = rc.Height() -1;
      }
    }

    //
    // we are selecting
    //
    int  seo = m_selEnd;
    CPoint pt = CalcPos(point.x, point.y);
    if(pt.x > -1)
    {
      m_selEnd = m_currentAddress;
      if(m_currentMode == EDIT_HIGH || m_currentMode == EDIT_LOW)
        m_selEnd++;
    }
    if(IsSelected())
      DestroyCaret();

    if(seo != m_selEnd)
      RedrawWindow();
  }
}

void CHexEditView::UpdateScrollbars()
{
  return;
  HWND hWnd = GetSafeHwnd ();
  SCROLLINFO si;

  si.cbSize = sizeof (SCROLLINFO);
  si.fMask = SIF_ALL;
  si.nMin = 0;
  si.nMax = *m_length / m_bpr - 1;
  si.nPage = m_lpp;
  si.nPos = m_topindex / m_bpr;

  // SetScrollInfo (SB_VERT, &si, TRUE);
  ::SetScrollInfo (hWnd, SB_VERT, &si, TRUE);
  if(si.nMax > (int) si.nPage)
    // EnableScrollBar (SB_VERT, ESB_ENABLE_BOTH);
    ::EnableScrollBar (hWnd, SB_VERT, ESB_ENABLE_BOTH);

  CRect rc;
  GetClientRect (&rc);

  si.nMin = 0;
  si.nMax =((m_dwFlags & HVW_SHOW_ADDRESS ? (m_dwFlags & HVW_WIDE_ADDRESS ? 8 : 4) : 0) +
        (m_dwFlags & HVW_SHOW_HEX ? m_bpr * 3 : 0) +
        (m_dwFlags & HVW_SHOW_ASCII ? m_bpr : 0) ) * m_nullWidth;
  si.nPage = 1;
  si.nPos = 0;
  // SetScrollInfo (SB_HORZ, &si, TRUE);
  ::SetScrollInfo (hWnd, SB_HORZ, &si, TRUE);
}


inline BOOL CHexEditView::IsSelected()
{
  return m_selStart != 0xffffffff;
}

void CHexEditView::OnLButtonUp(UINT nFlags, CPoint point) 
{
  if(IsSelected())
    ReleaseCapture();

  CWnd::OnLButtonUp(nFlags, point);
}

void CHexEditView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  nFlags;nRepCnt;
  if(!m_pData || !*m_pData)
    return;
  if(nChar == _T ('\t'))
    return;
  if(GetKeyState(VK_CONTROL) & 0x80000000)
  {
    switch(nChar)
    {
      case 0x03:
        if(IsSelected())
          OnEditCopy();
        return;
      case 0x16:
        OnEditPaste();
        return;
      case 0x18:
        if(IsSelected())
          OnEditCut();
        return;
      case 0x1a:
        OnEditUndo();
        return;
    }
  }

  if(nChar == 0x08)
  {
    if(m_currentAddress > 0)
    {
      m_currentAddress--;
      SelDelete(m_currentAddress, m_currentAddress+1);
      RepositionCaret(m_currentAddress);
      RedrawWindow();
    }
    return;
  }

  SetSel(-1, -1);
  if (!(m_dwFlags & HVW_READ_ONLY))
    switch(m_currentMode)
    {
      case EDIT_NONE:
        return;
      case EDIT_HIGH:
      case EDIT_LOW:
        if((nChar >= _T ('0') && nChar <= _T ('9')) || (nChar >= _T ('a') && nChar <= _T ('f')))
        {
          UINT b = nChar - _T ('0');
          if(b > 9) 
            b = 10 + nChar - _T ('a');

          if(m_currentMode == EDIT_HIGH)
          {
            (*m_pData)[m_currentAddress] = (unsigned char)(((*m_pData)[m_currentAddress] & 0x0f) | (b << 4));
          }
          else
          {
            (*m_pData)[m_currentAddress] = (unsigned char)(((*m_pData)[m_currentAddress] & 0xf0) | b);
          }
          CDocument *pDoc = GetDocument ();
          pDoc->SetModifiedFlag ();
          Move(1,0);
        }
        break;
      case EDIT_ASCII:
        {
          (*m_pData)[m_currentAddress] = (unsigned char)nChar;
          CDocument *pDoc = GetDocument ();
          pDoc->SetModifiedFlag ();
          Move(1,0);
        }
        break;
    }
  RedrawWindow();
}

void CHexEditView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  nFlags; nRepCnt;

  BOOL bShift = GetKeyState(VK_SHIFT) & 0x80000000;
  BOOL bac = (m_dwFlags & HVW_NO_ADDRESS_CHANGE) != 0;
  m_dwFlags |= HVW_NO_ADDRESS_CHANGE;
  switch(nChar)
  {
    case VK_DOWN:
      if(bShift)
      {
        if(!IsSelected())
        {
          m_selStart = m_currentAddress;
        }
        Move(0,1);
        m_selEnd   = m_currentAddress;
        if(m_currentMode == EDIT_HIGH || m_currentMode == EDIT_LOW)
          m_selEnd++;
        RedrawWindow();
        break;
      }
      else
        SetSel(-1, -1);
      Move(0,1);
      break;
    case VK_UP:
      if(bShift)
      {
        if(!IsSelected())
        {
          m_selStart = m_currentAddress;
        }
        Move(0,-1);
        m_selEnd   = m_currentAddress;
        RedrawWindow();
        break;
      }
      else
        SetSel(-1, -1);
      Move(0,-1);
      break;
    case VK_LEFT:
      if(bShift)
      {
        if(!IsSelected())
        {
          m_selStart = m_currentAddress;
        }
        Move(-1,0);
        m_selEnd   = m_currentAddress;
        RedrawWindow();
        break;
      }
      else
        SetSel(-1, -1);
      Move(-1,0);
      break;
    case VK_RIGHT:
      if(bShift)
      {
        if(!IsSelected())
        {
          m_selStart = m_currentAddress;
        }
        Move(1,0);
        m_selEnd   = m_currentAddress;
        if(m_currentMode == EDIT_HIGH || m_currentMode == EDIT_LOW)
          m_selEnd++;
        RedrawWindow();
        break;
      }
      else
        SetSel(-1, -1);
      Move(1,0);
      break;
    case VK_PRIOR:
      if(bShift)
      {
        if(!IsSelected())
        {
          m_selStart = m_currentAddress;
        }
        OnVScroll(SB_PAGEUP, 0, NULL);
        Move(0,0);
        m_selEnd   = m_currentAddress;
        RedrawWindow();
        break;
      }
      else
        SetSel(-1, -1);
      OnVScroll(SB_PAGEUP, 0, NULL);
      Move(0,0);
      break;
    case VK_NEXT:
      if(bShift)
      {
        if(!IsSelected())
        {
          m_selStart = m_currentAddress;
        }
        OnVScroll(SB_PAGEDOWN, 0, NULL);
        Move(0,0);
        m_selEnd   = m_currentAddress;
        RedrawWindow();
        break;
      }
      else
        SetSel(-1, -1);
      OnVScroll(SB_PAGEDOWN, 0, NULL);
      Move(0,0);
      break;
    case VK_HOME:
      if(bShift)
      {
        if(!IsSelected())
        {
          m_selStart = m_currentAddress;
        }
        if(GetKeyState(VK_CONTROL) & 0x80000000)
        {
          OnVScroll(SB_THUMBTRACK, 0, NULL);
          Move(0,0);
        }
        else
        {
          m_currentAddress /= m_bpr;
          m_currentAddress *= m_bpr;
          Move(0,0);
        }
        m_selEnd   = m_currentAddress;
        RedrawWindow();
        break;
      }
      else
        SetSel(-1, -1);
      if(GetKeyState(VK_CONTROL) & 0x80000000)
      {
        OnVScroll(SB_THUMBTRACK, 0, NULL);
        m_currentAddress = 0;
        Move(0,0);
      }
      else
      {
        m_currentAddress /= m_bpr;
        m_currentAddress *= m_bpr;
        Move(0,0);
      }
      break;
    case VK_END:
      if(bShift)
      {
        if(!IsSelected())
        {
          m_selStart = m_currentAddress;
        }
        if(GetKeyState(VK_CONTROL) & 0x80000000)
        {
          m_currentAddress = *m_length-1;
          OnVScroll(SB_THUMBTRACK, ((*m_length+(m_bpr/2)) / m_bpr) - m_lpp, NULL);
          Move(0,0);
        }
        else
        {
          m_currentAddress /= m_bpr;
          m_currentAddress *= m_bpr;
          m_currentAddress += m_bpr - 1;
          if(m_currentAddress > *m_length)
            m_currentAddress = *m_length-1;
          Move(0,0);
        }
        m_selEnd   = m_currentAddress;
        RedrawWindow();
        break;
      }
      else
        SetSel(-1, -1);
      if(GetKeyState(VK_CONTROL) & 0x80000000)
      {
        m_currentAddress = *m_length-1;
        if(m_dwFlags & HVW_HALF_PAGE)
          OnVScroll(SB_THUMBTRACK, 0, NULL);
        else
          OnVScroll(SB_THUMBTRACK, ((*m_length+(m_bpr/2)) / m_bpr) - m_lpp, NULL);
        Move(0,0);
      }
      else
      {
        m_currentAddress /= m_bpr;
        m_currentAddress *= m_bpr;
        m_currentAddress += m_bpr - 1;
        if(m_currentAddress > *m_length)
          m_currentAddress = *m_length-1;
        Move(0,0);
      }
      break;
    case VK_INSERT:
      SelInsert(m_currentAddress, max(1, m_selEnd-m_selStart));
      RedrawWindow();
      break;
    case VK_DELETE:
      if(IsSelected())
      {
        OnEditClear();
      }
      else
      {
        SelDelete(m_currentAddress, m_currentAddress+1);
        RedrawWindow();
      }
      break;
    case _T ('\t'):
      switch(m_currentMode)
      {
        case EDIT_NONE:
          m_currentMode = EDIT_HIGH;
          break;
        case EDIT_HIGH:
        case EDIT_LOW:
          m_currentMode = EDIT_ASCII;
          break;
        case EDIT_ASCII:
          m_currentMode = EDIT_HIGH;
          break;
      }
      Move(0,0);
      break;

  }
  if (bac)
    m_dwFlags |= HVW_NO_ADDRESS_CHANGE;
  else
    m_dwFlags &= ~HVW_NO_ADDRESS_CHANGE;
}

void CHexEditView::Move(int x, int y)
{
  switch(m_currentMode)
  {
    case EDIT_NONE:
      return;
    case EDIT_HIGH:
      if(x != 0)
        m_currentMode = EDIT_LOW;
      if(x == -1)
        m_currentAddress --;
      m_currentAddress += y* m_bpr;
      break;
    case EDIT_LOW:
      if(x != 0)
        m_currentMode = EDIT_HIGH;
      if(x == 1)
        m_currentAddress++;
      m_currentAddress += y* m_bpr;
      break;
    case EDIT_ASCII:
      {
        m_currentAddress += x;
        m_currentAddress += y*m_bpr;
      }
      break;
  }
  if(m_currentAddress < 0)
    m_currentAddress = 0;

  if(m_currentAddress >= *m_length)
  {
    m_currentAddress -= x;
    m_currentAddress -= y*m_bpr;
  }
  m_dwFlags |= HVW_NO_ADDRESS_CHANGE;
  if(m_currentAddress < m_topindex)
  {
    OnVScroll(SB_LINEUP, 0, NULL);
  }
  if(m_currentAddress >= m_topindex + m_lpp*m_bpr)
  {
    OnVScroll(SB_LINEDOWN, 0, NULL);
  }
  m_dwFlags &= ~HVW_NO_ADDRESS_CHANGE;
  //ScrollIntoView(m_currentAddress);
  RepositionCaret(m_currentAddress);
}

void CHexEditView::SetSel(int s, int e)
{
  DestroyCaret();
  m_selStart = s;
  m_selEnd = e;
  RedrawWindow();
  if(m_editPos.x == 0 && (m_dwFlags & HVW_SHOW_ADDRESS))
    CreateAddressCaret();
  else
    CreateEditCaret();
  SetCaretPos(m_editPos);
  ShowCaret();
}

void CHexEditView::RepositionCaret(int   p)
{
  int x, y;

  y = (p - m_topindex) / m_bpr;
  x = (p - m_topindex) % m_bpr;

  switch(m_currentMode)
  {
    case EDIT_NONE:
      CreateAddressCaret();
      x = 0;
      break;
    case EDIT_HIGH:
      CreateEditCaret();
      x *= m_nullWidth*3;
      x += m_offHex;
      break;
    case EDIT_LOW:
      CreateEditCaret();
      x *= m_nullWidth*3;
      x += m_nullWidth;
      x += m_offHex;
      break;
    case EDIT_ASCII:
      CreateEditCaret();
      x *= m_nullWidth;
      x += m_offAscii;
      break;
  }
  m_editPos.x = x;
  m_editPos.y = y*m_lineHeight;
  CRect rc;
  GetClientRect(&rc);
  if(rc.PtInRect(m_editPos))
  {
    SetCaretPos(m_editPos);
    ShowCaret();
  }
}

void CHexEditView::ScrollIntoView(int p)
{
  if(p < m_topindex || p > m_topindex + m_lpp*m_bpr)
  {
    m_topindex = (p/m_bpr) * m_bpr;
    m_topindex -= (m_lpp / 3) * m_bpr;
    if(m_topindex < 0)
      m_topindex = 0;

    UpdateScrollbars();
    RedrawWindow();
  }
}

void CHexEditView::OnContextMenu(CWnd*, CPoint point)
{

  // CG: This block was added by the Pop-up Menu component
  {
    if (point.x == -1 && point.y == -1)
    {
      //keystroke invocation
      CRect rect;
      GetClientRect(rect);
      ClientToScreen(rect);

      point = rect.TopLeft();
      point.Offset(5, 5);
    }

    CMenu menu;
    VERIFY(menu.LoadMenu(IDR_POPUP_HEX_EDIT));

    CMenu* pPopup = menu.GetSubMenu(0);
    ASSERT(pPopup != NULL);

    pPopup->EnableMenuItem(ID_EDIT_UNDO, MF_GRAYED|MF_DISABLED|MF_BYCOMMAND);
    if(!IsSelected())
    {
      pPopup->EnableMenuItem(ID_EDIT_CLEAR, MF_GRAYED|MF_DISABLED|MF_BYCOMMAND);
      pPopup->EnableMenuItem(ID_EDIT_CUT, MF_GRAYED|MF_DISABLED|MF_BYCOMMAND);
      pPopup->EnableMenuItem(ID_EDIT_COPY, MF_GRAYED|MF_DISABLED|MF_BYCOMMAND);
    }
    {
      COleDataObject  obj;  
      if (obj.AttachClipboard()) 
      {
        if(!obj.IsDataAvailable(CF_TEXT) && !obj.IsDataAvailable(RegisterClipboardFormat(_T ("BinaryData"))))
          pPopup->EnableMenuItem(ID_EDIT_PASTE, MF_GRAYED|MF_DISABLED|MF_BYCOMMAND);
      }
    }

    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
      this);
  }
}

void CHexEditView::OnEditClear() 
{
  m_currentAddress = m_selStart;
  SelDelete(m_selStart, m_selEnd);
  RepositionCaret(m_currentAddress);
  RedrawWindow();
}

void CHexEditView::OnEditCopy() 
{
  COleDataSource*   pSource = new COleDataSource();
  EmptyClipboard();
  if(m_currentMode != EDIT_ASCII)
  {
    int     dwLen = (m_selEnd-m_selStart);
    HGLOBAL   hMemb = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT, m_selEnd-m_selStart);
    HGLOBAL   hMema = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT, (dwLen) * 3);

    if (!hMema) 
      return;

    // copy binary
    LPTSTR p = (LPTSTR)::GlobalLock(hMemb);
    memcpy(p, (*m_pData)+m_selStart, dwLen);
    ::GlobalUnlock(hMemb);
    
    // copy ascii
    p = (LPTSTR)::GlobalLock(hMema);
    for(int  i = 0; i < dwLen;)
    {
      TOHEX((*m_pData)[m_selStart+i], p);
      *p++ = _T (' ');
      i++;
    }

    ::GlobalUnlock(hMema);

    pSource->CacheGlobalData(RegisterClipboardFormat(_T ("BinaryData")), hMemb); 
    pSource->CacheGlobalData(CF_TEXT, hMema); 
  }
  else
  {
    HGLOBAL       hMemb = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT, m_selEnd-m_selStart);
    HGLOBAL       hMema = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT, m_selEnd-m_selStart);
    if (!hMemb || !hMema) 
      return;

    // copy binary
    LPBYTE  p = (BYTE*)::GlobalLock(hMemb);
    int   dwLen = m_selEnd-m_selStart;

    memcpy(p, (*m_pData)+m_selStart, dwLen);
    ::GlobalUnlock(hMemb);
    
    // copy ascii
    p = (BYTE*)::GlobalLock(hMema);
    memcpy(p, (*m_pData)+m_selStart, dwLen);
    for(int i = 0; i < dwLen; p++, i++)
      if(!isprint(*p))
        *p = _T ('.');
    ::GlobalUnlock(hMema);

    pSource->CacheGlobalData(RegisterClipboardFormat(_T ("BinaryData")), hMemb); 
    pSource->CacheGlobalData(CF_TEXT, hMema); 
  }
  pSource->SetClipboard();
}

void CHexEditView::OnEditCut() 
{
  OnEditCopy();
  SelDelete(m_selStart, m_selEnd);
  RedrawWindow();
}

void CHexEditView::OnEditPaste() 
{
  COleDataObject  obj;  
  if (obj.AttachClipboard()) 
  {
    HGLOBAL hmem = NULL;
    if (obj.IsDataAvailable(RegisterClipboardFormat(_T ("BinaryData")))) 
    {
      hmem = obj.GetGlobalData(RegisterClipboardFormat(_T ("BinaryData")));
    } 
    else if (obj.IsDataAvailable(CF_TEXT)) 
    {
      hmem = obj.GetGlobalData(CF_TEXT);
    }
    if(hmem)
    {
      LPBYTE  p = (BYTE*)::GlobalLock(hmem);
      DWORD dwLen = ::GlobalSize(hmem);
      int   insert;
      int   oa = m_currentAddress;
      
      NormalizeSel();
      if(m_selStart == 0xffffffff)
      {
        if(m_currentMode == EDIT_LOW)
          m_currentAddress++;
        insert = m_currentAddress;
        SelInsert(m_currentAddress, dwLen);
      }
      else
      {
        insert = m_selStart;
        SelDelete(m_selStart, m_selEnd);
        SelInsert(insert, dwLen);
        SetSel(-1, -1);
      }

      memcpy((*m_pData)+insert, p, dwLen);

      m_currentAddress = oa;
      RedrawWindow();
      ::GlobalUnlock(hmem);
    }
  }
}

void CHexEditView::OnEditSelectAll() 
{
  m_selStart = 0;
  m_selEnd = *m_length;
  DestroyCaret();
  RedrawWindow();
}

void CHexEditView::OnEditUndo() 
{
  // TODO: Add your command handler code here
  
}

void CHexEditView::NormalizeSel()
{
  if(m_selStart > m_selEnd)
    m_selStart ^= m_selEnd ^= m_selStart ^= m_selEnd;
}

void CHexEditView::SelDelete(int s, int e)
{
  LPBYTE p = (LPBYTE) malloc(*m_length - (e-s)+1);
  memcpy(p, *m_pData, s);
  if(s < *m_length-(e-s)) 
    memcpy(p+s, (*m_pData)+e, (*m_length -e));
  
  free(*m_pData);
  SetSel(-1, -1);
  *m_pData = p;
  *m_length = *m_length-(e-s);
  CDocument *pDoc = GetDocument ();
  pDoc->SetModifiedFlag ();
  if(m_currentAddress > *m_length)
  {
    m_currentAddress = *m_length;
    RepositionCaret(m_currentAddress);
  }
  m_dwFlags |= HVW_UPDATE;
}

void CHexEditView::SelInsert(int s, int l)
{
  LPBYTE p = (LPBYTE) calloc(*m_length + l, 1);
  memcpy(p, *m_pData, s);
  memcpy(p+s+l, (*m_pData)+s, (*m_length-s));
  free(*m_pData);
  SetSel(-1, -1);
  *m_pData = p;
  *m_length = *m_length+l;
  CDocument *pDoc = GetDocument ();
  pDoc->SetModifiedFlag ();
  m_dwFlags |= HVW_UPDATE;
}

CSize CHexEditView::GetSel()
{
  return CSize(m_selStart, m_selEnd);
}

void CHexEditView::SetData(LPBYTE p, int len)
{
  free(*m_pData);
  LPBYTE pp = (LPBYTE) malloc(len);
  memcpy(pp, p, len);
  SetOrigData(pp, len);
}

void CHexEditView::SetOrigData(LPBYTE p, int len)
{
  *m_pData = p;
  *m_length = len;
  ResetView ();
}

void CHexEditView::ResetView ()
{
  SetSel(-1, -1);
  m_currentAddress = 0;
  m_editPos.x = m_editPos.y = 0;
  m_currentMode = EDIT_HIGH;
  m_topindex = 0;
  m_dwFlags |= HVW_UPDATE;
}

int CHexEditView::GetData(LPBYTE p, int len)
{
  memcpy(p, *m_pData, min(len, *m_length));
  return *m_length;
}

int CHexEditView::GetOrigData(LPBYTE &p)
{
  p = *m_pData;
  return *m_length;
}

void CHexEditView::OnReadOnly()
{
  m_dwFlags ^= HVW_READ_ONLY;
  m_dwFlags |= HVW_UPDATE;
  RedrawWindow ();
}

void CHexEditView::OnUpdateReadOnly (CCmdUI * pCmdUI)
{
  pCmdUI->SetCheck ((m_dwFlags & HVW_READ_ONLY) != 0);
}

void CHexEditView::OnFormatShowAddress()
{
  m_dwFlags ^= HVW_SHOW_ADDRESS;
  m_dwFlags |= HVW_UPDATE;
  RedrawWindow ();
}

void CHexEditView::OnUpdateFormatShowAddress (CCmdUI * pCmdUI)
{
  pCmdUI->SetCheck ((m_dwFlags & HVW_SHOW_ADDRESS) != 0);
}

void CHexEditView::OnFormatShowAscii()
{
  m_dwFlags ^= HVW_SHOW_ASCII;
  m_dwFlags |= HVW_UPDATE;
  RedrawWindow ();
}

void CHexEditView::OnUpdateFormatShowAscii (CCmdUI * pCmdUI)
{
  pCmdUI->SetCheck ((m_dwFlags & HVW_SHOW_ASCII) != 0);
}

void CHexEditView::OnFormatShowHex()
{
  m_dwFlags ^= HVW_SHOW_HEX;
  m_dwFlags |= HVW_UPDATE;
  RedrawWindow ();
}

void CHexEditView::OnUpdateFormatShowHex (CCmdUI * pCmdUI)
{
  pCmdUI->SetCheck ((m_dwFlags & HVW_SHOW_HEX) != 0);
}

void CHexEditView::OnFormatWideAddress()
{
  m_dwFlags ^= HVW_WIDE_ADDRESS;
  m_dwFlags |= HVW_UPDATE;
  RedrawWindow ();
}

void CHexEditView::OnUpdateFormatWideAddress (CCmdUI * pCmdUI)
{
  pCmdUI->SetCheck ((m_dwFlags & HVW_WIDE_ADDRESS) != 0);
}

void CHexEditView::OnBpr (UINT nCmd)
{
  SetBPR(nCmd - ID_FORMAT_BPR_FIRST + 1);
  RedrawWindow ();
}

void CHexEditView::OnUpdateBpr (CCmdUI * pCmdUI)
{
  pCmdUI->SetCheck (pCmdUI->m_nID - ID_FORMAT_BPR_FIRST + 1 == (UINT) m_bpr);
}
