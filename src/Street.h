/*
 * Rua.h
 *
 *  Created on: 21/04/2016
 *      Author: Carolina
 */

#ifndef SRC_STREET_H_
#define SRC_STREET_H_

#include <string>

namespace std {

class Street {
	unsigned long id;
	string nome;
	bool bi;
public:

	/**
	 * @brief Default constructor.
	 */
	Street();

	/**
	 * Default destructor.
	 */
	virtual ~Street();

	/**
	 *
	 * @return True if the street is bidirectional or false otherwise.
	 */
	bool isBi() const;

	/**
	 *
	 * @param bi True for bidirectional street or false otherwise.
	 */
	void setBi(bool bi);

	/**
	 * @return Street ID.
	 */
	unsigned long getId() const;

	/**
	 *
	 * @param id Street ID.
	 */
	void setId(int id);

	/**
	 *
	 * @return Street name.
	 */
	const string getName() const;

	/**
	 *
	 * @param name Street name.
	 */
	void setName(const string& name);
};

} /* namespace std */

#endif /* SRC_STREET_H_ */
