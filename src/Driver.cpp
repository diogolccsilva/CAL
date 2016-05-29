/*
 * Driver.cpp
 *
 */

#include "Driver.h"

namespace std {

static int Driver::sid = 0;

Driver::Driver(string name):name(name),id(sid++) {
	// TODO Auto-generated constructor stub

}

Driver::~Driver() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
