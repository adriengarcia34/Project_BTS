/*************************************************************************
 Nom du projet	: Bilan Energetique d'un climatiseur
 Nom du fichier	: Campagne.h
 Description	: Contient les paramètres de la campagne
 Auteur			: Adrien GARCIA
 Environnement 	: Visual Studio 2010 
 Version		: 1.1
**************************************************************************/
#pragma once
#include "stdafx.h"
#include "SocketBDD.h"


class CCampagne
{
private:
	float liste_grandeurs[16];

	float echantillonnage;
	CString nomCampagne;
	CString description;
	CString date;
	CString machine;
	CString emplacement;
	CSocketBDD socket;

	bool campagneCreeeSurBDD;
	bool acquisitionActive;

public:
	CCampagne(CString p_nomCampagne,CString p_descritpion,CString p_date,CString p_machine,CString p_emplacement,float p_echantillonnage);
	~CCampagne();
	unsigned char AjouterGrandeurs();
	bool Sauvegarder();
	void ChangerAttributs(CString p_nomCampagne,CString p_descritpion,CString p_date,CString p_machine,CString p_emplacement,float p_echantillonnage);
	float DonneValeur(unsigned char p_valeur)const{return liste_grandeurs[p_valeur];}
	bool ParametrerSocket(std::string* p_listeParam);

	void FinDeCampagne();

	void ChangeEtatAcquisition(bool p_nouvelEtat);
	bool DonneEtatAcquisition()const{return acquisitionActive;}

	float	DonneEchantillonnage()const{return echantillonnage;}
	CString DonneNomCampagne()const{return nomCampagne;}
	CString DonneDescription()const{return description;}
	CString DonneDate()const{return date;}
	CString DonneMachine()const{return machine;}
	CString DonneEmplacement()const{return emplacement;}
};