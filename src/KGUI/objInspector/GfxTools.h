
class CQuickFont : public CFont
{
public :
	CQuickFont(CString cFontName, int nHeight, int nWidth, bool bUnderline = false)
	{
		CreateFont(nHeight,0,0,0, nWidth, 0, bUnderline,0, DEFAULT_CHARSET,
			       OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, ANTIALIASED_QUALITY,
				    DEFAULT_PITCH | FF_DONTCARE, cFontName);
	}
};

class CBrushSelector
{
	private:
		CBrush *m_pBrush, 
			   *m_pOBrush;
		CDC    *m_pDC;
	public:

	CBrushSelector(COLORREF color, CDC *pDC)
	{
		m_pDC = pDC;
		m_pBrush = (CBrush*) new CBrush(color);
		m_pOBrush = m_pDC->SelectObject(m_pBrush);
	};

	~CBrushSelector()
	{
		m_pDC->SelectObject(m_pOBrush);
		delete m_pBrush;
	};
};


class CFontSelector
{
private:
	CFont *m_pFont;
	CDC   *m_pDC;
public:

	CFontSelector(CFont* pFont, CDC *pDC)
	{
		m_pDC = pDC;
		m_pFont = m_pDC->SelectObject(pFont);
	}

	~CFontSelector()
	{
		m_pDC->SelectObject(m_pFont);
	}

};

class CPenSelector 
{
private:
	
	CDC  *m_pDC;
	CPen *m_pOPen;
	CPen *m_pPen;

public : 
	CPenSelector (int nPenStyle, int nWidth, COLORREF nColor, CDC *pDC)
	{
		ASSERT(pDC);

		m_pDC   = pDC;
		m_pPen  = new CPen(nPenStyle, nWidth, nColor);
		m_pOPen = m_pDC->SelectObject(m_pPen);
	};

	virtual ~CPenSelector()
	{
		m_pDC->SelectObject(m_pOPen);
		delete m_pPen;
	};
};


CRect RectCopyDeflate(CRect rect, int l, int t, int r, int b)
{
	rect.DeflateRect(l,t,r,b);
	return rect;
}
CRect RectCopyInflate(CRect rect, int l, int t, int r, int b)
{
	rect.InflateRect(l,t,r,b);
	return rect;
}


