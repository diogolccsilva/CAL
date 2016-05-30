/*
 * Driver.h
 *
 */

#ifndef SRC_DRIVER_H_
#define SRC_DRIVER_H_

#include <iostream>
#include <string>
#include "StringFuncts.h"

using namespace std;

/*
 *
 */
class Driver {
	static int cnt;
	string name;
	int id;
	bool occupied;
public:

	/**
	 * Driver constructor.
	 * @param name Driver's name.
	 */
	Driver(string name);

	/**
	 * Default destructor.
	 */
	virtual ~Driver();

	/**
	 * @brief Sets the cnt parameter to 0.
	 */
	static void resetCnt();

	/**
	 *
	 * @return The name of the driver.
	 */
	string getName() const;

	/**
	 *
	 * @return The id of the driver.
	 */
	int getId() const;

	/**
	 *
	 * @return Weather if driver is occupied or not.
	 */
	bool getOccupied() const;

	/**
	 * @brief Sets the occupied parameter of the driver with the given value.
	 * @param oc
	 */
	void setOccupied(bool oc);

	bool operator==(Driver &d);

	friend ostream& operator<<(ostream& os, const Driver& obj) {
		os << "ID: "<< obj.id << endl << "Nome: " << obj.name << endl;
		return os;
	}
};

#endif /* SRC_DRIVER_H_ */
