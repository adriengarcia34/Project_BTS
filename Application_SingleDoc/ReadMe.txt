================================================================================
    BIBLIOTH�QUE MICROSOFT FOUNDATION CLASS : Vue d'ensemble du projet 
    Application_SingleDoc
================================================================================

L'Assistant Application a cr�� cette application Application_SingleDoc pour 
vous.  Cette application d�crit les principes de base de l'utilisation de 
Microsoft Foundation Classes et vous permet de cr�er votre application.

Ce fichier contient un r�sum� du contenu de chacun des fichiers qui constituent 
votre application Application_SingleDoc.

Application_SingleDoc.vcxproj
    Il s'agit du fichier projet principal pour les projets VC++ g�n�r�s � l'aide 
    d'un Assistant Application. 
    Il contient les informations sur la version de Visual C++ qui a g�n�r� le 
    fichier et des informations sur les plates-formes, configurations et 
    fonctionnalit�s du projet s�lectionn�es avec l'Assistant Application.

Application_SingleDoc.vcxproj.filters
    Il s'agit du fichier de filtres pour les projets VC++ g�n�r�s � l'aide d'un 
    Assistant Application. 
    Il contient des informations sur l'association entre les fichiers de votre 
    projet et les filtres. Cette association est utilis�e dans l'IDE pour 
    afficher le regroupement des fichiers qui ont des extensions similares sous 
    un n�ud sp�cifique (par exemple, les fichiers ".cpp" sont associ�s au 
    filtre "Fichiers sources").

Application_SingleDoc.h
    Il s'agit du fichier d'en-t�te principal de l'application.  Il contient 
    d'autres en-t�tes de projet sp�cifiques (y compris Resource.h) et d�clare 
    la classe d'application CApplication_SingleDocApp.

Application_SingleDoc.cpp
    Il s'agit du fichier source principal de l'application qui contient la 
    classe d'application CApplication_SingleDocApp.

Application_SingleDoc.rc
    Il s'agit de la liste de toutes les ressources Microsoft Windows que le 
    programme utilise.  Elle comprend les ic�nes, les bitmaps et les curseurs 
    qui sont stock�s dans le sous-r�pertoire RES. Ce fichier peut �tre modifi� 
    directement dans Microsoft Visual C++. Vos ressources de projet sont dans 
    1036.

res\Application_SingleDoc.ico
    Il s'agit d'un fichier ic�ne, qui est utilis� comme ic�ne de l'application.  
    Cette ic�ne est incluse par le fichier de ressource principal 
    Application_SingleDoc.rc.

res\Application_SingleDoc.rc2
    Ce fichier contient les ressources qui ne sont pas modifi�es par Microsoft  
    Visual C++. Vous devez placer toutes les ressources non modifiables par 
    l'�diteur de ressources dans ce fichier.

/////////////////////////////////////////////////////////////////////////////

Pour la fen�tre frame principale :
    Le projet comprend une interface MFC standard.

MainFrm.h, MainFrm.cpp
    Ces fichiers contiennent la classe de frame CMainFrame 
    d�riv�e de
    CFrameWnd et qui contr�le toutes les fonctionnalit�s des frames SDI.

/////////////////////////////////////////////////////////////////////////////

L'Assistant Application cr�e un type de document et une vue :

Application_SingleDocDoc.h, Application_SingleDocDoc.cpp - le document
    Ces fichiers contiennent votre classe CApplication_SingleDocDoc.  Modifiez ces 
fichiers pour 
    ajouter les donn�es de document sp�ciales et impl�menter l'enregistrement 
    et le chargement des fichiers (via CApplication_SingleDocDoc::Serialize).

Application_SingleDocView.h, Application_SingleDocView.cpp - la vue du document
    Ces fichiers contiennent votre classe CApplication_SingleDocView.
    Les objets CApplication_SingleDocView servent � afficher les objets 
    CApplication_SingleDocDoc.





/////////////////////////////////////////////////////////////////////////////

Autres fonctionnalit�s :

Prise en charge de l'impression et de l'aper�u avant impression
    L'Assistant Application a g�n�r� un code pour g�rer les commandes 
    d'impression, de configuration de l'impression et d'aper�u avant 
    impression en appelant les fonctions membres dans la classe CView, � 
    partir de la biblioth�que MFC.

/////////////////////////////////////////////////////////////////////////////

Autres fichiers standard :

StdAfx.h, StdAfx.cpp
    Ces fichiers sont utilis�s pour g�n�rer un fichier d'en-t�te pr�compil� 
    (PCH) nomm� Application_SingleDoc.pch et un fichier de type pr�compil� 
    nomm� Stdafx.obj.

Resource.h
    Il s'agit du ficher d'en-t�te standard, qui d�finit les nouveaux ID de 
    ressources.
    Microsoft Visual C++ lit et met � jour ce fichier.

Application_SingleDoc.manifest
    Les fichiers manifestes d'application sont utilis�s par Windows XP pour 
    d�crire les d�pendances des applications sur des versions sp�cifiques 
    des assemblys c�te � c�te. Le chargeur utilise ces informations pour 
    charger l'assembly appropri� � partir du cache de l'assembly ou 
    directement � partir de l'application. Le manifeste de l'application peut 
    �tre inclus pour redistribution comme fichier .manifest externe install� 
    dans le m�me dossier que l'ex�cutable de l'application ou �tre inclus 
    dans l'ex�cutable sous la forme d'une ressource. 
/////////////////////////////////////////////////////////////////////////////

Autres remarques :

L'Assistant Application utilise "TODO:" pour indiquer les parties du code 
source o� vous devrez ajouter ou modifier du code.

Si votre application utilise les MFC dans une DLL partag�e vous devez 
redistribuer les DLL MFC. Si la langue de votre application n'est pas celle 
du syst�me d'exploitation, vous devez �galement redistribuer le fichier des 
ressources localis�es MFC100XXX.DLL. Pour plus d'informations, consultez la 
section relative � la redistribution des applications Visual C++ dans la 
documentation MSDN.

/////////////////////////////////////////////////////////////////////////////
