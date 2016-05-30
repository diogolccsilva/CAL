/*
 * Driver.cpp
 *
 */

#include "Driver.h"

namespace std {

int Driver::cnt = 0;

Driver::Driver(string name) :
		name(name), id(++cnt) {
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

} /* namespace std */
