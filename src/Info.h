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
	 * @brief default constructor
	 */
	Info();
	/**
	 * @brief default destructor
	 */
	virtual ~Info();
	bool operator == (const Info &p2) const;
	/**
	 *
	 * @return
	 */
	int getRelativeId() const{
		return relativeID;
	}
	/**
	 *
	 * @return
	 */
	double getGlat() const {
		return glat;
	}
	/**
	 *
	 * @param glat
	 */
	void setGlat(double glat) {
		this->glat = glat;
	}

	double getGlong() const {
		return glong;
	}
	/**
	 *
	 * @param glong
	 */
	void setGlong(double glong) {
		this->glong = glong;
	}
	/**
	 *
	 */
	unsigned long getId() const {
		return id;
	}
	/**
	 *
	 * @param id
	 */
	void setId(int id);
	/**
	 *
	 * @return
	 */
	const string getName() const;
	/**
	 *
	 * @param nome
	 */
	void setNome(const string& name);
	/**
	 *
	 * @return
	 */
	double getRlat() const;
	/**
	 *
	 * @param rlat
	 */
	void setRlat(double rlat);
	/**
	 *
	 * @return
	 */
	double getRlong() const;
	/**
	 *
	 * @param rlong
	 */
	void setRlong(double rlong);
};

#endif /* SRC_INFO_H_ */
