/*
 * Edge.cpp
 *
 */

#include "Edge.h"
#include "Info.h"

namespace std {

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w, string name):dest(d),weight(w), name(name){

}

template class Edge<Info>;

} /* namespace std */
