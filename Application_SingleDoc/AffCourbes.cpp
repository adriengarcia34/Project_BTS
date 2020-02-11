/*************************************************************************
 Nom du projet	: Bilan Energetique d'un climatiseur
 Nom du fichier	: AffCourbes.cpp
 Description	: Gère la fenêtre d'affichage de courbes
 Auteur			: Adrien GARCIA
 Environnement 	: Visual Studio 2010 
 Version		: 1.1
**************************************************************************/
// AffCourbes.cpp : implementation file
//
#pragma once
#include "stdafx.h"
#include "Application_SingleDoc.h"
#include "AffCourbes.h"
#include "afxdialogex.h"


// CAffCourbes dialog

IMPLEMENT_DYNAMIC(CAffCourbes, CDialogEx)

CAffCourbes::CAffCourbes(CCampagne* ptr_campagne,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAffCourbes::IDD, pParent)
	, ptr_Campagne(ptr_campagne)
	, m_ChartCtrlHaut()
	, m_ChartCtrlBas()
	, nbPoints(0)
{
	for(int i=0;i<16; i++)
	{
		ptr_SeriePointsH[i] = NULL;
		ptr_SeriePointsB[i] = NULL;
		m_EditBoxValeurs[i] = 0.0f;
		m_CheckBoxChartHaut[i] = FALSE;
		m_CheckBoxChartBas[i] = FALSE;
	}
}

CAffCourbes::~CAffCourbes()
{
	for(int i =0; i<16; i++)
	{
		ptr_SeriePointsH[i]->ClearSerie();
		ptr_SeriePointsB[i]->ClearSerie();
	}
}

void CAffCourbes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHARTDLG1, m_ChartCtrlHaut);
	DDX_Control(pDX, IDC_CHARTDLG2, m_ChartCtrlBas);

	DDX_Control(pDX, IDC_BUTTONLANCER, m_ctrl_Btn_Lancer);
	DDX_Control(pDX, IDC_BUTTONSTOP, m_ctrl_Btn_Stop);

	for(int i =0; i<16; i++)
		DDX_Check(pDX, IDC_CHECK1+i, m_CheckBoxChartHaut[i]);
	for(int i =0; i<16; i++)
		DDX_Check(pDX, IDC_CHECK17+i, m_CheckBoxChartBas[i]);	//Erreur lors du deboggage si
	for(int i =0; i<16; i++)									//les 3 DDX sont dans la meme boucle
		DDX_Text(pDX, IDC_EDIT1+i, m_EditBoxValeurs[i]);
	DDX_Control(pDX, IDC_BUTTONPAUSE, m_ctrlBtnPause);
}


BEGIN_MESSAGE_MAP(CAffCourbes, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONLANCER, &CAffCourbes::OnBnClickedButtonLancer)
	ON_BN_CLICKED(IDC_BUTTONSTOP, &CAffCourbes::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTONPAUSE, &CAffCourbes::OnBnClickedButtonPause)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAffCourbes message handlers
BOOL CAffCourbes::OnInitDialog()
{
	//Initialisation des graph
	//Graph Haut
	UpdateData(false);

	CChartStandardAxis* pBottomAxis = 
		m_ChartCtrlHaut.CreateStandardAxis(CChartCtrl::BottomAxis);

	CChartStandardAxis* pLeftAxis =
		m_ChartCtrlHaut.CreateStandardAxis(CChartCtrl::LeftAxis);

	m_ChartCtrlHaut.EnableRefresh(true);
	m_ChartCtrlHaut.SetBackColor(RGB(255,255,255));
	m_ChartCtrlHaut.SetZoomRectColor(RGB(0,0,0));
	pBottomAxis->SetDiscrete(false);
	pBottomAxis->SetAutomatic(true);
	pLeftAxis->SetAutomatic(true);
	m_ChartCtrlHaut.SetPanEnabled(false);
	m_ChartCtrlHaut.SetZoomEnabled(false);

	//Graph Haut
	CChartStandardAxis* _pBottomAxis = 
		m_ChartCtrlBas.CreateStandardAxis(CChartCtrl::BottomAxis);

	CChartStandardAxis* _pLeftAxis =
		m_ChartCtrlBas.CreateStandardAxis(CChartCtrl::LeftAxis);

	m_ChartCtrlBas.EnableRefresh(true);
	m_ChartCtrlBas.SetBackColor(RGB(255,255,255));
	m_ChartCtrlBas.SetZoomRectColor(RGB(0,0,0));
	_pBottomAxis->SetDiscrete(false);
	_pBottomAxis->SetAutomatic(true);
	_pLeftAxis->SetAutomatic(true);
	m_ChartCtrlBas.SetPanEnabled(false);
	m_ChartCtrlBas.SetZoomEnabled(false);

	return TRUE;
}

void CAffCourbes::OnBnClickedButtonLancer()
{
	(GetDlgItem(IDC_BUTTONLANCER))->EnableWindow(false);
	(GetDlgItem(IDC_BUTTONSTOP))->EnableWindow(true);
	(GetDlgItem(IDC_BUTTONPAUSE))->EnableWindow(true);

	m_ChartCtrlHaut.SetPanEnabled(false);
	m_ChartCtrlHaut.SetZoomEnabled(false);
	m_ChartCtrlBas.SetPanEnabled(false);
	m_ChartCtrlBas.SetZoomEnabled(false);

	ptr_Campagne->ChangeEtatAcquisition(true);
	m_ChartCtrlHaut.EnableRefresh(true);
	m_ChartCtrlBas.EnableRefresh(true);

	for(int i =0; i<16; i++)
	{
	if (!ptr_SeriePointsH[i])	ptr_SeriePointsH[i] = m_ChartCtrlHaut.CreateLineSerie();
	if (!ptr_SeriePointsB[i])	ptr_SeriePointsB[i] = m_ChartCtrlBas.CreateLineSerie();
	}
	SetTimer(1,ptr_Campagne->DonneEchantillonnage()*1000,NULL);
	etatTimer = ON;
}

void CAffCourbes::OnBnClickedButtonPause()
{
	(GetDlgItem(IDC_BUTTONSTOP))->EnableWindow(true);
	(GetDlgItem(IDC_BUTTONLANCER))->EnableWindow(true);
	(GetDlgItem(IDC_BUTTONPAUSE))->EnableWindow(false);

	ptr_Campagne->ChangeEtatAcquisition(false);
	
	m_ChartCtrlHaut.SetPanEnabled(true);
	m_ChartCtrlHaut.SetZoomEnabled(true);
	m_ChartCtrlBas.SetPanEnabled(true);
	m_ChartCtrlBas.SetZoomEnabled(true);

	m_ChartCtrlHaut.EnableRefresh(false);
	m_ChartCtrlBas.EnableRefresh(false);

}

void CAffCourbes::OnBnClickedButtonStop()
{
	(GetDlgItem(IDC_BUTTONSTOP))->EnableWindow(false);
	(GetDlgItem(IDC_BUTTONLANCER))->EnableWindow(false);
	(GetDlgItem(IDC_BUTTONPAUSE))->EnableWindow(false);

	m_ChartCtrlHaut.SetPanEnabled(true);
	m_ChartCtrlHaut.SetZoomEnabled(true);
	m_ChartCtrlBas.SetPanEnabled(true);
	m_ChartCtrlBas.SetZoomEnabled(true);

	ptr_Campagne->ChangeEtatAcquisition(false);
	m_ChartCtrlHaut.EnableRefresh(false);
	m_ChartCtrlBas.EnableRefresh(false);
	KillTimer(1);
	etatTimer = OFF;
}

void CAffCourbes::OnTimer(UINT_PTR nIDEvent)
{
	UpdateData(true);
	ptr_Campagne->AjouterGrandeurs();
	
	for(int i =0; i<16; i++)
	{	
		if(m_CheckBoxChartHaut[i])	ptr_SeriePointsH[i]->SetVisible(true);
		else ptr_SeriePointsH[i]->SetVisible(false);
		if(ptr_Campagne->DonneEtatAcquisition())
			((CChartXYSerie*)ptr_SeriePointsH[i])->AddPoint((ptr_Campagne->DonneEchantillonnage())*nbPoints,ptr_Campagne->DonneValeur(i));
		
		if(m_CheckBoxChartBas[i])	ptr_SeriePointsB[i]->SetVisible(true);
		else ptr_SeriePointsB[i]->SetVisible(false);
		if(ptr_Campagne->DonneEtatAcquisition())
			((CChartXYSerie*)ptr_SeriePointsB[i])->AddPoint((ptr_Campagne->DonneEchantillonnage())*nbPoints,ptr_Campagne->DonneValeur(i));

		m_EditBoxValeurs[i] = ptr_Campagne->DonneValeur(i);
		UpdateData(false);
	}
	CDialog::OnTimer(nIDEvent);
	nbPoints++;
}

