/*
 * Camiao.cpp
 *
 */

#include "Camiao.h"

namespace std {

int Camiao::cnt = 0;

Camiao::Camiao(double cUtil,Cores::Cor cor) :
		id(cnt), cUtil(cUtil), cOcupada(0),cor(cor) {
	cnt++;
}

Camiao::~Camiao() {
	// TODO Auto-generated destructor stub
}

double Camiao::getCOcupada() const {
	return cOcupada;
}

int Camiao::getId() const {
	return id;
}

double Camiao::getCUtil() const {
	return cUtil;
}

Cores::Cor Camiao::getCor() const {
	return cor;
}

} /* namespace std */
