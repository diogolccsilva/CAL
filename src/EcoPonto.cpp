/*
 * EcoPonto.cpp
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#include "EcoPonto.h"

namespace std {

int EcoPonto::cnt = 0;

EcoPonto::EcoPonto():id(cnt),vertex(NULL) {
	cnt++;
}

EcoPonto::EcoPonto(vector<Contentor> contentores):id(cnt),contentores(contentores),vertex(NULL) {
	cnt++;
}

EcoPonto::~EcoPonto() {
	// TODO Auto-generated destructor stub
}

const vector<Contentor>& EcoPonto::getContentores() const {
	return contentores;
}

vector<Contentor*> EcoPonto::check() {
	vector<Contentor*> temp;
	//cout << "Entra check \n";
	for (unsigned int i = 0; i < contentores.size(); i++) {
		//cout << contentores.at(i).cOcupada / (contentores.at(i).cUtil * 1.0) << endl;
		if (contentores.at(i).cOcupada / (contentores.at(i).cUtil * 1.0) >= 0.7)
			temp.push_back(&contentores.at(i));
	}
	return temp;
}

void EcoPonto::setContentores(const vector<Contentor>& contentores) {
	this->contentores = contentores;
}

const Vertex<Info> *EcoPonto::getVertex() const {
	return vertex;
}

void EcoPonto::setVertex(Vertex<Info>* vertex) {
	this->vertex = vertex;
}

void EcoPonto::geraLixo() {
	for (unsigned int i = 0; i < contentores.size(); i++) {
		int n = rand() % 100;
		contentores.at(i).setOcupada(contentores.at(i).getUtil() * n / 100.0);
	}
}

int EcoPonto::getId() const {
	return id;
}

void EcoPonto::resetCnt() {
	cnt = 0;
}

}

/* namespace std */
