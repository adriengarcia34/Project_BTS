
// Application_SingleDoc.h : fichier d'en-tête principal pour l'application Application_SingleDoc
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"       // symboles principaux


// CApplication_SingleDocApp:
// Consultez Application_SingleDoc.cpp pour l'implémentation de cette classe
//

class CApplication_SingleDocApp : public CWinAppEx
{
public:
	CApplication_SingleDocApp();


// Substitutions
public:
	virtual BOOL InitInstance();

// Implémentation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CApplication_SingleDocApp theApp;
