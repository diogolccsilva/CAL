/*
 * Color.h
 *
 */

#ifndef SRC_COLOR_H_
#define SRC_COLOR_H_

#include <map>
#include <string>

namespace std {

struct Colors {
	/*! Color Enum */
	enum Color {
		/*! Represents the color blue */ blue,
		/*! Represents the color yellow */ yellow,
		/*! Represents the color green */ green,
		/*! Represents the color red */ red,
		/*! Represents the color black */ black
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
