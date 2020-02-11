/*************************************************************************
 Nom du projet	: Bilan Energetique d'un climatiseur
 Nom du fichier	: SocketBDD.cpp
 Description	: Gère la connection au serveur et l'envoi de données
 Auteur			: Adrien GARCIA
 Environnement 	: Visual Studio 2010 
 Version		: 1.1
**************************************************************************/
#pragma once
#include "stdafx.h"
#include "SocketBDD.h"
#include <vector>

CSocketBDD::CSocketBDD()
	:adresse("")
	,identifiant("")
	,mdp("")
	,nomBDD("")
	,ptr_driver(NULL)
	,ptr_con(NULL)
	,ptr_stmt(NULL)
	,ptr_res(NULL)
	,estConnecte(false)
	,idCampagne(0)
{
	nomBDD = "";
}

CSocketBDD::~CSocketBDD()
{
	ptr_driver = NULL;
	ptr_con = NULL;
	ptr_stmt = NULL;
	ptr_res = NULL;

}

bool CSocketBDD::Connecter()
{
	estConnecte = true;
	try
	{
		ptr_driver = get_driver_instance();
		ptr_con = ptr_driver->connect(adresse,identifiant,mdp);		//Connection au serveur
		ptr_con->setSchema(nomBDD);			//Selectionner la table Campagne
	}
	catch(sql::SQLException &e)
	{
		estConnecte = false;
	}
	return estConnecte;
}

bool CSocketBDD::Deconnecter()
{
	if(estConnecte)
	{
		ptr_con->close();
		estConnecte = false;
	}
	return estConnecte;
}

bool CSocketBDD::CreerCampagneSurBDD(CString p_nomCampagne,CString p_descritpion,CString p_date,CString p_machine,CString p_emplacement,float p_echantillonnage)
{
	bool l_retour = true;
	try
	{
		std::stringstream l_commande;
		l_commande <<"INSERT INTO t_campagnedemesure(nom,date,machine,emplacement,echantillonnage,commentaire) VALUES (\""<<CW2A(p_nomCampagne)<<"\",\""<<CW2A(p_date)<<"\",\""<<CW2A(p_machine)<<"\",\""<<CW2A(p_emplacement)<<"\",\""<<p_echantillonnage*1000<<"\",\""<<CW2A(p_descritpion)<<"\");";
		ptr_stmt = ptr_con->createStatement();
		ptr_res = ptr_stmt->executeQuery(l_commande.str());
	}
	catch(sql::SQLException &e)
	{
		if(e.getErrorCode())
		{
			l_retour = false;
			MessageBox(NULL,_T("Erreur de requête SQL"),_T("Erreur SQL"),MB_ICONERROR);
		}
	}

	if(l_retour)
	{
		try
		{
			std::stringstream l_commande;
			l_commande << "SELECT MAX(`id_CampagneDeMesure`) FROM t_campagnedemesure;";
			ptr_res = ptr_stmt->executeQuery(l_commande.str());
			ptr_res->next();
			idCampagne = ptr_res->getInt("MAX(`id_CampagneDeMesure`)");
		}
		catch(sql::SQLException &e)
		{
			if(e.getErrorCode())
			{
				MessageBox(NULL,_T("Erreur de requête SQL"),_T("Erreur SQL"),MB_ICONERROR);
			}
		}
	}
	return l_retour;
}

bool CSocketBDD::EcrireSurBDD(float* ptr_valeurs,bool p_acquisitionActive)
{
	bool l_retour = true;
	static int nbValeursEcrites = 1;
	try
	{
		std::stringstream l_commande;

		l_commande << "INSERT INTO t_mesure(numero_mesure,hygrometrie,temperature,temperature_ambiante,temperature_soufflage_air,temperature_sortie_air,temperature_aspiration,temperature_refoulement,temperature_sortie_evaporateur,temperature_entree_evaporateur,temperature_sortie_detendeur,temperature_sortie_condenseur,temperature_entree_condenseur,tension_alimentation,courant,puissance,anemometre,ExtID_CampagneDeMesure) VALUES("<<nbValeursEcrites;
		for(int i = 0; i<16; i++) 
		{
			l_commande <<","<<ptr_valeurs[i]; 
		}
		l_commande <<","<<idCampagne<<");";
	
		ptr_stmt = ptr_con->createStatement();
		ptr_res = ptr_stmt->executeQuery(l_commande.str());
		
	}
	catch(sql::SQLException &e)
	{
		if(e.getErrorCode())
		{
			l_retour = false;
			MessageBox(NULL,_T("Erreur de requête SQL"),_T("Erreur SQL"),MB_ICONERROR);
		}
	}
	nbValeursEcrites++;
	return l_retour;
}

bool CSocketBDD::ModifierParametresConnection(std::string* p_listeParam)
{
	bool l_changementsAppliques = false;

	adresse = *p_listeParam;
	identifiant = *(p_listeParam+1);
	mdp = *(p_listeParam+2);
	nomBDD = *(p_listeParam+3);
	if(Connecter())
	{
		l_changementsAppliques = true;
	}
	return l_changementsAppliques;
}