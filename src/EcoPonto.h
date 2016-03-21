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

namespace std {

class EcoPonto {
private:
	double longitude, latitude;
	vector<Contentor> contentores;
public:
	EcoPonto();
	EcoPonto(double longitude,double latitude,vector<Contentor> contentores);
	virtual ~EcoPonto();
};

} /* namespace std */

#endif /* SRC_ECOPONTO_H_ */
