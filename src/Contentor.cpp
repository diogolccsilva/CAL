/*
 * Contentor.cpp
 *
 */

#include "Contentor.h"

namespace std {

Contentor::Contentor(double capacidade,Cor cor){
	this->cUtil = capacidade;
	this->cOcupada = 0;
	this->cor = cor;
}

Contentor::~Contentor() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
