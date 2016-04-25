#ifndef SRC_INFO_H_
#define SRC_INFO_H_

#include <iostream>
#include <iomanip>

using namespace std;


class Info {
private:
	unsigned long id;
	double rlat, rlong, glat, glong;
	string nome;
	int relativeID;
	static int cnt;

public:

	Info();
	virtual ~Info();
	bool operator == (const Info &p2) const;
	int getRelativeId() const{
		return relativeID;
	}

	double getGlat() const {
		return glat;
	}

	void setGlat(double glat) {
		this->glat = glat;
	}

	double getGlong() const {
		return glong;
	}

	void setGlong(double glong) {
		this->glong = glong;
	}

	unsigned long getId() const {
		return id;
	}

	void setId(int id) {
		this->id = id;
	}

	const string getNome() const {
		return nome;
	}

	void setNome(const string& nome) {
		this->nome = nome;
	}

	double getRlat() const {
		return rlat;
	}

	void setRlat(double rlat) {
		this->rlat = rlat;
	}

	double getRlong() const {
		return rlong;
	}

	void setRlong(double rlong) {
		this->rlong = rlong;
	}
};

#endif /* SRC_INFO_H_ */
