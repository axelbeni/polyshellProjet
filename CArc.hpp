#ifndef C_ARC_H
#define C_ARC_H

#include <iostream>


class CArc
{
private:
	unsigned int uiARCDestination;

public:
	CArc();
	void ARCAfficher();
	//accesseur en lecture de la destination de l'arc
	 unsigned int ARCLireDestination();
	// accesseur en Ecriture de la destination de l'arc 
	 void ARCEcrireDestination(unsigned int uiValeur);
  // constructeur de confort qui fait le racourcie de deux operation declarer une CArc tout en affectons la destination
	CArc(unsigned int uiValue);
// constructeur de recopie permet d'intinatialiser une instance de Carc grace à une autre existante
	CArc(CArc &  ARCParam);

};
#endif
