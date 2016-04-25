/*
 * Empresa.h
 *
 *  Created on: Apr 25, 2016
 *      Author: Diogo
 */

#ifndef SRC_EMPRESA_H_
#define SRC_EMPRESA_H_

#include <vector>

#include "Camiao.h"
#include "EcoCentro.h"
#include "EcoPonto.h"
#include "Graph.h"
#include "Info.h"

namespace std {

class Empresa {
	Graph<Info> mapa;
	vector<EcoPonto> ecopontos;
	vector<Camiao> camioes;
	vector<EcoCentro> ecocentros;
public:
	Empresa();
	virtual ~Empresa();
	const vector<Camiao>& getCamioes() const;
	void setCamioes(const vector<Camiao>& camioes);
	void addCamiao(const Camiao camiao);
	const vector<EcoCentro>& getEcocentros() const;
	void setEcocentros(const vector<EcoCentro>& ecocentros);
	void addEcocentro(const EcoCentro ecocentro);
	const vector<EcoPonto>& getEcopontos() const;
	void setEcopontos(const vector<EcoPonto>& ecopontos);
	void addEcoponto(const EcoPonto ecoponto);
	const Graph<Info>& getMapa() const;
	void setMapa(const Graph<Info>& mapa);
};

} /* namespace std */

#endif /* SRC_EMPRESA_H_ */
