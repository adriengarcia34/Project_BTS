/*************************************************************************
 Nom du projet	: Bilan Energetique d'un climatiseur
 Nom du fichier	: SocketBDD.h
 Description	: Gère la connection au serveur et l'envoi de données
 Auteur			: Adrien GARCIA
 Environnement 	: Visual Studio 2010 
 Version		: 1.1
**************************************************************************/

#pragma once
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <string>
#include <sstream>


using namespace sql;

class CSocketBDD
{
private:
	std::string adresse;
	std::string identifiant;
	std::string mdp;
	std::string nomBDD;

	unsigned int idCampagne;

	bool estConnecte;
	
	Driver*				ptr_driver;
	Connection*			ptr_con;
	Statement*			ptr_stmt;
	ResultSet*			ptr_res;

public:
	CSocketBDD();
	~CSocketBDD();
	bool Connecter();
	bool Deconnecter();
	bool EstConnecte()const{return estConnecte;}
	bool CreerCampagneSurBDD(CString p_nomCampagne,CString p_descritpion,CString p_date,CString p_machine,CString p_emplacement,float p_echantillonnage);
	bool EcrireSurBDD(float* ptr_valeurs, bool p_acquisitionActive);
	bool ModifierParametresConnection(std::string* p_listeParam);
	bool ModifierCampagne(CString p_nomCampagne,CString p_descritpion,CString p_date,CString p_machine,CString p_emplacement,float p_echantillonnage);
};