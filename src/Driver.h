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
	bool ocupied;
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
	static void resetCnt();
	string getName() const;
	int getId() const;
	bool getOcupied() const;
	void setOcupied(bool oc);
	bool operator==(Driver &d);
	friend ostream& operator<<(ostream& os, const Driver& obj) {
		os << "ID: "<< obj.id << endl << "Nome: " << obj.name << endl;
		return os;
	}
};

#endif /* SRC_DRIVER_H_ */
