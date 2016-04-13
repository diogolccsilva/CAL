/*
 * Graph.h
 *
 */

#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <queue>
#include "Vertex.h"

namespace std {

template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<T> &res) const;
public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;
};

} /* namespace std */

#endif /* SRC_GRAPH_H_ */
