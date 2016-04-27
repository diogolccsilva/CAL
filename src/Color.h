/*
 * Cor.h
 *
 *  Created on: Apr 27, 2016
 */

#ifndef SRC_COLOR_H_
#define SRC_COLOR_H_

#include <map>
#include <string>

namespace std {

struct Colors {
	enum Color {
		blue, yellow, green, red, black
	};
	static map<Color, string> create_map() {
		map<Color, string> m;
		m[blue] = "blue";
		m[yellow] = "yellow";
		m[green] = "green";
		m[red] = "red";
		m[black] = "black";
		return m;
	}
	static map<Color, string> colors;

};

}

#endif /* SRC_COLOR_H_ */
