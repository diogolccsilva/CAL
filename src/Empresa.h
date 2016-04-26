/*
 * Empresa.h
 *
 *  Created on: Apr 25, 2016
 *      Author: Diogo
 */

#ifndef SRC_EMPRESA_H_
#define SRC_EMPRESA_H_

#include <vector>
#include <fstream>
#include <sstream>

#include "Camiao.h"
#include "EcoCentro.h"
#include "EcoPonto.h"
#include "Graph.h"
#include "Info.h"
#include "Vertex.h"
#include "Rua.h"

#define _USE_MATH_DEFINES

#include <cmath>
#include <algorithm>

namespace std {

class Empresa {
	Graph<Info> mapa;
	GraphViewer *gv;
	vector<EcoPonto> ecopontos;
	vector<Camiao> camioes;
	vector<EcoCentro> ecocentros;
	void readMapa();
	bool createRandomEcoPonto(Vertex<Info> *vertex);
	void createGraphViewer();
public:
	Empresa();
	virtual ~Empresa();
	//void addNo(const Info )
	const vector<Camiao>& getCamioes() const;
	void setCamioes(const vector<Camiao>& camioes);
	void addCamiao(const Camiao camiao);
	const vector<EcoCentro>& getEcocentros() const;
	void setEcocentros(const vector<EcoCentro>& ecocentros);
	void addEcocentro(const EcoCentro ecocentro);
	const vector<EcoPonto>& getEcopontos() const;
	void setEcopontos(const vector<EcoPonto>& ecopontos);
	void addEcoponto(const EcoPonto ecoponto);
	const Graph<Info> getMapa() const;
	void setMapa(const Graph<Info>& mapa);
	void createRandomEcoPontos();
	void recolha();
	vector<EcoPonto*> getPontosInt();
	string shortestPath();
};

} /* namespace std */

#endif /* SRC_EMPRESA_H_ */
