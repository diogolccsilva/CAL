/*
 * Cor.h
 *
 *  Created on: Apr 27, 2016
 */

#ifndef SRC_COR_H_
#define SRC_COR_H_

#include <map>
#include <string>

namespace std {

struct Cores {
	enum Cor {
		azul, amarelo, verde, vermelho, preto
	};
	static map<Cor, string> create_map() {
		map<Cor, string> m;
		m[azul] = "azul";
		m[amarelo] = "amarelo";
		m[verde] = "verde";
		m[vermelho] = "vermelho";
		m[preto] = "preto";
		return m;
	}
	static map<Cor, string> cores;

};

}

#endif /* SRC_COR_H_ */
