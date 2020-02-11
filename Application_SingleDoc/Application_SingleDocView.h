
// Application_SingleDocView.h : interface de la classe CApplication_SingleDocView
//

#pragma once


class CApplication_SingleDocView : public CView
{
protected: // cr�ation � partir de la s�rialisation uniquement
	CApplication_SingleDocView();
	DECLARE_DYNCREATE(CApplication_SingleDocView)

// Attributs
public:
	CApplication_SingleDocDoc* GetDocument() const;

// Op�rations
public:

// Substitutions
public:
	virtual void OnDraw(CDC* pDC);  // substitu� pour dessiner cette vue
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Impl�mentation
public:
	virtual ~CApplication_SingleDocView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions g�n�r�es de la table des messages
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // version debug dans Application_SingleDocView.cpp
inline CApplication_SingleDocDoc* CApplication_SingleDocView::GetDocument() const
   { return reinterpret_cast<CApplication_SingleDocDoc*>(m_pDocument); }
#endif

