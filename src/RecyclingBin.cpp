/*
 * EcoPonto.cpp
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#include "RecyclingBin.h"

namespace std {

int RecyclingBin::cnt = 0;

RecyclingBin::RecyclingBin() :
		id(cnt), vertex(NULL) {
	cnt++;
}

RecyclingBin::RecyclingBin(vector<Container> containers) :
		id(cnt), containers(containers), vertex(NULL) {
	cnt++;
}

RecyclingBin::~RecyclingBin() {
	// TODO Auto-generated destructor stub
}

const vector<Container>& RecyclingBin::getContainers() const {
	return containers;
}

vector<Container*> RecyclingBin::check() {
	vector<Container*> temp;

	//cout << "Entra check \n";
	for (unsigned int i = 0; i < containers.size(); i++) {
		//cout << contentores.at(i).cOcupada / (contentores.at(i).cUtil * 1.0) << endl;
		if (containers.at(i).cOccupied / (containers.at(i).cUsable * 1.0) >= 0.7)
			temp.push_back(&containers.at(i));
	}
	return temp;
}

void RecyclingBin::setContainers(const vector<Container>& contentores) {
	this->containers = contentores;
}

const Vertex<Info> *RecyclingBin::getVertex() const {
	return vertex;
}

void RecyclingBin::setVertex(Vertex<Info>* vertex) {
	this->vertex = vertex;
}

void RecyclingBin::generateGarbage() {
	for (unsigned int i = 0; i < containers.size(); i++) {
		int n = rand() % 100;
		containers.at(i).setOcupiedCapacity(containers.at(i).getUsableCapacity() * n / 100.0);
	}
}

int RecyclingBin::getId() const {
	return id;
}

void RecyclingBin::resetCnt() {
	cnt = 0;
}

void RecyclingBin::setCapacity(Colors::Color color, double capacity) {
	vector<Container>::iterator it = containers.begin();

	for(; it != containers.end(); it++)
		if(it->getColor() == color)
			it->setOcupiedCapacity(capacity);
}

double RecyclingBin::getGarbage(Colors::Color color) {
	vector<Container>::iterator it = containers.begin();

	for(; it != containers.end(); it++)
		if(it->getColor() == color)
			return it->getOcupiedCapacity();
	return 0;
}

vector<Container*> RecyclingBin::check(Colors::Color color) {
	vector<Container*> temp;

	//cout << "Entra check \n";
	for (unsigned int i = 0; i < containers.size(); i++) {
		//cout << contentores.at(i).cOcupada / (contentores.at(i).cUtil * 1.0) << endl;
		if (containers.at(i).getColor() == color && containers.at(i).cOccupied / (containers.at(i).cUsable * 1.0) >= 0.7)
			temp.push_back(&containers.at(i));
	}
	return temp;
}

}

/* namespace std */
