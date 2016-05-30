/*
 * EcoPonto.h
 *
 *  Created on: 21/03/2016
 *      Author: Diogo
 */

#ifndef SRC_RECYCLINGBIN_H_
#define SRC_RECYCLINGBIN_H_

#include <iostream>
#include <iterator>
#include <vector>

#include "Container.h"
#include "Info.h"
#include "Vertex.h"

using namespace std;

class RecyclingBin {
private:
	Vertex<Info> *vertex;
	vector<Container> containers;
	int id;
	static int cnt;
public:

	/**
	 * @brief Default constructor.
	 */
	RecyclingBin();

	/**
	 * RecyclingBin constructor.
	 * @param containers Vectors of containers.
	 */
	RecyclingBin(vector<Container> containers);

	/**
	 *	@brief Default destructor.
	 */
	virtual ~RecyclingBin();

	/**
	 *
	 * @return The container vector.
	 */
	const vector<Container>& getContainers() const;

	/**
	 *
	 * @return A vector with the containers with enough garbage to be collected.
	 */
	vector<Container*> check();

	/**
	 *
	 * @param color Color representing the type of garbage.
	 * @return A vector with the containers with enough garbage to be collected of the specified color.
	 */
	vector<Container*> check(Colors::Color color);

	/**
	 *
	 * @param containers Vector of containers.
	 */
	void setContainers(const vector<Container>& containers);

	/**
	 *
	 * @return The vertex where the Recycling Bin is located.
	 */
	const Vertex<Info>* getVertex() const;

	/**
	 *
	 * @param vertex Vertex representing the location of the Recycling Bin.
	 */
	void setVertex(Vertex<Info>* vertex);

	/**
	 * Generates a random amount of garbage.
	 */
	void generateGarbage();

	/**
	 *
	 * @return Recycling Bin ID.
	 */
	int getId() const;

	/**
	 * @brief resets Recycling Bin's ID counter to 0.
	 */
	static void resetCnt();

	/**
	 *
	 * @param color Color represeting the type of garbage.
	 * @param capacity Maximum capacity to be set.
	 */
	void setCapacity(Colors::Color color, double capacity);

	/**
	 *
	 * @param color Color representing the type of garbage.
	 * @return The garbage with the color specified.
	 */
	double getGarbage(Colors::Color color);

	friend ostream& operator<<(ostream& os, const RecyclingBin& obj) {
		os << "ID: " << obj.id << " VertexID: " << obj.vertex->getInfo().getRelativeId() << endl;
		vector<Container>::const_iterator it = obj.containers.begin();
		for (;it!=obj.containers.end();it++)
			os << (*it);
		return os;
	}
};

#endif /* SRC_RECYCLINGBIN_H_ */
