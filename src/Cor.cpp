/*
 * Cor.cpp
 *
 *  Created on: Apr 27, 2016
 *      Author: Diogo
 */

#include "Color.h"

namespace std {
	map<Colors::Color, string> Colors::colors = Colors::create_map();
}
