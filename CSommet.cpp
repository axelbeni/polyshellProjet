
#include <iostream>
#include "CSommet.hpp"
#include "Cexception.hpp"
#define OUT_OF_MEMORY_DEL_INDEX 3
#define OUT_OF_MEMORY_ADD_INDEX 4
#define ERR_TAILLE_ARR 1
#define ERR_TAILLE_PAR 2
#define BAD_REALLOC 123


 void CSommet::SOMEcrireNumero(unsigned int uiNumero) {
	uiSOMNumero = uiNumero;
}


unsigned int CSommet::SOMLireNumero()
{
	return uiSOMNumero;
}

CArc **CSommet::SOMLireArcArrivant()
{
	return pSOMArrivant;
}

CArc ** CSommet::SOMLireArcPartant()
{
	return pSOMPartant;
}


void CSommet::SOMSupprimerArcArrivant(unsigned int uiPosition)
{
	if (uiPosition > uiSOMCmptArr) {
		CExeption EXEObjet(OUT_OF_MEMORY_DEL_INDEX);
		throw EXEObjet;	
	}
	for (unsigned int uiBoucle = uiPosition; uiBoucle < uiSOMCmptArr-1; uiBoucle++) 
	{
		pSOMArrivant[uiBoucle] = pSOMArrivant[uiBoucle + 1];
	}
	uiSOMCmptArr--;
	pSOMArrivant=(CArc**)realloc(pSOMArrivant, uiSOMCmptArr * sizeof(CArc*));
	if (pSOMArrivant == nullptr && uiPosition) {
		CExeption EXObj(BAD_REALLOC);
		throw EXObj;
	}
}

void CSommet::SOMSupprimerArcPartant(unsigned int uiPosition)
{
	if (uiPosition > uiSOMCmptPart) {
		CExeption EXEObjet(OUT_OF_MEMORY_DEL_INDEX);
		throw EXEObjet;
	}
	for (unsigned int uiBoucle = uiPosition; uiBoucle < uiSOMCmptPart - 1; uiBoucle++)
	{
		pSOMPartant[uiBoucle] = pSOMPartant[uiBoucle + 1];
	}
	uiSOMCmptPart--;
	pSOMPartant=(CArc**)realloc(pSOMPartant, uiSOMCmptPart * sizeof(CArc*));
	if (pSOMPartant == nullptr && uiPosition) {
		CExeption EXObj(BAD_REALLOC);
		throw EXObj;
	}
}

void CSommet::SOMModifierArcArrivant(unsigned int uiNum, CArc *ARCNewValeur)
{
	if (uiNum > uiSOMCmptArr) {
		CExeption EXCObjet(ERR_TAILLE_ARR);
		throw(EXCObjet);
	}
	pSOMArrivant[uiNum] =new CArc(* ARCNewValeur);
}

void CSommet::SOMModifierArcPartant(unsigned int uiNum, CArc *ARCNewValeur)
{
	if (uiNum > uiSOMCmptPart) {
		CExeption EXCObjet(ERR_TAILLE_PAR);
		throw(EXCObjet);
	}
	pSOMPartant[uiNum] = ARCNewValeur;
}
// ic vous aviez la possibilter de ne pas choisir de position d'insertion par default elle sera inserer à la fin du tableau
void CSommet::SOMAjouterArcPartant(unsigned int uiNum, CArc *ARCTableauSource)
{
	if (uiNum > uiSOMCmptPart + 1) {
		CExeption EXEObjet(OUT_OF_MEMORY_ADD_INDEX);
		throw EXEObjet;
	}
	pSOMPartant=(CArc**)realloc(pSOMPartant, (uiSOMCmptPart + 1) * sizeof(CArc*));
	for (unsigned int uiBoucle = uiSOMCmptPart; uiBoucle < uiNum; uiBoucle--)
	{
		pSOMPartant[uiBoucle] = pSOMPartant[uiBoucle - 1];
	}
	pSOMPartant[uiNum] = new CArc(*ARCTableauSource);
	uiSOMCmptPart++;

}
void CSommet::SOMAjouterArcArrivant(unsigned int uiNum, CArc *ARCTableauSource)
{
	if (uiNum > uiSOMCmptArr + 1) {
		CExeption EXEObjet(OUT_OF_MEMORY_ADD_INDEX);
		throw EXEObjet;
	}
	pSOMArrivant=(CArc**)realloc(pSOMArrivant , (uiSOMCmptArr + 1) * sizeof(CArc*));
	for (unsigned int uiBoucle = uiSOMCmptArr; uiBoucle < uiNum; uiBoucle--)
	{
		pSOMArrivant[uiBoucle] = pSOMArrivant[uiBoucle - 1];
	}
	pSOMArrivant[uiNum] = new CArc(*ARCTableauSource);
	uiSOMCmptArr++;
}

CSommet::CSommet()
{
	pSOMArrivant = nullptr;
	pSOMPartant = nullptr;
	uiSOMCmptArr = 0;
	uiSOMCmptPart = 0;
}

CSommet::CSommet(int iNumero)
{
	uiSOMNumero = iNumero;
	pSOMPartant = nullptr;
	pSOMArrivant = nullptr;
	uiSOMCmptArr = 0;
	uiSOMCmptPart = 0;
}


CSommet::CSommet(CSommet & SOMParam)
{
	unsigned int uiBoucle1;
	uiSOMCmptArr = SOMParam.uiSOMCmptArr;
	uiSOMCmptPart = SOMParam.uiSOMCmptPart;
	pSOMArrivant = (CArc**)malloc(SOMParam.uiSOMCmptArr * sizeof(CArc*));
	//pSOMArrivant = new CArc*[SOMParam.uiSOMCmptArr];
	//pSOMPartant = new CArc*[SOMParam.uiSOMCmptPart];
	pSOMPartant = (CArc**)malloc(SOMParam.uiSOMCmptPart * sizeof(CArc*));
	for (uiBoucle1 = 0; uiBoucle1 < uiSOMCmptArr; uiBoucle1++) {
		pSOMArrivant[uiBoucle1] = new CArc(SOMParam.SOMLireArcArrivant()[uiBoucle1]->ARCLireDestination());
	}
	for (uiBoucle1 = 0; uiBoucle1 < uiSOMCmptPart; uiBoucle1++) {
		pSOMPartant[uiBoucle1] = new CArc(SOMParam.SOMLireArcPartant()[uiBoucle1]->ARCLireDestination());
	}
}
CSommet::~CSommet()
{
	unsigned int uiBoucle;
	for (uiBoucle = 0; uiBoucle < uiSOMCmptArr; uiBoucle++) {
		delete pSOMArrivant[uiBoucle];
	}
	for (uiBoucle = 0; uiBoucle < uiSOMCmptPart; uiBoucle++) {
		delete pSOMPartant[uiBoucle];
	}
	free(pSOMArrivant);
	free(pSOMPartant);
	pSOMArrivant = nullptr;
	pSOMPartant = nullptr;
}

void CSommet::operator=(CSommet & SOMParam) {
	unsigned int uiBoucle1;
	uiSOMNumero = SOMParam.SOMLireNumero();
	uiSOMCmptArr = SOMParam.uiSOMCmptArr;
	uiSOMCmptPart = SOMParam.uiSOMCmptPart;
	pSOMArrivant = (CArc**)malloc(SOMParam.uiSOMCmptArr * sizeof(CArc*));
	//pSOMArrivant = new CArc*[SOMParam.uiSOMCmptArr];
	//pSOMPartant = new CArc*[SOMParam.uiSOMCmptPart];
	pSOMPartant = (CArc**)malloc(SOMParam.uiSOMCmptPart * sizeof(CArc*));
	for (uiBoucle1 = 0; uiBoucle1 < uiSOMCmptArr; uiBoucle1++) {
		pSOMArrivant[uiBoucle1] = new CArc(SOMParam.SOMLireArcArrivant()[uiBoucle1]->ARCLireDestination());
	}
	for (uiBoucle1 = 0; uiBoucle1 < uiSOMCmptPart; uiBoucle1++) {
		pSOMPartant[uiBoucle1] = new CArc(SOMParam.SOMLireArcPartant()[uiBoucle1]->ARCLireDestination());
	}

}
void CSommet::SOMAfficher() {
	std::cout << "Sommet n°" << SOMLireNumero() << std::endl<<"arc Arrivant"<<std::endl ;
	unsigned int uiBoucle1;
	for (uiBoucle1 = 0; uiBoucle1 < uiSOMCmptArr; uiBoucle1++) {
		pSOMArrivant[uiBoucle1]->ARCAfficher();
	}
	std::cout  << "arc PARTANT" << std::endl;
	for (uiBoucle1 = 0; uiBoucle1 < uiSOMCmptPart; uiBoucle1++) {
		pSOMPartant[uiBoucle1]->ARCAfficher();
	}

}

unsigned int CSommet::SOMlireNbArcArrivant()
{
	return uiSOMCmptArr;
}

unsigned int CSommet::SOMlireNbArcPartant()
{
	return uiSOMCmptPart;
}

CSommet & CSommet::SOMReverse()
{
	CSommet * SOMTemp = new CSommet(*this);
	unsigned int uiBoucle;
	for (uiBoucle = 0; uiBoucle < uiSOMCmptArr; uiBoucle++) {
		delete pSOMArrivant[uiBoucle];
	}
	for (uiBoucle = 0; uiBoucle < uiSOMCmptPart; uiBoucle++) {
		delete pSOMPartant[uiBoucle];
	}
	free(pSOMArrivant);
	free(pSOMPartant);
	uiSOMCmptArr = SOMTemp->uiSOMCmptPart;
	uiSOMCmptPart = SOMTemp->uiSOMCmptArr;
	pSOMArrivant = (CArc**)malloc(SOMTemp->uiSOMCmptPart * sizeof(CArc*));
	//pSOMArrivant = new CArc*[SOMParam.uiSOMCmptArr];
	//pSOMPartant = new CArc*[SOMParam.uiSOMCmptPart];
	pSOMPartant = (CArc**)malloc(SOMTemp->uiSOMCmptArr * sizeof(CArc*));
	for (uiBoucle = 0; uiBoucle < uiSOMCmptArr; uiBoucle++) {
		pSOMArrivant[uiBoucle] = new CArc(SOMTemp->SOMLireArcPartant()[uiBoucle]->ARCLireDestination());
	}
	for (uiBoucle = 0; uiBoucle < uiSOMCmptPart; uiBoucle++) {
		pSOMPartant[uiBoucle] = new CArc(SOMTemp->SOMLireArcArrivant()[uiBoucle]->ARCLireDestination());
	}
	delete SOMTemp;
	return *this;
}

void CSommet::SOMAjouterArcPartant( CArc *ARCTableauSource)
{
	
	pSOMPartant=(CArc**)realloc(pSOMPartant, (uiSOMCmptPart + 1) * sizeof(CArc*));
	if (pSOMPartant == NULL) {
		CExeption EXObj(BAD_REALLOC);
		throw EXObj;
	}

	pSOMPartant[uiSOMCmptPart] = new CArc(*ARCTableauSource);
	uiSOMCmptPart++;

}
void CSommet::SOMAjouterArcArrivant( CArc *ARCTableauSource)
{
	pSOMArrivant=(CArc**)realloc(pSOMArrivant, (uiSOMCmptArr + 1) * sizeof(CArc*));
	if (pSOMArrivant == nullptr) {
		CExeption EXObj(BAD_REALLOC);
		throw EXObj;
	}
	pSOMArrivant[uiSOMCmptArr] = new CArc (*ARCTableauSource);
	uiSOMCmptArr++;
}

