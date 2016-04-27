/*
 * Camiao.h
 *
 */

#ifndef SRC_CAMIAO_H_
#define SRC_CAMIAO_H_

#include <iostream>
#include <string>

#include "Cor.h"

namespace std {

class Camiao {
	double cUtil,cOcupada;
	int id;
	static int cnt;
	Cores::Cor cor;
public:
	Camiao(double cUtil,Cores::Cor cor);
	virtual ~Camiao();
	double getCOcupada() const;
	double getCUtil() const;
	int getId() const;
	Cores::Cor getCor() const;
	friend ostream& operator<<(ostream& os, const Camiao& obj) {
	    os << "ID: " << obj.id << " Capacidade util: " << obj.cUtil << " Cor: " << Cores::cores[obj.cor] << endl;
	    return os;
	}
};

} /* namespace std */

#endif /* SRC_CAMIAO_H_ */
