// SampleView.cpp : implementation of the CSampleView class
//

#include "stdafx.h"
//#include "Sample.h"
#include "resource.h"
#include "SampleDoc.h"
#include "SampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleView

IMPLEMENT_DYNCREATE(CSampleView, CCrystalEditView)

BEGIN_MESSAGE_MAP(CSampleView, CCrystalEditView)
	//{{AFX_MSG_MAP(CSampleView)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CCrystalEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CCrystalEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CCrystalEditView::OnFilePrintPreview)
	ON_COMMAND(ID_BUILD_COMPILE, OnBuildCompile)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleView construction/destruction

CSampleView::CSampleView()
{
	// TODO: add construction code here

}

CSampleView::~CSampleView()
{
}

BOOL CSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CCrystalEditView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CSampleView diagnostics

#ifdef _DEBUG
void CSampleView::AssertValid() const
{
	CCrystalEditView::AssertValid();
}

void CSampleView::Dump(CDumpContext& dc) const
{
	CCrystalEditView::Dump(dc);
}

CSampleDoc* CSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSampleDoc)));
	return (CSampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSampleView message handlers

CCrystalTextBuffer *CSampleView::LocateTextBuffer()
{
	return &GetDocument()->m_xTextBuffer;
}

void CSampleView::OnInitialUpdate() 
{
	CCrystalEditView::OnInitialUpdate();

	SetFont(GetDocument()->m_lf);
}

void CSampleView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	//AfxMessageBox("Build your own context menu!");
}

int CompileAndRun(char *ScriptSrc,char *DbgFile);

void CSampleView::OnBuildCompile()
{
	CString datext,datext2="";
	CSampleDoc *tmpdoc = (CSampleDoc *) GetDocument();
	tmpdoc->m_xTextBuffer.GetText(0,0,tmpdoc->m_xTextBuffer.GetLineCount()-1,tmpdoc->m_xTextBuffer.GetLineLength(tmpdoc->m_xTextBuffer.GetLineCount()-1),datext);

	int toto=datext.GetLength();
	for (int i=0;i<toto;i++)
	{
		if ( (datext[i]!='\r')&&(datext[i]!='\t'))
		{
			datext2+=datext[i];
		}
	}
	
	CString datext3="#include theHeader\n"
		"void Main()\n"
		"{\n"
		"MessageBox(\"Alive\");\n"
		"}\n";

	datext2+="\n\0";
	CompileAndRun(datext2.GetBuffer(1),"DebugFile");
}

void CSampleView::OnFileSave()
{
    CSampleDoc *tmpdoc = (CSampleDoc *) GetDocument();
	if (!tmpdoc->IsNamed)
	{
		OnFileSaveAs();
	}
	else
	{
		tmpdoc->m_xTextBuffer.SaveToFile(tmpdoc->daFileName);//, int nCrlfStyle = CRLF_STYLE_AUTOMATIC, BOOL bClearModifiedFlag = TRUE);
	}
}

void CSampleView::OnFileSaveAs()
{
    CFileDialog *m_FileDiag;
	m_FileDiag=new CFileDialog(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Kapsul script(*.ksc)\0*.ksc\0\0",this);
	//m_FileDiag->m_ofn.lpstrFilter=WriteFilter;
	if (m_FileDiag->DoModal()==IDOK)
	{
        CSampleDoc *tmpdoc = (CSampleDoc *) GetDocument();
		tmpdoc->m_xTextBuffer.SaveToFile(m_FileDiag->m_ofn.lpstrFile);//, int nCrlfStyle = CRLF_STYLE_AUTOMATIC, BOOL bClearModifiedFlag = TRUE);
		strcpy(tmpdoc->daFileName,m_FileDiag->m_ofn.lpstrFile);
		tmpdoc->SetTitle(m_FileDiag->m_ofn.lpstrFile);
	}	
}