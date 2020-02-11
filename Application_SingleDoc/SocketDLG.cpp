// SocketServer.cpp : implementation file
//
#pragma once
#include "stdafx.h"
#include "Application_SingleDoc.h"
#include "SocketDLG.h"
#include "afxdialogex.h"


// CSocketServer dialog

IMPLEMENT_DYNAMIC(CSocketDLG, CDialogEx)

CSocketDLG::CSocketDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSocketDLG::IDD, pParent)
	, m_ValeurAdresseIP(_T("172.20.28.5"))
	, m_ValeurIdentifiant(_T("applicationPC"))
	, m_ValeurNomBDD(_T("climatiseur"))
{
	
}

CSocketDLG::~CSocketDLG()
{
}

void CSocketDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADR_IP, m_ValeurAdresseIP);
	DDX_Text(pDX, IDC_ID_SERV, m_ValeurIdentifiant);
	DDX_Text(pDX, IDC_PASSW_SERV, m_ValeurMotDePasse);
	DDX_Text(pDX, IDC_NOMBDD, m_ValeurNomBDD);
}

BOOL CSocketDLG::OnInitDialog()
{
	UpdateData(false);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CSocketDLG, CDialogEx)
END_MESSAGE_MAP()

// CSocketServer message handlers


std::string* CSocketDLG::Retourne_IP_ID_MDP_BDD()
{
	CT2CA ConvertCStringEnStringIP(m_ValeurAdresseIP);	//Methode de conversion de CString
	CT2CA ConvertCStringEnStringID(m_ValeurIdentifiant);//en std::string
	CT2CA ConvertCStringEnStringMDP(m_ValeurMotDePasse);
	CT2CA ConvertCStringEnStringBDD(m_ValeurNomBDD);

	listeParametres[0] = ConvertCStringEnStringIP;
	listeParametres[1] = ConvertCStringEnStringID;
	listeParametres[2] = ConvertCStringEnStringMDP;
	listeParametres[3] = ConvertCStringEnStringBDD;
	return listeParametres;
}

void CSocketDLG::OnOK()
{
	UpdateData(true);
	CDialogEx::OnOK();
}