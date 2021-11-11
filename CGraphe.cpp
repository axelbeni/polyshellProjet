
#include "Cexception.hpp"
#include "CGraphe.hpp"
#define POSITION_DEL_INEXISTANTE 9
#define INDICE_INEXISTANT 10
#define BAD_REALLOC 126
using namespace std;


void CGraphe::GRAAjouterSommet(unsigned int uiNum, CSommet & SOMParam)
{
	if (uiNum > uiGRACmptSommet+1) {
		CExeption EXEObject(POSITION_DEL_INEXISTANTE);
		throw EXEObject;
	}
	CGraphe *GRAtemp = new CGraphe(*this);
	delete this;
	uiGRACmptSommet = GRAtemp->uiGRACmptSommet + 1;
	pGRAListe = new CSommet[uiGRACmptSommet];

	for (unsigned int uiBoucle = 0; uiBoucle <uiGRACmptSommet-1 ; uiBoucle++)
	{
		pGRAListe[uiBoucle] = GRAtemp->pGRAListe[uiBoucle];
	}
	for (unsigned int uiBoucle = uiGRACmptSommet - 1; uiBoucle >uiNum; uiBoucle--)
	{
		pGRAListe[uiBoucle] = pGRAListe[uiBoucle-1];
	}
	pGRAListe[uiNum] = SOMParam;
}

void CGraphe::GRASupprimerSommet(unsigned int uiNum)
{
	if (uiNum > uiGRACmptSommet) {
		
		CExeption EXEObject(POSITION_DEL_INEXISTANTE);
		throw EXEObject;
	}
	
	for (unsigned int uiBoucle = uiNum ; uiBoucle < uiGRACmptSommet-1; uiBoucle++)
	{
		pGRAListe[uiBoucle] = pGRAListe[uiBoucle+1];
	}
	uiGRACmptSommet--;
}

void CGraphe::GRAModifierSommet(unsigned int uiNum, CSommet & SOMParam)
{
	if (uiNum> uiGRACmptSommet)
	{
		CExeption EXObjet(INDICE_INEXISTANT);
		throw EXObjet;

	}
   pGRAListe[uiNum] = SOMParam;
}
void CGraphe::operator =(CGraphe & GRAVal) {
	if (pGRAListe !=nullptr) {
		delete[] pGRAListe;
	}
	uiGRACmptSommet = GRAVal.uiGRACmptSommet;
	pGRAListe = new CSommet[uiGRACmptSommet];
	for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet; uiBoucle++)
	{
		pGRAListe[uiBoucle] = GRAVal.pGRAListe[uiBoucle];
	}

}

CGraphe::CGraphe()
{
	pGRAListe = nullptr;
	uiGRACmptSommet = 0;
}

CGraphe::CGraphe(CGraphe & GRAParam)
{
	uiGRACmptSommet = GRAParam.uiGRACmptSommet;
	pGRAListe = new CSommet[uiGRACmptSommet];
	for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet; uiBoucle++)
	{
		pGRAListe[uiBoucle] = GRAParam.pGRAListe[uiBoucle];
	}

}

CGraphe::CGraphe(CSommet & SOMList, unsigned int uiNbSommet)
{
	uiGRACmptSommet = uiNbSommet;
	*pGRAListe = SOMList;
}

CGraphe::~CGraphe()
{
	delete [] pGRAListe;
}



CSommet & CGraphe::GRAlireSommetA(unsigned int uiPosition) {
	if (uiPosition > uiGRACmptSommet)
	{
		CExeption EXObjet(INDICE_INEXISTANT);
		throw EXObjet;

	}
	return pGRAListe[uiPosition];


}
void CGraphe::GRAAfficher() {
	for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet; uiBoucle++)
	{
		pGRAListe[uiBoucle].SOMAfficher();
	
	}
}
void CGraphe::GRAAfficherOrienter()
{
		for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet; uiBoucle++)
		{
			for(unsigned int uiBoucle1=0 ;uiBoucle1 < pGRAListe[uiBoucle].SOMlireNbArcPartant();uiBoucle1++)
			cout << pGRAListe[uiBoucle].SOMLireNumero() << "-->" << pGRAListe[uiBoucle].SOMLireArcPartant()[uiBoucle1]->ARCLireDestination() <<endl;
			for (unsigned int uiBoucle1 = 0; uiBoucle1 < pGRAListe[uiBoucle].SOMlireNbArcArrivant(); uiBoucle1++)
				cout << pGRAListe[uiBoucle].SOMLireNumero() << "<--" << pGRAListe[uiBoucle].SOMLireArcArrivant()[uiBoucle1]->ARCLireDestination() << endl;

		}
	
}
void CGraphe::GRAReverse()
{
	for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet; uiBoucle++)
		pGRAListe[uiBoucle].SOMReverse();
}
void CGraphe::GRASupprimerSommet()
{
	uiGRACmptSommet--;
}
unsigned int CGraphe::GRAGetNbSommet()
{
	return uiGRACmptSommet;
}
void CGraphe::GRASetNbSommet(unsigned int uiNbSommet)
{
	uiGRACmptSommet = uiNbSommet;
}
void CGraphe::GRAAjouterSommet( CSommet & SOMParam)
{
	uiGRACmptSommet++;
	if(uiGRACmptSommet == 1)
		pGRAListe = new CSommet[uiGRACmptSommet];
	else
	{
		CSommet* SOMtemp = new CSommet[uiGRACmptSommet];
		for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet - 1; uiBoucle++)
		{
			SOMtemp[uiBoucle] = pGRAListe[uiBoucle];
		}
		delete[] pGRAListe;
		pGRAListe = new CSommet[uiGRACmptSommet];
		for (unsigned int uiBoucle = 0; uiBoucle < uiGRACmptSommet - 1; uiBoucle++)
		{
			pGRAListe[uiBoucle] = SOMtemp[uiBoucle];
		}
		delete[] SOMtemp;
	}

	pGRAListe[uiGRACmptSommet-1] = SOMParam;
}
