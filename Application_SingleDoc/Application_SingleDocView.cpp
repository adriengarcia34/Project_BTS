
// Application_SingleDocView.cpp : implémentation de la classe CApplication_SingleDocView
//

#include "stdafx.h"
// SHARED_HANDLERS peuvent être définis dans les gestionnaires d'aperçu, de miniature
// et de recherche d'implémentation de projet ATL et permettent la partage de code de document avec ce projet.
#ifndef SHARED_HANDLERS
#include "Application_SingleDoc.h"
#endif

#include "Application_SingleDocDoc.h"
#include "Application_SingleDocView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CApplication_SingleDocView

IMPLEMENT_DYNCREATE(CApplication_SingleDocView, CView)

BEGIN_MESSAGE_MAP(CApplication_SingleDocView, CView)
	// Commandes d'impression standard
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CApplication_SingleDocView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// construction ou destruction de CApplication_SingleDocView

CApplication_SingleDocView::CApplication_SingleDocView()
{
	// TODO: ajoutez ici du code de construction

}

CApplication_SingleDocView::~CApplication_SingleDocView()
{
}

BOOL CApplication_SingleDocView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: changez ici la classe ou les styles Window en modifiant
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// dessin de CApplication_SingleDocView

void CApplication_SingleDocView::OnDraw(CDC* /*pDC*/)
{
	CApplication_SingleDocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ajoutez ici le code de dessin pour les données natives
}


// impression de CApplication_SingleDocView


void CApplication_SingleDocView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CApplication_SingleDocView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// préparation par défaut
	return DoPreparePrinting(pInfo);
}

void CApplication_SingleDocView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ajoutez une initialisation supplémentaire avant l'impression
}

void CApplication_SingleDocView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ajoutez un nettoyage après l'impression
}

void CApplication_SingleDocView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CApplication_SingleDocView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// diagnostics pour CApplication_SingleDocView

#ifdef _DEBUG
void CApplication_SingleDocView::AssertValid() const
{
	CView::AssertValid();
}

void CApplication_SingleDocView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CApplication_SingleDocDoc* CApplication_SingleDocView::GetDocument() const // la version non Debug est inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CApplication_SingleDocDoc)));
	return (CApplication_SingleDocDoc*)m_pDocument;
}
#endif //_DEBUG


// gestionnaires de messages pour CApplication_SingleDocView
