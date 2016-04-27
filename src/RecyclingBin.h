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

namespace std {

class RecyclingBin {
private:
	Vertex<Info> *vertex;
	vector<Container> containers;
	int id;
	static int cnt;
public:
	/**
	 * @brief default constructor
	 */
	RecyclingBin();
	/**
	 *
	 * @param contentores
	 */
	RecyclingBin(vector<Container> containers);
	/**
	 *	@brief default destructor
	 */
	virtual ~RecyclingBin();
	/**
	 *
	 * @return
	 */
	const vector<Container>& getContainers() const;
	/**
	 *
	 * @return
	 */
	vector<Container*> check();
	/**
	 *
	 * @param color
	 * @return
	 */
	vector<Container*> check(Colors::Color color);
	/**
	 *
	 * @param containers
	 */
	void setContainers(const vector<Container>& contentores);
	/**
	 *
	 * @return
	 */
	const Vertex<Info>* getVertex() const;
	/**
	 *
	 * @param vertex
	 */
	void setVertex(Vertex<Info>* vertex);
	/**
	 *
	 */
	void generateGarbage();
	/**
	 *
	 * @return
	 */
	int getId() const;
	/**
	 * @brief resets EcoPonto's id counter to 0
	 */
	static void resetCnt();
	/**
	 *
	 * @param color
	 * @param capacity
	 */
	void setCapacity(Colors::Color color, double capacity);
	/**
	 *
	 * @param color
	 * @return
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

} /* namespace std */

#endif /* SRC_RECYCLINGBIN_H_ */
