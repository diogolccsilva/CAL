/*
 * Vertex.h
 *
 */

#ifndef SRC_VERTEX_H_
#define SRC_VERTEX_H_

#include "Edge.h"

namespace std {

template<class T>
class Vertex {
	T info;
	vector<Edge<T> > adj;
	bool visited;
	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	friend class Graph<T>;
};

} /* namespace std */

#endif /* SRC_VERTEX_H_ */
