/*
 * Driver.h
 *
 */

#ifndef SRC_DRIVER_H_
#define SRC_DRIVER_H_

#include <iostream>
#include <string>

namespace std {

/*
 *
 */
class Driver {
	static int cnt;
	string name;
	int id;
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
	friend ostream& operator<<(ostream& os, const Driver& obj) {
		os << "ID: "<< obj.id << endl << "Nome: " << obj.name << endl;
		return os;
	}
};

} /* namespace std */

#endif /* SRC_DRIVER_H_ */
