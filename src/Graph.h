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

#include <iostream>
#include <queue>

#include "edgetype.h"
#include "Edge.h"
#include "graphviewer.h"
#include "Info.h"

#define _USE_MATH_DEFINES

#include <cmath>
#include <algorithm>

using namespace std ;

const int INT_INFINITY = INT_MAX;

template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	double ** W;   //weight
	int ** P;   //path
	double p;

	void dfs(Vertex<T> *v, vector<T> &res) const;
	void getfloydWarshallPathAux(int index1, int index2, vector<T> & res);
public:
	static double minLat, minLong,maxLat,maxLong;

	/**
	 * Adds a vertex to the graph.
	 * @param in Object of the class representing the vertex info.
	 * @param v1 Vertex to be added.
	 * @return True if the vertex was successfully added or false otherwise.
	 */
	bool addVertex(const T &in, Vertex<T> *v1);

	/**
	 * Adds an edge to the graph.
	 * @param sourc Source vertex.
	 * @param dest Destination vertex.
	 * @param w Weight of the edge.
	 * @param n Name of the edge.
	 * @return True of the edge was successfully added or false otherwise.
	 */
	bool addEdge(const T &sourc, const T &dest, double w, string n);

	/**
	 *
	 * @param sourc Source vertex.
	 * @param dest Destination vertex.
	 * @return Returns the edge connecting the to vertexes passed as arguments.
	 */
	Edge<T> getEdge(const T &sourc, const T &dest);

	/**
	 * Removes a vertex from the graph.
	 * @param in Info of the vertex.
	 * @return True if the vertex was successfully removed or false otherwise.
	 */
	bool removeVertex(const T &in);

	/**
	 * Removes an edge from the graph.
	 * @param sourc Source vertex.
	 * @param dest Destination source.
	 * @return True if the edge was successfully removed or false otherwise.
	 */
	bool removeEdge(const T &sourc, const T &dest);

	/**
	 *
	 * @return A vector with the information of the vertexes in the same order as they were visited using a dfs algorithm.
	 */
	vector<T> dfs() const;

	/**
	 *
	 * @param v Start vertex.
	 * @return A vector with the information of the vertexes in the same order as they were visited using a bfs algorithm.
	 */
	vector<T> bfs(Vertex<T> *v) const;

	/**
	 * ??
	 * @param v
	 * @param inf
	 * @return
	 */
	int maxNewChildren(Vertex<T> *v, T &inf) const;

	/**
	 *
	 * @return The vector of the exisiting vertexes of the graph.
	 */
	vector<Vertex<T> *> getVertexSet() const;

	/**
	 *
	 * @return The number of exisiting vertexes.
	 */
	int getNumVertex() const;

	/**
	 * Creates the Floyd-Warshall matrix for the graph.
	 */
	void floydWarshallShortestPath();

	/**
	 *
	 * @param vOrigIndex Source vertex.
	 * @param vDestIndex Destination vertex.
	 * @return The weight of the edge connecting the two vertexes passed as arguments.
	 */
	double edgeCost(int vOrigIndex, int vDestIndex);

	/**
	 *
	 * @param origin Source vertex.
	 * @param dest Destination vertex.
	 * @return The information of all the vertexes that connect the two vertexes passed as arguments.
	 */
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);

	/**
	 *
	 * @param originIndex ID of the source vertex.
	 * @param destinationIndex ID of the destination vertex.
	 * @return The information of all the vertexes that connect the two vertexes passed as arguments.
	 */
	vector<T> getfloydWarshallPath(int originIndex, int destinationIndex);

	/**
	 *
	 * @param originIndex ID of the source vertex.
	 * @param destinationIndex ID of the destination vertex.
	 * @return The weight of the shortest path between the two vertexes passed as arguments.
	 */
	double getWeight(int originIndex, int destinationIndex);

	/**
	 * Resets the color of all the edges to the default one.
	 * @param gv Graphviewer representing the graph.
	 */
	void resetEdgeColors(GraphViewer *gv);

	/**
	 * Resets the color of all the vertexes to the default one.
	 * @param gv Graphviewer representing the graph.
	 */
	void resetVertexColors(GraphViewer *gv);

	/**
	 * ??
	 * @param a
	 */
	void setP(double a){
		p = a;
	}
};

#endif /* SRC_GRAPH_H_ */
