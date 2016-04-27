/*
 * Rua.cpp
 *
 *  Created on: 21/04/2016
 *      Author: Carolina
 */

#include "Street.h"

namespace std {

Street::Street() {
	// TODO Auto-generated constructor stub

}

Street::~Street() {
	// TODO Auto-generated destructor stub
}

bool Street::isBi() const {
	return bi;
}

void Street::setBi(bool bi) {
	this->bi = bi;
}

unsigned long Street::getId() const {
	return id;
}

void Street::setId(int id) {
	this->id = id;
}

const string Street::getName() const {
	return nome;
}

void Street::setName(const string& nome) {
	this->nome = nome;
}

} /* namespace std */
