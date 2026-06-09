// RecView.cpp : implementation of the RecView class
//

#include "stdafx.h"
#include "v10.h"

#include "Set.h"
#include "Doc.h"
#include "RecView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RecView

IMPLEMENT_DYNCREATE(RecView, CRecordView)

BEGIN_MESSAGE_MAP(RecView, CRecordView)
    //{{AFX_MSG_MAP(RecView)
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CRecordView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, CRecordView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RecView construction/destruction

RecView::RecView()
    : CRecordView(RecView::IDD)
{
}

RecView::~RecView()
{
}

void RecView::DoDataExchange(CDataExchange* pDX)
{
    CRecordView::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(RecView)
    //}}AFX_DATA_MAP
    DDX_FieldText(pDX, IDC_EDIT1, m_pSet->m_id, m_pSet);
    DDX_FieldText(pDX, IDC_EDIT2, m_pSet->m_name, m_pSet);
    DDX_FieldCheck(pDX, IDC_CHECK1, m_pSet->m_manager, m_pSet);
}

BOOL RecView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CRecordView::PreCreateWindow(cs);
}

void RecView::OnInitialUpdate()
{
    m_pSet = &GetDocument()->m_set;
    CRecordView::OnInitialUpdate();
    GetParentFrame()->RecalcLayout();
    ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// RecView printing

BOOL RecView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void RecView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void RecView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// RecView diagnostics

#ifdef _DEBUG
void RecView::AssertValid() const
{
    CRecordView::AssertValid();
}

void RecView::Dump(CDumpContext& dc) const
{
    CRecordView::Dump(dc);
}

Doc* RecView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Doc)));
    return (Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// RecView database support
CRecordset* RecView::OnGetRecordset()
{
    return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// RecView message handlers

void RecView::OnPrint(CDC* pDC, CPrintInfo* pInfo) {
    const int pageWidth = pDC->GetDeviceCaps(HORZRES);

    CFont printFont;
    printFont.CreatePointFont(100, _T("Times New Roman"), pDC);
    CFont* pOldFont = pDC->SelectObject(&printFont);

    const CSize textSize = pDC->GetTextExtent(_T("Sample"));
    const int margin = textSize.cx;
    const int rowHeight = textSize.cy * 3;
    int y = margin * 2;

    const int colIdX = pageWidth / 12;
    const int colNameX = colIdX * 3;
    const int colManagerX = colIdX * 7;
    const int colEndX = pageWidth - margin;

    pDC->DrawText(_T("ID"), CRect(colIdX, y, colNameX, y + rowHeight), DT_LEFT);
    pDC->DrawText(_T("Name"), CRect(colNameX, y, colManagerX, y + rowHeight), DT_LEFT);
    pDC->DrawText(_T("Manager"), CRect(colManagerX, y, colEndX, y + rowHeight), DT_LEFT);

    y += rowHeight;
    pDC->MoveTo(margin, y);
    pDC->LineTo(colEndX, y);
    y += textSize.cy;

    Set recordSet;
    recordSet.Open();

    while (!recordSet.IsEOF()) {
        CString idStr;
        idStr.Format(_T("%d"), recordSet.m_id);

        pDC->DrawText(idStr, CRect(colIdX, y, colNameX, y + rowHeight), DT_LEFT);
        pDC->DrawText(recordSet.m_name, CRect(colNameX, y, colManagerX, y + rowHeight), DT_LEFT);

        CString managerStr = recordSet.m_manager ? _T("Yes") : _T("No");
        pDC->DrawText(managerStr, CRect(colManagerX, y, colEndX, y + rowHeight), DT_LEFT);

        y += rowHeight;
        recordSet.MoveNext();
    }

    pDC->SelectObject(pOldFont);
}