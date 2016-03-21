/*
 * EcoPonto.h
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#ifndef SRC_ECOPONTO_H_
#define SRC_ECOPONTO_H_

#include <vector>
#include <string>
#include "Contentor.h"

namespace std {

class EcoPonto {
private:
	string longitude, latitude;
	vector<Contentor> contentores;
public:
	EcoPonto();
	EcoPonto(string longitude,string latitude,vector<Contentor> contentores);
	virtual ~EcoPonto();
};

} /* namespace std */

#endif /* SRC_ECOPONTO_H_ */
