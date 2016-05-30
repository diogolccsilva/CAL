/*
 * Driver.cpp
 *
 */

#include "Driver.h"

using namespace std;

int Driver::cnt = 0;

Driver::Driver(string name) :
		name(name), id(++cnt), occupied(false) {
	// TODO Auto-generated constructor stub

}

Driver::~Driver() {
	// TODO Auto-generated destructor stub
}

void Driver::resetCnt() {
	cnt = 0;
}

string Driver::getName() const {
	return name;
}

int Driver::getId() const {
	return id;
}

bool Driver::getOccupied() const {
	return occupied;
}

void Driver::setOccupied(bool oc) {
	occupied = oc;
}

bool Driver::operator==(Driver& d) {
	if (id == d.id)
		return true;
	return false;
}
