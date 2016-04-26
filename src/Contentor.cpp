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



double Contentor::getOcupada() const {
	return cOcupada;
}

void Contentor::setOcupada(double ocupada) {
	cOcupada = ocupada;
}

Contentor::Cor Contentor::getCor() const {
	return cor;
}

void Contentor::setCor(Cor cor) {
	this->cor = cor;
}

double Contentor::getUtil() const {
	return cUtil;
}

void Contentor::setUtil(double util) {
	cUtil = util;
}
} /* namespace std */
