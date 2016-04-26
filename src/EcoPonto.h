/*
 * EcoPonto.h
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#ifndef SRC_ECOPONTO_H_
#define SRC_ECOPONTO_H_

#include <vector>

#include "Contentor.h"
#include "Info.h"
#include "Vertex.h"

namespace std {

class EcoPonto {
private:
	Vertex<Info> *vertex;
	vector<Contentor> contentores;
public:
	EcoPonto();
	EcoPonto(vector<Contentor> contentores);
	virtual ~EcoPonto();
	vector<Contentor> getContentores() const;
	vector<Contentor*> check();
	void setContentores(const vector<Contentor>& contentores);
	const Vertex<Info>* getVertex() const;
	void setVertex(Vertex<Info>* vertex);
	void geraLixo();
};

} /* namespace std */

#endif /* SRC_ECOPONTO_H_ */
