// RecView.h : interface of the RecView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECVIEW_H__853B6D36_06B4_4C92_AE5A_AE47A448FE7A__INCLUDED_)
#define AFX_RECVIEW_H__853B6D36_06B4_4C92_AE5A_AE47A448FE7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Set;

class RecView : public CRecordView
{
protected: // create from serialization only
	RecView();
	DECLARE_DYNCREATE(RecView)

public:
	//{{AFX_DATA(RecView)
	enum { IDD = IDD_V10_FORM };
	Set* m_pSet;
	//}}AFX_DATA

// Attributes
public:
	Doc* GetDocument();

	// Operations
public:

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(RecView)
public:
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~RecView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(RecView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RecView.cpp
inline Doc* RecView::GetDocument()
{
	return (Doc*)m_pDocument;
}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECVIEW_H__853B6D36_06B4_4C92_AE5A_AE47A448FE7A__INCLUDED_)