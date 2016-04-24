/*
 * Contentor.cpp
 *
 */

#include "Contentor.h"


namespace std {

Contentor::Contentor(double capacidade,Cor cor){
	srand(time(NULL));
	double n=rand()%100;

	this->cUtil = capacidade;
	this->cOcupada = capacidade*(n/100.0);
	this->cor = cor;
}

Contentor::~Contentor() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
