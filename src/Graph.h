/*
 * Graph.h
 *
 */

#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <queue>
#include <climits>
#include "Vertex.h"
#include "graphviewer.h"

namespace std {

const int INT_INFINITY = INT_MAX;

template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	int ** W;   //weight
	int ** P;   //path
	void dfs(Vertex<T> *v, vector<T> &res) const;
	double p;
public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w, string n);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;

	void floydWarshallShortestPath();
	int edgeCost(int vOrigIndex, int vDestIndex);
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);
	void getfloydWarshallPathAux(int index1, int index2, vector<T> & res);

	void display() const;

	void setP(double a){
		p = a;
	}
};

} /* namespace std */

#endif /* SRC_GRAPH_H_ */
