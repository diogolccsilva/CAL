/*
 * Edge.h
 *
 */

#ifndef SRC_EDGE_H_
#define SRC_EDGE_H_

#include <vector>
#include <string>

namespace std {

template<class T> class Graph;
template<class T> class Vertex;

template<class T>
class Edge {
	Vertex<T> * dest;
	double weight;
	string name;
	int ID;
	static int cnt;
public:

	/**
	 * Edge constructor.
	 * @param d Destination node.
	 * @param w Edge weight.
	 * @param name Edge name.
	 */
	Edge(Vertex<T> *d, double w, string name);

	/**
	 *
	 * @return The edge name.
	 */
	const string& getName() const;

	/**
	 *
	 * @return The destination node.
	 */
	const Vertex<T>* getDest();

	/**
	 *
	 * @return The edge ID.
	 */
	const int getID() const;

	friend class Graph<T> ;
	friend class Vertex<T> ;
};

} /* namespace std */

#endif /* SRC_EDGE_H_ */
