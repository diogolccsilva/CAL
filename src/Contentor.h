/*
 * Contentor.h
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#ifndef SRC_CONTENTOR_H_
#define SRC_CONTENTOR_H_

#include <time.h>
#include <stdlib.h>
namespace std {

class Contentor {
public:
	enum Cor {azul,amarelo,verde,vermelho,preto};
private:
	double cUtil,cOcupada;
	Cor cor;
public:
	Contentor(double capacidade,Cor cor);
	virtual ~Contentor();
	friend class EcoPonto;
};

} /* namespace std */

#endif /* SRC_CONTENTOR_H_ */
