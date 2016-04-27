/*
 * Contentor.cpp
 *
 */

#include "Contentor.h"


namespace std {

Contentor::Contentor(double capacidade,Cores::Cor cor){
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

Cores::Cor Contentor::getCor() const {
	return cor;
}

void Contentor::setCor(Cores::Cor cor) {
	this->cor = cor;
}

double Contentor::getUtil() const {
	return cUtil;
}

void Contentor::setUtil(double util) {
	cUtil = util;
}
} /* namespace std */
