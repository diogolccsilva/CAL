#ifndef SRC_INFO_H_
#define SRC_INFO_H_

#include <iostream>
#include <iomanip>

using namespace std;

class Info {
private:
	unsigned long id;
	double rlat, rlong, glat, glong;
	string name;
	int relativeID;
	static int cnt;

public:

	/**
	 * @brief Default constructor.
	 */
	Info();

	/**
	 * @brief Default destructor.
	 */
	virtual ~Info();

	bool operator == (const Info &p2) const;

	/**
	 *
	 * @return Info relative ID.
	 */
	int getRelativeId() const{
		return relativeID;
	}

	/**
	 *
	 * @return Info Latitude in degrees.
	 */
	double getGlat() const {
		return glat;
	}

	/**
	 *
	 * @param glat Latitude in degrees.
	 */
	void setGlat(double glat) {
		this->glat = glat;
	}

	/**
	 *
	 * @return Info Longitude in degrees.
	 */
	double getGlong() const {
		return glong;
	}

	/**
	 *
	 * @param glong Longitude in degrees.
	 */
	void setGlong(double glong) {
		this->glong = glong;
	}

	/**
	 *
	 * @return Info ID.
	 */
	unsigned long getId() const {
		return id;
	}

	/**
	 *
	 * @param id Info ID.
	 */
	void setId(int id);

	/**
	 *
	 * @return Info name.
	 */
	const string getName() const;

	/**
	 *
	 * @param name Info name.
	 */
	void setNome(const string& name);

	/**
	 *
	 * @return Info latitude in radians.
	 */
	double getRlat() const;

	/**
	 *
	 * @param rlat Latitude in radians.
	 */
	void setRlat(double rlat);

	/**
	 *
	 * @return Info longitude in radians.
	 */
	double getRlong() const;

	/**
	 *
	 * @param rlong Longitude in radians.
	 */
	void setRlong(double rlong);
};

#endif /* SRC_INFO_H_ */
