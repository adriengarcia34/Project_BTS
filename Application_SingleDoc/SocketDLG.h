#pragma once

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <string>
using namespace sql;
// CSocketDLG dialog

class CSocketDLG : public CDialogEx
{
	DECLARE_DYNAMIC(CSocketDLG)

private:
	BOOL OnInitDialog();

public:
	CSocketDLG(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSocketDLG();

// Dialog Data
	enum { IDD = IDD_DLGSERV };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CString m_ValeurAdresseIP;
	CString m_ValeurIdentifiant;
	CString m_ValeurMotDePasse;
	CString m_ValeurNomBDD;

	std::string listeParametres[4];

public:
	std::string* Retourne_IP_ID_MDP_BDD();
	void OnOK();
	
};
