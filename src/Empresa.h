/*
 * Empresa.h
 *
 *  Created on: Apr 25, 2016
 *      Author: Diogo
 */

#ifndef SRC_EMPRESA_H_
#define SRC_EMPRESA_H_

#include <map>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Camiao.h"
#include "Cor.h"
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
	//Mapa
	Graph<Info> mapa;
	GraphViewer *gv;
	void readMapa();
	void createGraphViewer();

	//EcoCentros
	vector<EcoCentro> ecocentros;
	void createEcoCentro(Vertex<Info>* vertex);

	//EcoPontos
	vector<EcoPonto> ecopontos;
	bool createRandomEcoPonto(Vertex<Info> *vertex);
	void createEcoPonto(Vertex<Info>* vertex);

	//Camioes
	vector<Camiao> vcamioes;
	map<Cores::Cor, vector<Camiao*>> camioes;

	//Utilidades
	double recolhaIlimitadaAux(int ids, int idd, queue<EcoPonto*> &q,
			vector<EcoPonto*> pinteresses);
public:
	Empresa();
	virtual ~Empresa();
	//Mapa
	const Graph<Info> getMapa() const;

	//EcoCentros
	const vector<EcoCentro>& getEcocentros() const;
	void addEcocentro(const EcoCentro ecocentro);
	bool createEcoCentro(int idv);
	string getSCentros() const;

	//EcoPontos
	const vector<EcoPonto>& getEcopontos() const;
	void addEcoponto(const EcoPonto ecoponto);
	int createRandomEcoPontos();
	bool createEcoPonto(int idv);
	int eraseEcoPontos();
	bool removeEcoPonto(int id);
	string getSPontos() const;
	int geraLixo();
	double getLixoTotal(Cores::Cor cor);

	//Camioes
	const map<Cores::Cor, vector<Camiao*>>& getCamioes() const;
	void addCamiao(Camiao& camiao);
	int createCamioes();
	string getSCamioes() const;

	//Utilidades
	string recolhaIlimitada(int ids, int idd);
	vector<EcoPonto*> getPontosInt();
	string shortestPath(int ids, int idd);
	void dynamic();
};

} /* namespace std */

#endif /* SRC_EMPRESA_H_ */
