/*
 * Contentor.cpp
 *
 */

#include "Contentor.h"

namespace std {

Contentor::Contentor() {
	// TODO Auto-generated constructor stub

}

Contentor::Contentor(double capacidade,Cor cor){
	this->cutil = capacidade;
	this->cocupada = 0;
	this->cor = cor;
}

Contentor::~Contentor() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
