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

using namespace std;

class RecyclingCenter {
	Vertex<Info>* vertex;
	int id;
	static int cnt;
public:

	/**
	 * @brief Recycling Center constructor.
	 * @param vertex Vertex representing the Recycling Center location.
	 */
	RecyclingCenter(Vertex<Info>* vertex);

	/**
	 * @brief Default destructor.
	 */
	virtual ~RecyclingCenter();

	/**
	 *
	 * @return The Recycling Center ID.
	 */
	int getId() const;

	/**
	 *
	 * @return The vertex representing the Recycling Center location.
	 */
	const Vertex<Info>* getVertex() const;

	/**
	 *	@brief resets Recycling Center's ID counter to 0.
	 */
	static void resetCnt();

	friend ostream& operator<<(ostream& os, const RecyclingCenter& obj) {
		os << "ID: " << obj.id << " VertexID: "
				<< obj.vertex->getInfo().getRelativeId() << endl;
		return os;
	}
};

#endif /* SRC_RECYCLINGCENTER_H_ */
