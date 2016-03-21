/*
 * Contentor.h
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#ifndef SRC_CONTENTOR_H_
#define SRC_CONTENTOR_H_

namespace std {

class Contentor {
public:
	enum Cor {azul,amarelo,verde,vermelho,preto};
private:
	double cutil,cocupada;
	Cor cor;
public:
	Contentor();
	Contentor(double capacidade,Cor cor);
	virtual ~Contentor();
};

} /* namespace std */

#endif /* SRC_CONTENTOR_H_ */
