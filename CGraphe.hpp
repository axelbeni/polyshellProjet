#ifndef C_GRAPHE_H
#define C_GRAPHE_H


#include "CSommet.hpp"


class CGraphe
{
private:
	CSommet *pGRAListe;

	unsigned int uiGRACmptSommet;

public:
	void GRAAjouterSommet(unsigned int uiNum, CSommet & SOMParam);

	void GRASupprimerSommet(unsigned int uiNum);

	void GRAModifierSommet(unsigned int uiNum, CSommet & SOMParam);

	CGraphe();
	void GRAAjouterSommet( CSommet & SOMParam);
	void GRASupprimerSommet();
	unsigned int GRAGetNbSommet();
	void GRASetNbSommet(unsigned int uiNbSommet);


	CGraphe(CGraphe & GRAParam);
	CGraphe(CSommet & SOMList, unsigned int uiNbSommet);
	~CGraphe();
	
	CSommet & GRAlireSommetA(unsigned int uiPosition);
	void operator=(CGraphe & GRAVal);
	void GRAAfficher();
	void GRAAfficherOrienter();
	void GRAReverse();

};
#endif
