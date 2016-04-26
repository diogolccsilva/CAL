/*
 * Graph.h
 *
 */

#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <climits>
#include <string>
#include <vector>

#include "Vertex.h"

namespace std {

const int INT_INFINITY = INT_MAX;

template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	double ** W;   //weight
	int ** P;   //path
	void dfs(Vertex<T> *v, vector<T> &res) const;
	double p;
public:
	static double minLat, minLong;
	bool addVertex(const T &in,Vertex<T> *v1);
	bool addEdge(const T &sourc, const T &dest, double w, string n);
	Edge<T> getEdge(const T &sourc, const T &dest);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;

	void floydWarshallShortestPath();
	double edgeCost(int vOrigIndex, int vDestIndex);
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);
	void getfloydWarshallPathAux(int index1, int index2, vector<T> & res);
	vector<T> getfloydWarshallPath(int originIndex, int destinationIndex) ;
	double getWeight(int originIndex, int destinationIndex);

	void display() const;

	void setP(double a){
		p = a;
	}
};

} /* namespace std */

#endif /* SRC_GRAPH_H_ */
