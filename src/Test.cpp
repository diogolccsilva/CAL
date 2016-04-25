#include <conio.h>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

#include "Graph.h"
#include "Info.h"
#include "Vertex.h"
#include "Empresa.h"

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

void shortestPath(Graph<Info> grafo) {
	int ids,idd;
	cin >> ids >> idd;
	auto v = grafo.getfloydWarshallPath(grafo.getVertexSet().at(ids)->getInfo(),
			grafo.getVertexSet().at(idd)->getInfo());
	if (v.size() == 0) {
		cout << "Pontos sem ligacao!" << endl;
		return;
	}
	auto it = v.begin();
	for (; it != v.end(); it++) {
		cout << it->getRelativeId() << endl;
	}

}

int menu() {
	Empresa emp = Empresa();
	while (1) {
		cout << "1. Caminho mais curto;" << endl;
		cout << "9. Sair;" << endl;
		switch (getch()) {
		case '1':
			shortestPath(emp.getMapa());
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
