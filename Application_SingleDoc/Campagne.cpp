/*************************************************************************
 Nom du projet	: Bilan Energetique d'un climatiseur
 Nom du fichier	: SocketBDD.cpp
 Description	: Contient les paramètres de la campagne
 Auteur			: Adrien GARCIA
 Environnement 	: Visual Studio 2010 
 Version		: 1.1
**************************************************************************/

#pragma once
#include "stdafx.h"
#include "Campagne.h"
#include <iostream>
#include <conio.h>

using namespace std;


CCampagne::CCampagne(CString p_nomCampagne,CString p_descritpion,CString p_date,CString p_machine,CString p_emplacement,float p_echantillonnage)
	:nomCampagne(p_nomCampagne)
	,description(p_descritpion)
	,date(p_date)
	,emplacement(p_emplacement)
	,machine(p_machine)
	,echantillonnage(p_echantillonnage)
	,socket()
	,campagneCreeeSurBDD(false)
	,acquisitionActive(false)
{
	for(int i=0; i<16; i++)
		liste_grandeurs[i] = 0;
}

CCampagne::~CCampagne()
{
	for(int i=0; i<16; i++)
		liste_grandeurs[i] = 0;
}


void CCampagne::ChangerAttributs(CString p_nomCampagne,CString p_descritpion,CString p_date,CString p_machine,CString p_emplacement,float p_echantillonnage)
{
	nomCampagne = p_nomCampagne;
	description = p_descritpion;
	machine = p_machine;
	emplacement = p_emplacement;
	echantillonnage = p_echantillonnage;
	date = p_date;
}


unsigned char CCampagne::AjouterGrandeurs()
{
	unsigned char l_retour = 0;

	//Manipulation pour ajouter une grandeur
	for(int i = 0; i<16;i++)
	{
		if(!liste_grandeurs[i])	liste_grandeurs[i] = i + 1;
		else liste_grandeurs[i]++;
	}
	Sauvegarder();
	
	return l_retour;	//en retour :
						//0 = tout bon
						//1 = BDD pas co
						//2 = Sauv raté
}

bool CCampagne::Sauvegarder()
{
	bool l_retour = false;
	//Ecrire sur la BDD
	if(socket.EstConnecte())
	{
		if(!campagneCreeeSurBDD)
		{
			campagneCreeeSurBDD = socket.CreerCampagneSurBDD(nomCampagne,description,date,machine,emplacement,echantillonnage);
		}
		if(campagneCreeeSurBDD)
		{
			l_retour = socket.EcrireSurBDD(liste_grandeurs,acquisitionActive);
		}
	}
	return l_retour;	//Si faux, afficher une msgbox
}

bool CCampagne::ParametrerSocket(std::string* p_listeParam)
{
	bool l_socketOK = false;
	l_socketOK = socket.ModifierParametresConnection(p_listeParam);
	if(l_socketOK)
	{
		MessageBox(NULL,_T("Connection établie"),_T("Connection OK"),NULL);
		l_socketOK = true;
	}
	else
	{
		MessageBox(NULL,_T("Connection échouée. Vérifiez vos paramètres de connection"),_T("Connection Echec"),MB_ICONERROR);
	}
	return l_socketOK;
}

void CCampagne::ChangeEtatAcquisition(bool p_nouvelEtat)
{
	acquisitionActive = p_nouvelEtat;
}

void CCampagne::FinDeCampagne()
{
	socket.Deconnecter();
}