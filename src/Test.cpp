#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <climits>
#include "Info.h"
#include "Vertex.h"
#include "Rua.h"
#include "Edge.h"
#include "Graph.h"

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

int main2(){
	string temp;
	vector<Rua> ruas;
	Graph<Info> grafo = Graph<Info>();
	ifstream map1, map2, map3;
	map1.open("map1.txt");
	map2.open("map2.txt");
	map3.open("map3.txt");
	cout << "Hello 2." << endl;

	if (map1.is_open())
	{
		while (!map1.eof()){
			Info tempInfo = Info();
			getline(map1, temp, ';');
			if(temp!=""){
				tempInfo.setId(atol(temp.c_str()));
				getline(map1, temp, ';');
				tempInfo.setGlat(atol(temp.c_str()));
				getline(map1, temp, ';');
				tempInfo.setGlong(atol(temp.c_str()));
				getline(map1, temp, ';');
				tempInfo.setRlat(atol(temp.c_str()));
				getline(map1, temp);
				tempInfo.setRlong(atol(temp.c_str()));


				grafo.addVertex(tempInfo);
			}
		}
	}

	if (map2.is_open())
	{
		while (!map2.eof()){
			Rua tempRua = Rua();
			getline(map2, temp, ';');
			if(temp!=""){
				tempRua.setId(atol(temp.c_str()));
				getline(map2, temp, ';');
				tempRua.setNome(temp);
				getline(map2, temp);
				if(temp=="true")
					tempRua.setBi(true);
				else
					tempRua.setBi(false);
				ruas.push_back(tempRua);
			}
		}
	}

	if (map3.is_open())
	{
		while (!map3.eof()){

			unsigned long idRua, idNo, idDest;
			getline(map3, temp, ';');
			if(temp!=""){
				idRua=atol(temp.c_str());
				getline(map3, temp, ';');
				idNo=atol(temp.c_str());
				getline(map3, temp);
				idDest=atol(temp.c_str());
				vector<Vertex<Info> *> vertexSet=grafo.getVertexSet();

				for(unsigned int i=0; i< ruas.size();i++){
					if(ruas.at(i).getId() == idRua){
						Vertex<Info> *tempNo, *tempDest;
						for(unsigned int j=0; j<vertexSet.size();j++){
							if(vertexSet.at(j)->getInfo().getId()==idNo)
								tempNo=vertexSet.at(j);
							if(vertexSet.at(j)->getInfo().getId()==idDest)
								tempDest=vertexSet.at(j);

						}
						if(ruas.at(i).isBi())
							grafo.addEdge(tempDest->getInfo(),tempNo->getInfo(),1,ruas.at(i).getNome());
						grafo.addEdge(tempNo->getInfo(),tempDest->getInfo(),1,ruas.at(i).getNome());
					}

				}
			}
		}
	}

	map1.close();
	map2.close();
	map3.close();

	grafo.display();

	return 0;
}

int main(){
	//   runAllTests(argc,argv);
	main2();

	return 0;
}
