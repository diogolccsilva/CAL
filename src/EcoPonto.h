/*
 * EcoPonto.h
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#ifndef SRC_ECOPONTO_H_
#define SRC_ECOPONTO_H_

#include <iostream>
#include <iterator>
#include <vector>

#include "Contentor.h"
#include "Info.h"
#include "Vertex.h"

namespace std {

class EcoPonto {
private:
	Vertex<Info> *vertex;
	vector<Contentor> contentores;
	int id;
	static int cnt;
public:
	EcoPonto();
	EcoPonto(vector<Contentor> contentores);
	virtual ~EcoPonto();
	const vector<Contentor>& getContentores() const;
	vector<Contentor*> check();
	void setContentores(const vector<Contentor>& contentores);
	const Vertex<Info>* getVertex() const;
	void setVertex(Vertex<Info>* vertex);
	void geraLixo();
	int getId() const;
	static void resetCnt();

	friend ostream& operator<<(ostream& os, const EcoPonto& obj) {
		os << "ID: " << obj.id << " VertexID: " << obj.vertex->getInfo().getRelativeId() << endl;
		vector<Contentor>::const_iterator it = obj.contentores.begin();
		for (;it!=obj.contentores.end();it++)
			os << (*it);
		return os;
	}
};

} /* namespace std */

#endif /* SRC_ECOPONTO_H_ */
