/*
 * EcoCentro.h
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#ifndef SRC_ECOCENTRO_H_
#define SRC_ECOCENTRO_H_

#include <string>

namespace std {

class EcoCentro {
	string latitude,longitude;
public:
	EcoCentro(string latitude,string longitude);
	EcoCentro();
	virtual ~EcoCentro();
};

} /* namespace std */

#endif /* SRC_ECOCENTRO_H_ */
