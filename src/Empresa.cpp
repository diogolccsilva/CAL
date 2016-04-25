/*
 * Empresa.cpp
 *
 *  Created on: Apr 25, 2016
 *      Author: Diogo
 */

#include "Empresa.h"

namespace std {

Empresa::Empresa() {
	// TODO Auto-generated constructor stub

}

const vector<Camiao>& Empresa::getCamioes() const {
	return camioes;
}

void Empresa::setCamioes(const vector<Camiao>& camioes) {
	this->camioes = camioes;
}

const vector<EcoCentro>& Empresa::getEcocentros() const {
	return ecocentros;
}

void Empresa::setEcocentros(const vector<EcoCentro>& ecocentros) {
	this->ecocentros = ecocentros;
}

const vector<EcoPonto>& Empresa::getEcopontos() const {
	return ecopontos;
}

void Empresa::setEcopontos(const vector<EcoPonto>& ecopontos) {
	this->ecopontos = ecopontos;
}

const Graph<Info>& Empresa::getMapa() const {
	return mapa;
}

void Empresa::addCamiao(const Camiao camiao) {
	camioes.push_back(camiao);
}

void Empresa::addEcocentro(const EcoCentro ecocentro) {
	ecocentros.push_back(ecocentro);
}

void Empresa::addEcoponto(const EcoPonto ecoponto) {
	ecopontos.push_back(ecoponto);
}

void Empresa::setMapa(const Graph<Info>& mapa) {
	this->mapa = mapa;
}

Empresa::~Empresa() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
