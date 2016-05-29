/*
 * Contentor.h
 *
 */

#ifndef SRC_CONTAINER_H_
#define SRC_CONTAINER_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Color.h"

namespace std {

class Container {
private:
	double cUsable, cOcupied;
	Colors::Color color;
public:
	/**
	 *
	 * @param capacity
	 * @param color
	 */
	Container(double capacity, Colors::Color color);
	/**
	 * @brief default destructor
	 */
	virtual ~Container();
	/**
	 *
	 * @return
	 */
	double getOcupiedCapacity() const;
	/**
	 *
	 * @param cocupied
	 */
	void setOcupiedCapacity(double cocupied);
	/**
	 *
	 * @return color
	 */
	Colors::Color getColor() const;
	/**
	 *
	 * @param color
	 */
	void setColor(Colors::Color color);
	/**
	 *
	 * @return
	 */
	double getUsableCapacity() const;
	/**
	 *
	 * @param cusable
	 */
	void setUsableCapacity(double cusable);
	friend ostream& operator<<(ostream& os, const Container& obj) {
		os << "Cor: " << Colors::colors[obj.color] << " Capacidade Util: " << obj.cUsable << " Capacidade Ocupada: " << obj.cOcupied << endl;
		return os;
	}

	friend class RecyclingBin;
};

} /* namespace std */

#endif /* SRC_CONTAINER_H_ */
