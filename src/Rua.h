/*
 * Rua.h
 *
 *  Created on: 21/04/2016
 *      Author: Carolina
 */

#ifndef SRC_RUA_H_
#define SRC_RUA_H_

#include <string>

namespace std {

class Rua {
	unsigned long id;
	string nome;
	bool bi;
public:
	Rua();
	virtual ~Rua();

	bool isBi() const {
		return bi;
	}

	void setBi(bool bi) {
		this->bi = bi;
	}

	unsigned long getId() const {
		return id;
	}

	void setId(int id) {
		this->id = id;
	}

	const string getNome() const {
		return nome;
	}

	void setNome(const string& nome) {
		this->nome = nome;
	}
};

} /* namespace std */

#endif /* SRC_RUA_H_ */
