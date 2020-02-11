/*************************************************************************
 Nom du projet	: Bilan Energetique d'un climatiseur
 Nom du fichier	: ParamCamp.cpp
 Description	: Gère la fenêtre de paramétrage de la campagne
 Auteur			: Adrien GARCIA
 Environnement 	: Visual Studio 2010 
 Version		: 1.1
**************************************************************************/
// ParamCamp.cpp : implementation file
//
#pragma once
#include "stdafx.h"
#include "Application_SingleDoc.h"
#include "ParamCamp.h"
#include "afxdialogex.h"
#include "resource.h"
#include <sstream>

// CParamCamp dialog

IMPLEMENT_DYNAMIC(CParamCamp, CDialogEx)

CParamCamp::CParamCamp(bool p_firstOpen,CCampagne* p_campagne, CWnd* pParent /*=NULL*/)
	: CDialogEx(CParamCamp::IDD, pParent)
	, m_ValeurEditCampagne(_T(""))
	, m_ValeurEditEchantillonnage(0)
	, m_ValeurEditMachine(_T(""))
	, m_ValeurEditLieu(_T(""))
	, m_ValeurEditDescription(_T(""))
	, m_ValeurDate(COleDateTime::GetCurrentTime())
	, modif(false)
	, firstOpen(p_firstOpen)
{
	if(p_campagne)
	{
		m_ValeurEditCampagne = p_campagne->DonneNomCampagne();
		m_ValeurEditEchantillonnage = p_campagne->DonneEchantillonnage();
		m_ValeurEditMachine = p_campagne->DonneMachine();
		m_ValeurEditLieu = p_campagne->DonneEmplacement();
		m_ValeurEditDescription = p_campagne->DonneDescription();
	}
}

CParamCamp::~CParamCamp()
{
}

void CParamCamp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CAMPAGNE, m_ValeurEditCampagne);
	DDX_Text(pDX, IDC_ECHANTILLONNAGE, m_ValeurEditEchantillonnage);
	DDX_Text(pDX, IDC_MACHINE, m_ValeurEditMachine);
	DDX_Text(pDX, IDC_EMPLACEMENT, m_ValeurEditLieu);
	DDX_Text(pDX, IDC_DESCRIPTION, m_ValeurEditDescription);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_ValeurDate);
}


BEGIN_MESSAGE_MAP(CParamCamp, CDialogEx)
	ON_BN_CLICKED(IDOK, &CParamCamp::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CParamCamp::OnBnClickedCancel)
END_MESSAGE_MAP()


// CParamCamp message handlers


void CParamCamp::OnBnClickedOk()
{
	UpdateData(true);
	// Pour que la chaine soit conforme à la systaxe attendue pour la future requete SQL
	// Je la met sous la forme necessaire
	std::stringstream l_date;
	l_date<<m_ValeurDate.GetYear()<<'-'<<m_ValeurDate.GetMonth()<<'-'<<m_ValeurDate.GetDay()<<' '<<m_ValeurDate.GetHour()<<':'<<m_ValeurDate.GetMinute()<<':'<<m_ValeurDate.GetSecond();
	m_ValeurDateString = l_date.str().c_str();
	
	if(m_ValeurEditCampagne != ""&& m_ValeurEditEchantillonnage >= 1.0f && m_ValeurEditEchantillonnage <= 500.0f)
	{
		modif = true;
		CDialogEx::OnOK();
	}
	else
	{
		if(m_ValeurEditCampagne == "")
		{
			MessageBox(_T("Vous devez donner un nom à votre campagne"),_T("Pas de nom"),MB_ICONEXCLAMATION);
		}
		else
		if(m_ValeurEditEchantillonnage < 1.0f || m_ValeurEditEchantillonnage > 500.0f)
		{
			MessageBox(_T("Vous devez donner une valeur d'echantillonnage entre 1s et 5min"),_T("Echantillonnage incorrect"),MB_ICONEXCLAMATION);
		}
	}
}


void CParamCamp::OnBnClickedCancel()
{
	if(!firstOpen) CDialogEx::OnCancel();
	else MessageBox(_T("Vous ne pouvez pas annuler"),_T("Erreur"),MB_ICONEXCLAMATION);
}

void CParamCamp::ApresChangementAttributs()
{
	modif = false;
}