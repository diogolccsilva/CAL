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
	 * @brief default constructor
	 */
	Street();
	/**
	 *
	 */
	virtual ~Street();
	/**
	 *
	 * @return
	 */
	bool isBi() const;
	/**
	 *
	 * @param bi
	 */
	void setBi(bool bi);
	/**
	 *
	 */
	unsigned long getId() const;
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
	 * @param name
	 */
	void setName(const string& nome);
};

} /* namespace std */

#endif /* SRC_STREET_H_ */
