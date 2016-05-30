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

using namespace std;

class Container {
private:
	double cUsable, cOccupied;
	Colors::Color color;
public:

	/**
	 * Container constructor.
	 * @param capacity Maximum capacity of the container.
	 * @param color Color of the container, i.e, the type of garbage it contains.
	 */
	Container(double capacity, Colors::Color color);

	/**
	 * @brief default destructor
	 */
	virtual ~Container();

	/**
	 *
	 * @return The occupied capacity.
	 */
	double getOcupiedCapacity() const;

	/**
	 *
	 * @param cocupied Occupied capacity.
	 */
	void setOcupiedCapacity(double cocupied);

	/**
	 *
	 * @return Color of the container.
	 */
	Colors::Color getColor() const;

	/**
	 *
	 * @param color Color associated with the specified garbage.
	 */
	void setColor(Colors::Color color);

	/**
	 *
	 * @return The usable capacity.
	 */
	double getUsableCapacity() const;

	/**
	 *
	 * @param cusable Usable capacity.
	 */
	void setUsableCapacity(double cusable);
	friend ostream& operator<<(ostream& os, const Container& obj) {
		os << "Cor: " << Colors::colors[obj.color] << " Capacidade Util: " << obj.cUsable << " Capacidade Ocupada: " << obj.cOccupied << endl;
		return os;
	}

	friend class RecyclingBin;
};

#endif /* SRC_CONTAINER_H_ */
