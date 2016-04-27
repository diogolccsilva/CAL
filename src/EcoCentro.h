/*
 * EcoCentro.h
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#ifndef SRC_ECOCENTRO_H_
#define SRC_ECOCENTRO_H_

#include <iostream>

#include "Info.h"
#include "Vertex.h"

namespace std {

class EcoCentro {
	Vertex<Info>* vertex;
	int id;
	static int cnt;
public:
	EcoCentro(Vertex<Info>* vertex);
	virtual ~EcoCentro();
	friend ostream& operator<<(ostream& os,const EcoCentro& obj){
		os << "ID: " << obj.id << " VertexID: " << obj.vertex->getInfo().getRelativeId() << endl;
		return os;
	}
};

} /* namespace std */

#endif /* SRC_ECOCENTRO_H_ */
