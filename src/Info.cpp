/*
 * Info.cpp
 *
 *  Created on: 19/04/2016
 *      Author: Carolina
 */

#include "Info.h"

int Info::cnt = 0;

Info::Info() :
		relativeID(cnt) {
	cnt++;
}

bool Info::operator ==(const Info &i2) const {
	return (id == i2.id);
}

Info::~Info() {
	// TODO Auto-generated destructor stub
}

double Info::getRlong() const {
	return rlong;
}

void Info::setRlat(double rlat) {
	this->rlat = rlat;
}

double Info::getRlat() const {
	return rlat;
}

void Info::setNome(const string& name) {
	this->name = name;
}

const string Info::getName() const {
	return name;
}

void Info::setId(int id) {
	this->id = id;
}

void Info::setRlong(double rlong) {
	this->rlong = rlong;
}
