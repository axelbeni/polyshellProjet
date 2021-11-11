// Gaphe.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*
NBSommets=3
	NBArcs=3
	Sommets=[
	Numero=1
	Numero=2
Numero=3
]
Arcs=[
Debut=1, Fin=2
Debut=2, Fin=3
Debut=3, Fin=1
]
*/
using namespace std;
#include <iostream>
#include "CGraphe.hpp"
#include "CString.hpp"
#include "CFichier.hpp"
#include "Cexception.hpp"
#define FILENO_OPEN 20 

/* u que on travaille sur unt type de fichier particulier alors la strategie repose la forme du fichier cette code ne peut etre coherente que sur le bon format 
du fichier */

CString& getWordAfterBalise(CFichier &FICTemp,char cBalise,int iNumBalise)
{
	int iBalise = 0;
	CString *result=new CString();
	FICTemp.FICOpen();
	if (FICTemp.FICIsOpen()) {
		char cChar;
		while (!FICTemp.FICisOver() && iBalise != iNumBalise)
		{
			cChar = FICTemp.FICGetChar();
			if (cChar == cBalise)iBalise++;
		}
		if (iBalise == iNumBalise) {
			*result = FICTemp.FICGetWord();
		}
		FICTemp.FICClose();

	}
	return *result;
}
CGraphe & GetAndSetGrapheInFile(CString & STRFileName)
{
	CFichier  *Fichier = new CFichier(STRFileName);
	Fichier->FICOpen();
	if (Fichier->FICIsOpen()) {
		CString *temp = new CString();
		int iNbSommet;
		int iNbArc;
		int iNumSommet;
		int iArcDebut, iArcFin;
		CArc **ARCArrivant;
		CArc **ARCPartatant;
		CSommet **SOMSommet;
		
		*temp = getWordAfterBalise(*Fichier, '=', 1);
		 iNbSommet = atoi(*temp);
		*temp = getWordAfterBalise(*Fichier, '=', 2);
	    iNbArc = atoi(*temp);
		ARCArrivant = new CArc*[iNbArc];
		ARCPartatant = new CArc*[iNbArc];
		SOMSommet = new CSommet*[iNbSommet];
		for (int iBoucle =0 ; iBoucle < iNbSommet ; iBoucle++) {
			//int iBoucle1 = 0;
			*temp = getWordAfterBalise(*Fichier, '=', iBoucle+4);
			iNumSommet= atoi(*temp);
			SOMSommet[iBoucle] = new CSommet(iNumSommet);
			//iBoucle1++;
		}
		int iNumBalise = (5 +iNbSommet);
		for (int iBoucle = 0; iBoucle < iNbArc; iBoucle++){
			*temp = getWordAfterBalise(*Fichier, '=', iNumBalise);
			iArcDebut = atoi(*temp);
			cout << iArcDebut << endl;
			ARCArrivant[iBoucle] = new CArc(iArcDebut);
			*temp = getWordAfterBalise(*Fichier, '=', iNumBalise +1);
			iArcFin= atoi(*temp);
			cout << iArcFin << endl;
			ARCPartatant[iBoucle] = new CArc(iArcFin);
			iNumBalise += 2;
		}
		for (int iBoucle = 0; iBoucle < iNbSommet; iBoucle++) {
			for (int iBoucle2 = 0; iBoucle2 < iNbArc; iBoucle2++) {
				if (SOMSommet[iBoucle]->SOMLireNumero() == ARCArrivant[iBoucle2]->ARCLireDestination())
				     SOMSommet[iBoucle]->SOMAjouterArcPartant(ARCPartatant[iBoucle2]);
				if (SOMSommet[iBoucle]->SOMLireNumero() == ARCPartatant[iBoucle2]->ARCLireDestination())
				                    SOMSommet[iBoucle]->SOMAjouterArcArrivant(ARCArrivant[iBoucle2]);
			}
		
		}
		CGraphe *GRAFinal = new CGraphe();
		for (int iBoucle = 0; iBoucle < iNbSommet; iBoucle++)
		{
			GRAFinal->GRAAjouterSommet(*SOMSommet[iBoucle]);
		}
		return *GRAFinal;
	}
	else
	{
		CExeption EXOBj(FILENO_OPEN);
		throw EXOBj;
	}
}


int main(int argc,char **argv)
{
	CString Ficname("testgraaphe.txt");
	CGraphe *GRAFinal = new CGraphe();
	try {
		*GRAFinal=GetAndSetGrapheInFile(Ficname);
		GRAFinal->GRAAfficherOrienter();
		GRAFinal->GRAAfficher();
		GRAFinal->GRAReverse();
		GRAFinal->GRAAfficherOrienter();
		GRAFinal->GRAAfficher();
		GRAFinal->GRASupprimerSommet(0);
		GRAFinal->GRAAfficherOrienter();
		GRAFinal->GRASupprimerSommet();
		CArc *test1 = new CArc(1);
		CArc *test2 = new CArc(2);
		CSommet *pSom1 = new CSommet(2);
		pSom1->SOMAjouterArcArrivant(test2);
		pSom1->SOMAjouterArcArrivant(test1);
		pSom1->SOMAjouterArcPartant(test2);
		pSom1->SOMAjouterArcPartant(test1);
		pSom1->SOMSupprimerArcArrivant(1);
		pSom1->SOMSupprimerArcArrivant(0);
		pSom1->SOMSupprimerArcPartant(1);
		pSom1->SOMSupprimerArcPartant(0);


	}
	catch (CExeption obj) {
		cout << obj.EXCLirevaleur() << endl;
	}
	delete GRAFinal;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
