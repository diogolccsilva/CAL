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
	vector<Contentor> contentores;
public:
	EcoPonto();
	EcoPonto(vector<Contentor> contentores);
	virtual ~EcoPonto();
	vector<Contentor> getContentores() const;
	vector<Contentor*> check();

};

} /* namespace std */

#endif /* SRC_ECOPONTO_H_ */
