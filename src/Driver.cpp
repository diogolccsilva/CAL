/*
 * Driver.cpp
 *
 */

#include "Driver.h"

using namespace std;

int Driver::cnt = 0;

Driver::Driver(string name) :
		name(name), id(++cnt), ocupied(false) {
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

bool Driver::getOcupied() const {
	return ocupied;
}

void Driver::setOcupied(bool oc) {
	ocupied = oc;
}

bool Driver::operator==(Driver& d) {
	if (id == d.id)
		return true;
	return false;
}
