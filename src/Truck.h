/*
 * Camiao.h
 *
 */

#ifndef SRC_TRUCK_H_
#define SRC_TRUCK_H_

#include <iostream>
#include <string>

#include "Color.h"

namespace std {

class Truck {
	double cUsable,cOcupied;
	int id;
	static int cnt;
	Colors::Color color;
public:
	/**
	 * @brief
	 * @param cUtil
	 * @param cor
	 */
	Truck(double cUtil,Colors::Color color);
	/**
	 * @brief default destructor
	 */
	virtual ~Truck();
	/**
	 * @brief
	 * @return
	 */
	double getOcupiedCapacity() const;
	/**
	 *
	 * @param capacity
	 */
	void setOcupiedCapacity(double capacity);
	/**
	 * @brief
	 * @return truck's usable capacity
	 */
	double getUsableCapacity() const;
	/**
	 * @brief
	 * @return id
	 */
	int getId() const;
	/**
	 * @brief
	 * @return the color that represents the kind of garbage that the truck carries
	 */
	Colors::Color getColor() const;
	/**
	 * @brief resets Camiao's id counter to 0
	 */
	static void resetCnt();
	friend ostream& operator<<(ostream& os, const Truck& obj) {
	    os << "ID: " << obj.id << " Capacidade util: " << obj.cUsable << " Cor: " << Colors::colors[obj.color] << endl;
	    return os;
	}
};

} /* namespace std */

#endif /* SRC_TRUCK_H_ */
