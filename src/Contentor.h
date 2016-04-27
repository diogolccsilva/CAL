/*
 * Contentor.h
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#ifndef SRC_CONTENTOR_H_
#define SRC_CONTENTOR_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Cor.h"

namespace std {

class Contentor {
private:
	double cUtil, cOcupada;
	Cores::Cor cor;
public:
	Contentor(double capacidade, Cores::Cor cor);
	virtual ~Contentor();
	double getOcupada() const;
	void setOcupada(double ocupada);
	Cores::Cor getCor() const;
	void setCor(Cores::Cor cor);
	double getUtil() const;
	void setUtil(double util);

	friend ostream& operator<<(ostream& os, const Contentor& obj) {
		os << "Cor: " << Cores::cores[obj.cor] << " Capacidade Util: " << obj.cUtil << " Capacidade Ocupada: " << obj.cOcupada << endl;
		return os;
	}

	friend class EcoPonto;
};

} /* namespace std */

#endif /* SRC_CONTENTOR_H_ */
