/*
 * EcoPonto.cpp
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#include "EcoPonto.h"

namespace std {

EcoPonto::EcoPonto() {
	// TODO Auto-generated constructor stub

}

EcoPonto::EcoPonto(double longitude,double latitude,vector<Contentor> contentores){
	this->longitude = longitude;
	this->latitude = latitude;
	this->contentores = contentores;
}

EcoPonto::~EcoPonto() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
