#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <cstdio>
#include <conio.h>
#include "Info.h"
#include "Vertex.h"
#include "Rua.h"
#include "Edge.h"
#include "Graph.h"
#include <sstream>

using namespace std;

/*void thisIsATest() {
 ASSERTM("start writing tests", false);
 }*/

/*void runAllTests(int argc, char const *argv[]){
 cute::suite s;
 //TODO add your test here
 s.push_back(CUTE(thisIsATest));
 cute::xml_file_opener xmlfile(argc,argv);
 cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
 cute::makeRunner(lis,argc,argv)(s, "AllTests");
 }*/

double nodeDistance(Vertex<Info> *v1, Vertex<Info> *v2) {
	double lat1r, lon1r, lat2r, lon2r, u, v, earth_rad = 6371000;
	lat1r = v1->getInfo().getRlat();
	lon1r = v1->getInfo().getRlong();
	lat2r = v2->getInfo().getRlat();
	lon2r = v2->getInfo().getRlong();
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	return 2.0 * earth_rad * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

Graph<Info> readGraph() {
	string temp;
	vector<Rua> ruas;
	Graph<Info> grafo = Graph<Info>();
	ifstream map1, map2, map3;
	map1.open("map1.txt");
	map2.open("map2.txt");
	map3.open("map3.txt");

	if (map1.is_open()) {
		while (!map1.eof()) {
			Info tempInfo = Info();
			getline(map1, temp, ';');
			if (temp != "") {
				tempInfo.setId(atol(temp.c_str()));
				getline(map1, temp, ';');
				tempInfo.setGlat(atof(temp.c_str()));
				getline(map1, temp, ';');
				tempInfo.setGlong(atof(temp.c_str()));
				getline(map1, temp, ';');
				tempInfo.setRlat(atof(temp.c_str()));
				getline(map1, temp);
				tempInfo.setRlong(atof(temp.c_str()));

				grafo.addVertex(tempInfo);

			}
		}
	}

	if (map2.is_open()) {
		while (!map2.eof()) {
			Rua tempRua = Rua();
			getline(map2, temp, ';');
			if (temp != "") {
				tempRua.setId(atol(temp.c_str()));
				getline(map2, temp, ';');
				tempRua.setNome(temp);
				getline(map2, temp);
				if (temp == "true")
					tempRua.setBi(true);
				else
					tempRua.setBi(false);
				ruas.push_back(tempRua);
			}
		}
	}

	if (map3.is_open()) {
		while (!map3.eof()) {

			unsigned long idRua, idNo, idDest;
			getline(map3, temp, ';');
			if (temp != "") {
				idRua = atol(temp.c_str());
				getline(map3, temp, ';');
				idNo = atol(temp.c_str());
				getline(map3, temp);
				idDest = atol(temp.c_str());
				vector<Vertex<Info> *> vertexSet = grafo.getVertexSet();

				for (unsigned int i = 0; i < ruas.size(); i++) {
					if (ruas.at(i).getId() == idRua) {
						Vertex<Info> *tempNo, *tempDest;
						for (unsigned int j = 0; j < vertexSet.size(); j++) {
							if (vertexSet.at(j)->getInfo().getId() == idNo)
								tempNo = vertexSet.at(j);
							if (vertexSet.at(j)->getInfo().getId() == idDest)
								tempDest = vertexSet.at(j);

						}
						//cout << nodeDistance(tempNo, tempDest) << endl;
						if (ruas.at(i).isBi())
							grafo.addEdge(tempDest->getInfo(),
									tempNo->getInfo(),
									nodeDistance(tempNo, tempDest),
									ruas.at(i).getNome());
						grafo.addEdge(tempNo->getInfo(), tempDest->getInfo(),
								nodeDistance(tempNo, tempDest),
								ruas.at(i).getNome());
					}

				}
			}
		}
	}

	map1.close();
	map2.close();
	map3.close();

	grafo.display();
	//cout << "Tamanho: " << grafo.getVertexSet().size() << endl;
	grafo.floydWarshallShortestPath();

	return grafo;
}

void shortestPath(std::Graph<Info>& grafo) {

	auto v = grafo.getfloydWarshallPath(grafo.getVertexSet().at(185)->getInfo(),
			grafo.getVertexSet().at(127)->getInfo());
	if (v.size() == 0){
		cout << "Pontos sem ligacao!" << endl;
		return;
	}
	auto it = v.begin();
	for (;it!=v.end();it++){
		cout << it->getId() << endl;
	}

}

int menu() {
	Graph<Info> grafo = readGraph();
	while (1) {
		cout << "1. Caminho mais curto;" << endl;
		cout << "9. Sair;" << endl;
		switch (getch()) {
		case '1':
			shortestPath(grafo);
			break;
		case '2':
			break;
		case '3':
			break;
		case '4':
			break;
		case '9':
			return 0;
		default:
			break;
		}
	}
	return 1;
}

int main() {
	//   runAllTests(argc,argv);
	menu();

	return 0;
}
