/*************************************************************************
 Nom du projet	: Bilan Energetique d'un climatiseur
 Nom du fichier	: AffCourbes.h
 Description	: Gère la fenêtre d'affichage de courbes
 Auteur			: Adrien GARCIA
 Environnement 	: Visual Studio 2010 
 Version		: 1.1
**************************************************************************/

#pragma once
#include "ChartCtrl\ChartCtrl.h"
#include "ChartCtrl\ChartLineSerie.h"
#include "Campagne.h"
#include "afxwin.h"

// CAffCourbes dialog
typedef enum{ON,OFF}t_etatTimer;

class CAffCourbes : public CDialogEx
{
	DECLARE_DYNAMIC(CAffCourbes)

public:
	CAffCourbes(CCampagne* ptr_campagne,CWnd* pParent = NULL);   // standard constructor
	virtual ~CAffCourbes();

	void OnOk(){}
// Dialog Data
	enum { IDD = IDD_DIALOG_COURBES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	BOOL OnInitDialog();


	//Fenetre graphique
	CChartCtrl m_ChartCtrlHaut;
	CChartCtrl m_ChartCtrlBas;

	//Series de points du graph haut
	CChartLineSerie* ptr_SeriePointsH[16];

	//Series de points du graph bas
	CChartLineSerie* ptr_SeriePointsB[16];

	unsigned long nbPoints;

	CButton m_ctrl_Btn_Lancer;
	CButton m_ctrl_Btn_Stop;	
	CButton m_ctrl_Btn_EditHygrometrie;
	
	BOOL m_CheckBoxChartHaut[16];
	BOOL m_CheckBoxChartBas[16];
	float m_EditBoxValeurs[16];

	t_etatTimer etatTimer;

public:
	CCampagne* ptr_Campagne;
	afx_msg void OnBnClickedButtonLancer();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonStop();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_ctrlBtnPause;
};
