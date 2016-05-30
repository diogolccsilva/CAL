/*
 * Vertex.h
 *
 */

#ifndef SRC_VERTEX_H_
#define SRC_VERTEX_H_

#include "Edge.h"

using namespace std;

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

	/**
	 * Vertex constructor.
	 * @param in Class to represent the vertex info.
	 */
	Vertex(T in);

	/**
	 * Default constructor.
	 */
	Vertex();

	/**
	 * Displays on the screen all the information of the vertex.
	 */
	void display() const;
//	bool applyEco();

	/**
	 *
	 * @return The vector with the adjacent edges.
	 */
	const vector<Edge<T> >& getAdj() const {
		return adj;
	}

	/**
	 *
	 * @param adj Vector of edges.
	 */
	void setAdj(const vector<Edge<T> >& adj) {
		this->adj = adj;
	}

	/**
	 *
	 * @return The object of the class representing the vertex info.
	 */
	T getInfo() const {
		return info;
	}

	/**
	 *
	 * @param info Object of the class that represents the vertex info.
	 */
	void setInfo(T info) {
		this->info = info;
	}

	/**
	 *
	 * @return True if the vertex was visited before or false otherwise.
	 */
	bool isVisited() const {
		return visited;
	}

	/**
	 *
	 * @param visited True if the vertex was visited or false otherwise.
	 */
	void setVisited(bool visited) {
		this->visited = visited;
	}

	friend class Graph<T>;

};

#endif /* SRC_VERTEX_H_ */
