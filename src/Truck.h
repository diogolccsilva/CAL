/*
 * Camiao.h
 *
 */

#ifndef SRC_TRUCK_H_
#define SRC_TRUCK_H_

#include <iostream>
#include <string>

#include "Color.h"

using namespace std;

class Truck {
	double cUsable,cOccupied;
	int id;
	static int cnt;
	Colors::Color color;
public:

	/**
	 * Truck constructor.
	 * @param cUsable Usable capacity.
	 * @param color Color representing the type of garbage the truck is collecting.
	 */
	Truck(double cUsable,Colors::Color color);

	/**
	 * @brief Default destructor.
	 */
	virtual ~Truck();

	/**
	 *
	 * @return The occupied capacity.
	 */
	double getOcupiedCapacity() const;

	/**
	 *
	 * @param capacity Occupied capacity.
	 */
	void setOcupiedCapacity(double capacity);

	/**
	 *
	 * @return The usable capacity.
	 */
	double getUsableCapacity() const;

	/**
	 *
	 * @return Truck's ID.
	 */
	int getId() const;

	/**
	 *
	 * @return The color that represents the kind of garbage the truck collects.
	 */
	Colors::Color getColor() const;

	/**
	 * @brief Resets the truck's ID counter to 0.
	 */
	static void resetCnt();
	friend ostream& operator<<(ostream& os, const Truck& obj) {
	    os << "ID: " << obj.id << " Capacidade util: " << obj.cUsable << " Cor: " << Colors::colors[obj.color] << endl;
	    return os;
	}
};

#endif /* SRC_TRUCK_H_ */
