	/*************************************************************************
 Nom du projet	: Bilan Energetique d'un climatiseur
 Nom du fichier	: MainFrm.cpp
 Description	: Gère la fenêtre principale de l'application
 Auteur			: Adrien GARCIA
 Environnement 	: Visual Studio 2010 
 Version		: 1.1
**************************************************************************/
// MainFrm.cpp : implémentation de la classe CMainFrame
//
#pragma once
#include "stdafx.h"
#include "Application_SingleDoc.h"
#include "ParamCamp.h"
#include "AffCourbes.h"
#include "MainFrm.h"
#include "SocketDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND(ID_PARAM_CAMP, &CMainFrame::OnParamCamp)
	ON_COMMAND(ID_AFFICHAGE_COURBES, &CMainFrame::OnAffichageCourbes)
	ON_COMMAND(SC_CLOSE , &CMainFrame::OnClose)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // indicateur de la ligne d'état
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// construction ou destruction de CMainFrame

CMainFrame::CMainFrame():ptr_Campagne(NULL)
{
	// TODO: ajoutez ici le code d'une initialisation de membre
}

CMainFrame::~CMainFrame()
{
	if(ptr_Campagne)
		delete ptr_Campagne;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	// définir le gestionnaire visuel utilisé pour dessiner tous les éléments d'interface utilisateur
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Impossible de créer la barre de menus\n");
		return -1;      // échec de la création
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// empêche la barre de menus de prendre le focus lors de l'activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	/*if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("Impossible de créer toolbar\n");
		return -1;      // échec de la création
	}*/

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	//m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
//	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// Autoriser les opérations de barres d'outils définies par l'utilisateur :
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Impossible de créer la barre d'état\n");
		return -1;      // échec de la création
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: supprimez ces cinq lignes si vous ne souhaitez pas que la barre d'outils et la barre de menus soient ancrables
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
//	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
//	DockPane(&m_wndToolBar);


	// activer le comportement de la fenêtre d'ancrage de style Visual Studio 2005
	CDockingManager::SetDockingMode(DT_SMART);
	// activer le comportement de masquage automatique de la fenêtre d'ancrage de style Visual Studio 2005
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Activer le remplacement du menu de la fenêtre d'ancrage et de la barre d'outils
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// activer la personnalisation de barre d'outils rapide (Alt+faire glisser)
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// charger les images de barre d'outils définies par l'utilisateur
//		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
//			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// activer la personnalisation de menu (commandes les plus récemment utilisées)
	// TODO: définissez vos propres commandes de base, en vous assurant que chaque menu déroulant a au moins une commande de base.
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);
	
	CParamCamp dlgParam(true,NULL,NULL);
	dlgParam.DoModal();
	ptr_Campagne = new CCampagne(dlgParam.DonneValeurCampagne()
							,dlgParam.DonneValeurDescription()
							,dlgParam.DonneValeurDate()
							,dlgParam.DonneValeurMachine()
							,dlgParam.DonneValeurLieu()
							,dlgParam.DonneValeurEchantillonnage());
	dlgParam.ApresChangementAttributs();
	CSocketDLG dlgSocket;
	bool l_socketParametree = false;
	do
	{
		dlgSocket.DoModal();
		l_socketParametree = ptr_Campagne->ParametrerSocket(dlgSocket.Retourne_IP_ID_MDP_BDD());

	}while(l_socketParametree == false);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: changez ici la classe ou les styles Window en modifiant
	//  CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_SYSMENU;

	return TRUE;
}

// diagnostics pour CMainFrame

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// gestionnaires de messages pour CMainFrame

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* analyser les menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// la classe de base effectue le travail

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// activer le bouton de personnalisation pour toutes les barres d'outils utilisateur
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}
	
	return TRUE;
}



void CMainFrame::OnParamCamp()
{
	CParamCamp dlgParam(false,ptr_Campagne,NULL);
	dlgParam.DoModal();
	if(dlgParam.EstModifie())
	{
		ptr_Campagne->ChangerAttributs(dlgParam.DonneValeurCampagne()
								,dlgParam.DonneValeurDescription()
								,dlgParam.DonneValeurDate()
								,dlgParam.DonneValeurMachine()
								,dlgParam.DonneValeurLieu()
								,dlgParam.DonneValeurEchantillonnage());

		dlgParam.ApresChangementAttributs();
	}
}


void CMainFrame::OnAffichageCourbes()
{
	CAffCourbes dlgCourbes(ptr_Campagne);
	dlgCourbes.DoModal();
}

void CMainFrame::OnClose()
{
	ptr_Campagne->FinDeCampagne();
	delete ptr_Campagne;
}