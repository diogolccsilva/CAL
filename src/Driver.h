/*
 * Driver.h
 *
 */

#ifndef SRC_DRIVER_H_
#define SRC_DRIVER_H_

#include <string>

namespace std {

/*
 *
 */
class Driver {
	static int sid;
	int id;
	string name;
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
};

} /* namespace std */

#endif /* SRC_DRIVER_H_ */
