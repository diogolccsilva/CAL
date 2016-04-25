/*
 * Info.cpp
 *
 *  Created on: 19/04/2016
 *      Author: Carolina
 */

#include "Info.h"

int Info::cnt = 0;

Info::Info():relativeID(cnt) {
	cnt++;
}

bool Info::operator == (const Info &i2) const {
	return (id==i2.id);
}

Info::~Info() {
	// TODO Auto-generated destructor stub
}

