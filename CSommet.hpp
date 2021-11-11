#ifndef C_SOMMET_H
#define C_SOMMET_H

#include "CArc.hpp"

class CSommet
{
private:
	unsigned int uiSOMNumero;

	CArc **pSOMArrivant;

	CArc **pSOMPartant;

	unsigned int uiSOMCmptArr;

	unsigned int uiSOMCmptPart;



public:
	//renvoit le numero du Sommet sur laquelle on se trouve : Accesseur en Lecture
	 unsigned int SOMLireNumero();
	// defini ou modifie le numero du sommet concerné:Accesseur En Ecriture
    void SOMEcrireNumero(unsigned int uiNumero);
	// renvoi la liste d'addresse  de tous les arcs arrivant au  Somment 
	CArc **SOMLireArcArrivant();
	// renvoi la liste d'addresse  de tous les arcs partant du Somment 
	CArc **SOMLireArcPartant();
/**  @brief : supprime un Arc précis soit dans le arrivant ou dans les partant 
              il faut au préable connaitre la position de l'arc à supprimer
	@param : uiPosition
*/
	void SOMSupprimerArcArrivant(unsigned int uiPosition);
	void SOMSupprimerArcPartant(unsigned int uiPosition);

	void SOMModifierArcArrivant(unsigned int uiNum, CArc *ARCNewValeur);
	void SOMModifierArcPartant(unsigned int uiNum, CArc *ARCNewValeur);
	/**  @brief : Ajoute un Arc précis soit dans le arrivant ou dans les partant
			  si aucune valeur n'est preciser par default ce sera à la fin du tableau 
	@param : uiPosition ou rien 
*/

	void SOMAjouterArcPartant(unsigned int uiNum, CArc *ARCTableauSource);
	void SOMAjouterArcArrivant(unsigned int uiNum, CArc *ARCTableauSource);
	void SOMAjouterArcPartant( CArc *ARCTableauSource);
	void SOMAjouterArcArrivant( CArc *ARCTableauSource);

	CSommet();
	CSommet(int iNumero);
	//CSommet(int iNumero , CArc **pARCArrivant,CArc **pARCPartant);

	CSommet(CSommet & SOMParam);
	~CSommet();
	void operator=(CSommet & SOMvaleur);
	void SOMAfficher();
	unsigned int SOMlireNbArcArrivant();
	unsigned int SOMlireNbArcPartant();
	CSommet & SOMReverse();
};
#endif
