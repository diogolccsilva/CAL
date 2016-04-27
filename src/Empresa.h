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
#include <map>

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
	map<Cores::Cor, vector<Camiao*>> camioes;
	vector<Camiao> vcamioes;
	vector<EcoCentro> ecocentros;
	void readMapa();
	bool createRandomEcoPonto(Vertex<Info> *vertex);
	void createEcoPonto(Vertex<Info>* vertex);
	void createGraphViewer();
	double recolhaAux(int ids, int idd, queue<EcoPonto*> &q,
			vector<EcoPonto*> pinteresses);
public:
	Empresa();
	virtual ~Empresa();
	//EcoCentros
	const vector<EcoCentro>& getEcocentros() const;
	void addEcocentro(const EcoCentro ecocentro);
	//EcoPontos
	const vector<EcoPonto>& getEcopontos() const;
	void addEcoponto(const EcoPonto ecoponto);
	int createRandomEcoPontos();
	bool createEcoPonto(int idv);
	int eraseEcoPontos();
	bool removeEcoPonto(int id);
	//Camioes
	const map<Cores::Cor, vector<Camiao*>>& getCamioes() const;
	void addCamiao(Camiao& camiao);
	int createCamioes();
	//Utilidades
	string recolha(int ids, int idd);
	vector<EcoPonto*> getPontosInt();
	string shortestPath(int ids, int idd);
	string getSCamioes() const;
	string getSCentros() const;
	string getSPontos() const;
	int geraLixo();
	const Graph<Info> getMapa() const;
	double getLixoTotal(Cores::Cor cor);
	void dynamic();
};

} /* namespace std */

#endif /* SRC_EMPRESA_H_ */
