
// Application_SingleDocDoc.h : interface de la classe CApplication_SingleDocDoc
//


#pragma once


class CApplication_SingleDocDoc : public CDocument
{
protected: // cr�ation � partir de la s�rialisation uniquement
	CApplication_SingleDocDoc();
	DECLARE_DYNCREATE(CApplication_SingleDocDoc)

// Attributs
public:

// Op�rations
public:

// Substitutions
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Impl�mentation
public:
	virtual ~CApplication_SingleDocDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions g�n�r�es de la table des messages
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Fonction d'assistance qui d�finit le contenu de recherche pour un gestionnaire de recherche
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
