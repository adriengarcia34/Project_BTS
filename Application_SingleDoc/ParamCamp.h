/*************************************************************************
 Nom du projet	: Bilan Energetique d'un climatiseur
 Nom du fichier	: ParamCamp.h
 Description	: Gère la fenêtre de paramétrage de la campagne
 Auteur			: Adrien GARCIA
 Environnement 	: Visual Studio 2010 
 Version		: 1.1
**************************************************************************/

#pragma once
#include "Campagne.h"
// CParamCamp dialog


class CParamCamp : public CDialogEx
{
	DECLARE_DYNAMIC(CParamCamp)

public:
	CParamCamp(bool p_firstOpen = false,CCampagne* p_campagne = NULL,CWnd* pParent = NULL);   // standard constructor
	virtual ~CParamCamp();

// Dialog Data
	enum { IDD = IDD_DIALOG_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	bool modif;		//Parametres de la campagne modifiés
	bool firstOpen;
	
	CString m_ValeurEditCampagne;
	float m_ValeurEditEchantillonnage;
	CString m_ValeurEditMachine;
	CString m_ValeurEditLieu;
	CString m_ValeurEditDescription;
	COleDateTime m_ValeurDate;
	CString m_ValeurDateString;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	bool EstModifie()const{return modif;}
	void ApresChangementAttributs();
	CString DonneValeurCampagne()const{return m_ValeurEditCampagne;}
	CString DonneValeurMachine()const{return m_ValeurEditMachine;}
	CString DonneValeurLieu()const{return m_ValeurEditLieu;}
	CString DonneValeurDescription()const{return m_ValeurEditDescription;}
	CString DonneValeurDate()const{return m_ValeurDateString;}
	float DonneValeurEchantillonnage()const{return m_ValeurEditEchantillonnage;}
};
