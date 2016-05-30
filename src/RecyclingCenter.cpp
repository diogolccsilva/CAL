/*
 * EcoCentro.cpp
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#include "RecyclingCenter.h"

using namespace std;

int RecyclingCenter::cnt = 0;

RecyclingCenter::RecyclingCenter(Vertex<Info>* vertex):id(cnt), vertex(vertex){
	cnt++;
}

RecyclingCenter::~RecyclingCenter() {
	// TODO Auto-generated destructor stub
}

const Vertex<Info>* RecyclingCenter::getVertex() const {
	return vertex;
}

int RecyclingCenter::getId() const {
	return id;
}

void RecyclingCenter::resetCnt() {
	cnt = 0;
}
