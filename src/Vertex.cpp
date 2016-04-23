/*
 * Vertex.cpp
 *
 */

#include "Vertex.h"
#include "Info.h"

namespace std {

template<class T>
Vertex<T>::Vertex(T in):info(in),visited(false){

}

template<class T>
Vertex<T>::Vertex():visited(false){

}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w, string name) {
	Edge<T> edgeD(dest, w, name);
	adj.push_back(edgeD);
}

template <class T>
void Vertex<T>::display() const{
	cout<<info.getId()<<":"<<endl;
	for(unsigned int i=0; i<adj.size();i++){
		cout<<"Aresta "<< i << " nome: "<< adj.at(i).name << " dest: "<< adj.at(i).dest->info.getId()<<" dist: "<< adj.at(i).weight<<endl;
	}
}

template class Vertex<Info>;


} /* namespace std */
