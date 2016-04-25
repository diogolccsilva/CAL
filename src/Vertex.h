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
	//EcoPonto ecoponto;
	vector<Edge<T> > adj;
	bool visited;
	void addEdge(Vertex<T> *dest, double w, string name);
	bool removeEdgeTo(Vertex<T> *d);
	//vector<Contentor*> check();
public:
	Vertex(T in);
	Vertex();
	void display() const;
//	bool applyEco();

	const vector<Edge<T> >& getAdj() const {
		return adj;
	}

	void setAdj(const vector<Edge<T> >& adj) {
		this->adj = adj;
	}

	T getInfo() const {
		return info;
	}

	void setInfo(T info) {
		this->info = info;
	}

	bool isVisited() const {
		return visited;
	}

	void setVisited(bool visited) {
		this->visited = visited;
	}

	friend class Graph<T>;

};

} /* namespace std */

#endif /* SRC_VERTEX_H_ */
