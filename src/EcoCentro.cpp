/*
 * EcoCentro.cpp
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#include "EcoCentro.h"

namespace std {

int EcoCentro::cnt = 0;

EcoCentro::EcoCentro(Vertex<Info>* vertex):id(cnt), vertex(vertex){
	cnt++;
}

EcoCentro::~EcoCentro() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
