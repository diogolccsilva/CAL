/*
 * EcoCentro.h
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#ifndef SRC_RECYCLINGCENTER_H_
#define SRC_RECYCLINGCENTER_H_

#include <iostream>

#include "Info.h"
#include "Vertex.h"

namespace std {

class RecyclingCenter {
	Vertex<Info>* vertex;
	int id;
	static int cnt;
public:
	/**
	 * @brief
	 * @param vertex
	 */
	RecyclingCenter(Vertex<Info>* vertex);
	/**
	 * @brief default destructor
	 */
	virtual ~RecyclingCenter();
	/**
	 * @brief
	 * @return
	 */
	int getId() const;
	/**
	 * @brief
	 * @return
	 */
	const Vertex<Info>* getVertex() const;
	/**
	 *	@brief resets RecyclingCenter's id counter to 0
	 */
	static void resetCnt();
	friend ostream& operator<<(ostream& os, const RecyclingCenter& obj) {
		os << "ID: " << obj.id << " VertexID: "
				<< obj.vertex->getInfo().getRelativeId() << endl;
		return os;
	}
};

} /* namespace std */

#endif /* SRC_RECYCLINGCENTER_H_ */
