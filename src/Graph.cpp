/*
 * Graph.cpp
 *
 */

#include "Graph.h"

#include <iostream>
#include <queue>

#include "edgetype.h"
#include "Edge.h"
#include "graphviewer.h"
#include "Info.h"

#define _USE_MATH_DEFINES

#include <cmath>
#include <algorithm>

namespace std {

template<class T>
double Graph<T>::minLat = M_PI/2;
template<class T>
double Graph<T>::minLong = M_PI;

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template<class T>
bool Graph<T>::addVertex(const T &in,Vertex<T> *v1) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++)
		if ((*it)->info == in)
			return false;
	v1 = new Vertex<T>(in);

	vertexSet.push_back(v1);
	return true;
}

template<class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v = *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1 = vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e = vertexSet.end();
			for (; it1 != it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}
			delete v;
			return true;
		}
	}
	return false;
}

template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, string n) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}
		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}
		it++;
	}
	if (found != 2)
		return false;
	vS->addEdge(vD, w, n);
	return true;
}

template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}
		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}
		it++;
	}
	if (found != 2)
		return false;
	return vS->removeEdgeTo(vD);
}

template<class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	vector<T> res;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfs(*it, res);
	return res;
}

template<class T>
void Graph<T>::dfs(Vertex<T> *v, vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it = (v->adj).begin();
	typename vector<Edge<T> >::iterator ite = (v->adj).end();
	for (; it != ite; it++)
		if (it->dest->visited == false)
			dfs(it->dest, res);
}

template<class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it = v1->adj.begin();
		typename vector<Edge<T> >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
			}
		}
	}
	return res;
}

template<class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren = 0;
	inf = v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l = level.front();
		level.pop();
		l++;
		int nChildren = 0;
		typename vector<Edge<T> >::iterator it = v1->adj.begin();
		typename vector<Edge<T> >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren > maxChildren) {
			maxChildren = nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}

template<class T>
double Graph<T>::edgeCost(int vOrigIndex, int vDestIndex) {
	if (vertexSet[vOrigIndex] == vertexSet[vDestIndex])
		return 0;

	for (unsigned int i = 0; i < vertexSet[vOrigIndex]->adj.size(); i++) {
		if (vertexSet[vOrigIndex]->adj[i].dest == vertexSet[vDestIndex])
			return vertexSet[vOrigIndex]->adj[i].weight;
	}

	return INT_INFINITY;
}

template<class T>
double Graph<T>::getWeight(int originIndex, int destinationIndex) {
	return W[originIndex][destinationIndex];
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(int originIndex, int destinationIndex) {

	vector<T> res;

	//se nao foi encontrada solucao possivel, retorna lista vazia
	if (W[originIndex][destinationIndex] == INT_INFINITY)
		return res;

	res.push_back(vertexSet[originIndex]->info);

	//se houver pontos intermedios...
	if (P[originIndex][destinationIndex] != -1) {
		int intermedIndex = P[originIndex][destinationIndex];

		getfloydWarshallPathAux(originIndex, intermedIndex, res);

		res.push_back(vertexSet[intermedIndex]->info);

		getfloydWarshallPathAux(intermedIndex, destinationIndex, res);
	}

	res.push_back(vertexSet[destinationIndex]->info);

	return res;
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &origin, const T &dest) {

	int originIndex = -1, destinationIndex = -1;

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->info == origin)
			originIndex = i;
		if (vertexSet[i]->info == dest)
			destinationIndex = i;

		if (originIndex != -1 && destinationIndex != -1)
			break;
	}

	vector<T> res;

	//se nao foi encontrada solucao possivel, retorna lista vazia
	if (W[originIndex][destinationIndex] == INT_INFINITY)
		return res;

	res.push_back(vertexSet[originIndex]->info);

	//se houver pontos intermedios...
	if (P[originIndex][destinationIndex] != -1) {
		int intermedIndex = P[originIndex][destinationIndex];

		getfloydWarshallPathAux(originIndex, intermedIndex, res);

		res.push_back(vertexSet[intermedIndex]->info);

		getfloydWarshallPathAux(intermedIndex, destinationIndex, res);
	}

	res.push_back(vertexSet[destinationIndex]->info);

	return res;
}

template<class T>
void Graph<T>::getfloydWarshallPathAux(int index1, int index2,
		vector<T> & res) {
	if (P[index1][index2] != -1) {
		getfloydWarshallPathAux(index1, P[index1][index2], res);

		res.push_back(vertexSet[P[index1][index2]]->info);

		getfloydWarshallPathAux(P[index1][index2], index2, res);
	}
}

template<class T>
void Graph<T>::floydWarshallShortestPath() {

	W = new double *[vertexSet.size()];
	P = new int *[vertexSet.size()];
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		W[i] = new double[vertexSet.size()];
		P[i] = new int[vertexSet.size()];
		for (unsigned int j = 0; j < vertexSet.size(); j++) {
			W[i][j] = edgeCost(i, j);
			P[i][j] = -1;
		}
	}

	for (unsigned int k = 0; k < vertexSet.size(); k++)
		for (unsigned int i = 0; i < vertexSet.size(); i++)
			for (unsigned int j = 0; j < vertexSet.size(); j++) {
				//se somarmos qualquer coisa ao valor INT_INFINITY, ocorre overflow, o que resulta num valor negativo, logo nem convém considerar essa soma
				if (W[i][k] == INT_INFINITY || W[k][j] == INT_INFINITY)
					continue;

				double val = min(W[i][j], W[i][k] + W[k][j]);
				if (val != W[i][j]) {
					W[i][j] = val;
					P[i][j] = k;
				}
			}

}

template<class T>
Edge<T> Graph<T>::getEdge(const T& sourc, const T& dest) {
	typename vector<Vertex<T> *>::const_iterator it = vertexSet.begin();
	for (;it!=vertexSet.end();it++){
		if ((*it)->info == sourc){
			typename vector<Edge<T> >::const_iterator ite = (*it)->adj.begin();
			for (;ite!=(*it)->adj.end();ite++){
				if (ite->dest->info == dest)
					return (*ite);
			}
		}
	}
	return Edge<T>(new Vertex<T>(dest),INT_INFINITY,"\0");
}

template<class T>
void Graph<T>::display() const {
//	for (unsigned int i = 0; i < vertexSet.size(); i++) {
//		vertexSet.at(i)->display();
//	}

	GraphViewer *gv = new GraphViewer(100000, 100000, false);

	gv->createWindow(1366,768);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	string line;

	unsigned long idNo = 0;
	int r  = 10000000;
	//Read nodes
	auto itv = vertexSet.begin(); //typename vector<Vertex<T> *>::const_iterator
	for (; itv != vertexSet.end(); itv++) {
		idNo = (*itv)->info.getRelativeId();
		int y = (int)(((sin((*itv)->info.getRlong()+M_PI)-sin(minLong+M_PI))*r))%r;
		int x = (int)(((sin((*itv)->info.getRlat()+M_PI)-sin(minLat+M_PI))*r))%r;
		gv->addNode(idNo,x,y);
	}

	cout << minLong*M_PI/180.0 << "  " <<minLat*M_PI/180.0 << endl;

	unsigned long idNoOrigem = 0;
	unsigned long idNoDestino = 0;

	//Read Edges
	itv = vertexSet.begin();
	int cnt = 1;
	for (; itv != vertexSet.end(); itv++) {
		auto adj = (*itv)->adj;
		auto ite = adj.begin();
		for (; ite != adj.end(); ite++) {
			cnt++;
			idNoOrigem = (*itv)->getInfo().getRelativeId();
			idNoDestino = ite->dest->getInfo().getRelativeId();
			//cout << "S: " << idNoOrigem << " D: " << idNoDestino << " E: " << cnt << endl;
			if (!gv->addEdge(cnt, idNoOrigem, idNoDestino, EdgeType::DIRECTED))
				cout << "fodeu " << cnt << endl;
		}
	}

	gv->rearrange();
}

template class Graph<Info> ;

} /* namespace std */
