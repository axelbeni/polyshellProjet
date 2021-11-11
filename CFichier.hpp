#ifndef C_FICHIER_H
#define C_FICHIER_H

#include "CString.hpp"
#include <iostream>
using namespace std;

class CFichier
{
private:
	  CString sFICName;
	 FILE *pFFICpointeur;
	 int iFICStatut;
	 int iFicState;


public:
	//Constructeur par defaut 
	CFichier() ;
	~CFichier();
	// constructeur de confort qui prend directement un nom de fichier !!
	CFichier(const CString STRName);
	// Recopie FName
	CFichier(  CFichier & FName);
	//renvoie le nom du fichier defini declarer dans l'objet
	CString & FICLireName();
	// initialisation du nom {FICName =sName}
	void FICSetFileName(CString sName);
    // accesseur en lecture sur FICpointeur 
	FILE *FICGetFileDesc();
	// ouverture du Fichier
	void FICOpen();
	// renvoi le caractere sur la quelle se trouve le curseur et avance le curseur
	char FICGetChar();
	// ne fonctionne pa Fichier ouvert en mode read only :censé ajouter un charactère dans le fichier
	CString & FICGetWord();
	void  FICInputChar(char Cchar);
	// renoie True si le fichier est ouvert !!!!
	bool FICIsOpen();
	// renvoi true si on est a la fin du fichier 
	bool FICisOver();
	// ferme le fichier et reinitialise le curseur au debut du fichier
	void FICClose();
	// surcharge de >> pour lire un charactère dans un fichier de façon non exhaustive
	template <class T>
	T & operator>>(T &valeur);
	//surcharge de << :{ cout <<Cfichier valuer =>affiche le contenu de valeur sur la console}
	friend ostream & operator<<(ostream & Ooutput, CFichier & FICval);

};
CFichier::CFichier(){
	pFFICpointeur = NULL;
}
CFichier::CFichier(const CString STRName) {
	sFICName = STRName;
	pFFICpointeur = NULL;
}
CFichier::CFichier( CFichier & FName) {
	sFICName = FName.FICLireName();
	pFFICpointeur = FName.FICGetFileDesc();
}
 void CFichier::FICSetFileName(CString sName) {
	 sFICName = sName;
}
 CString & CFichier::FICLireName() {
	 return sFICName;
 }
 FILE * CFichier::FICGetFileDesc() {
	 return pFFICpointeur;
 }
 void CFichier::FICOpen() {
	 
	  iFicState = fopen_s(&pFFICpointeur,sFICName, "r");
	    
 }
 bool CFichier::FICIsOpen()
 {
	 return  (iFicState ==0) ;
}
 CFichier::~CFichier() {
	 if(FICIsOpen())fclose(pFFICpointeur);
 }
void   CFichier::FICClose() {
	rewind(pFFICpointeur);
	iFICStatut = !EOF;
	 fclose(pFFICpointeur);
	
 }
 void CFichier::FICInputChar(char c) {
	 fputc(c, pFFICpointeur);
 }
 char CFichier::FICGetChar() {
	 iFICStatut= fgetc(pFFICpointeur);
	 return iFICStatut;
 }
 ostream & operator<<(ostream & Ooutput, CFichier & FICval) {
	 FICval.FICOpen();
	 if (FICval.FICIsOpen()) {
		 while (!(FICval.FICisOver())) {
			 Ooutput << FICval.FICGetChar();
		 }
		 FICval.FICClose();
	 }
	 return Ooutput;
 }

 bool CFichier::FICisOver(){
	 return iFICStatut == EOF;
 }
 template <class T>
 T & CFichier::operator>>(T & valeur) {
	 valeur = FICGetChar();
	 return valeur;

 }
 CString & CFichier::FICGetWord() {
	 
	 char cChar= FICGetChar();
	 int som = 0;
	 if (cChar != ' ' && cChar != '\t' && cChar != '\n'  && !FICisOver()) {
		 CString *STRCurentWord = new CString();
		 while (cChar != ' ' && cChar != '\t' && cChar != '\n' &&  !FICisOver()) {
			 STRCurentWord->STRAjouterChar(cChar);
			 cChar = FICGetChar();
			 som += 1;
		 }
		 STRCurentWord->STRAjouterChar('\0');
		 return *STRCurentWord;
	 }
	 else
		 if(!FICisOver())
		 FICGetWord();

 }

#endif
