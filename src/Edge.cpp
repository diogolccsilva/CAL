/*
 * Edge.cpp
 *
 */

#include "Edge.h"
#include "Info.h"

namespace std {

template<class T>
int Edge<T>::cnt = 0;

template<class T>
const Vertex<T>* Edge<T>::getDest() {
	return dest;
}

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w, string name) :
		dest(d), weight(w), name(name), ID(cnt) {
	cnt++;
}

template<class T>
const string& Edge<T>::getName() const {
	return name;
}

template<class T>
const int Edge<T>::getID() const {
	return ID;
}

template class Edge<Info> ;

} /* namespace std */
