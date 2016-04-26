/*
 * Empresa.cpp
 *
 *  Created on: Apr 25, 2016
 *      Author: Diogo
 */

#include "Empresa.h"

namespace std {

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

Empresa::Empresa() {
	readMapa();
	createGraphViewer();
	createRandomEcoPontos();
	geraLixo();
}

const vector<Camiao>& Empresa::getCamioes() const {
	return camioes;
}

void Empresa::setCamioes(const vector<Camiao>& camioes) {
	this->camioes = camioes;
}

const vector<EcoCentro>& Empresa::getEcocentros() const {
	return ecocentros;
}

void Empresa::setEcocentros(const vector<EcoCentro>& ecocentros) {
	this->ecocentros = ecocentros;
}

const vector<EcoPonto>& Empresa::getEcopontos() const {
	return ecopontos;
}

void Empresa::setEcopontos(const vector<EcoPonto>& ecopontos) {
	this->ecopontos = ecopontos;
}

const Graph<Info> Empresa::getMapa() const {
	return mapa;
}

void Empresa::addCamiao(const Camiao camiao) {
	camioes.push_back(camiao);
}

void Empresa::addEcocentro(const EcoCentro ecocentro) {
	ecocentros.push_back(ecocentro);
}

void Empresa::addEcoponto(const EcoPonto ecoponto) {
	ecopontos.push_back(ecoponto);
}

void Empresa::readMapa() {
	string temp;
	vector<Rua> ruas;
	mapa = Graph<Info>();
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

				//				if (tempInfo.getGlat() > latmax) {
				//					latmax = tempInfo.getGlat();
				//				}
				if (tempInfo.getRlat() < Graph<Info>::minLat) {
					Graph<Info>::minLat = tempInfo.getRlat();
				}
				//				if (tempInfo.getGlong() > longmax) {
				//					longmax = tempInfo.getGlong();
				//				}
				if (tempInfo.getRlong() < Graph<Info>::minLong) {
					Graph<Info>::minLong = tempInfo.getRlong();
				}
				Vertex<Info> *vertex;
				mapa.addVertex(tempInfo, vertex);
				//createRandomEcoPonto(vertex);
			}
		}
	}

	cout << Graph<Info>::minLong << "  " << Graph<Info>::minLat << endl;

	//mapa.setP();

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
				vector<Vertex<Info> *> vertexSet = mapa.getVertexSet();

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
							mapa.addEdge(tempDest->getInfo(), tempNo->getInfo(),
									nodeDistance(tempNo, tempDest),
									ruas.at(i).getNome());
						mapa.addEdge(tempNo->getInfo(), tempDest->getInfo(),
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

	mapa.display();
	//cout << "Tamanho: " << mapa.getVertexSet().size() << endl;
	mapa.floydWarshallShortestPath();

}

bool Empresa::createRandomEcoPonto(Vertex<Info>* vertex) {
	int n = rand() % 100;
	if (n < 5) {
		vector<Contentor> contentores;
		contentores.push_back(Contentor(2500, Contentor::amarelo));
		contentores.push_back(Contentor(2500, Contentor::azul));
		contentores.push_back(Contentor(2500, Contentor::preto));
		contentores.push_back(Contentor(2500, Contentor::verde));
		contentores.push_back(Contentor(2500, Contentor::vermelho));
		EcoPonto ecoponto = EcoPonto();
		ecoponto.setContentores(contentores);
		ecoponto.setVertex(vertex);
		if (gv != NULL) {
			gv->setVertexColor(vertex->getInfo().getRelativeId(), "green");
			gv->rearrange();
		}
		ecopontos.push_back(ecoponto);
		return true;
	}
	return false;
}

void Empresa::setMapa(const Graph<Info>& mapa) {
	this->mapa = mapa;
}

Empresa::~Empresa() {
	// TODO Auto-generated destructor stub
}

void Empresa::createRandomEcoPontos() {
	srand(time(NULL));
	ecopontos.clear();
	vector<Vertex<Info> *> v = mapa.getVertexSet();
	vector<Vertex<Info> *>::const_iterator it = v.begin();
	for (; it != v.end(); it++) {
		createRandomEcoPonto(*it);
	}
}

vector<EcoPonto*> Empresa::getPontosInt() {
	cout<<"ecos size "<<ecopontos.size()<<endl;
	vector<EcoPonto*> temp;
	for (unsigned int i = 0; i < ecopontos.size(); i++) {
		if (ecopontos.at(i).check().size() != 0)
			temp.push_back(&ecopontos.at(i));
	}

	return temp;
}

string Empresa::recolha(int ids) {
	int idd, a=ids, b;
	vector<EcoPonto*> pinteresses = getPontosInt();
	double minW = INT_INFINITY;
	stringstream s;

	cout<<"pinteresse "<<pinteresses.size()<< endl;

	while (pinteresses.size() > 0) {
		for (unsigned int i = 0; i < pinteresses.size(); i++) {
			if (mapa.getWeight(a,
					pinteresses.at(i)->getVertex()->getInfo().getRelativeId()) ==INT_MAX){
				pinteresses.erase(pinteresses.begin() + i);
				i--;
				cout << "nao chego la mano " << a << endl;
			}
			else if (mapa.getWeight(a,
					pinteresses.at(i)->getVertex()->getInfo().getRelativeId())
					< minW) {
				b = pinteresses.at(i)->getVertex()->getInfo().getRelativeId();
				pinteresses.erase(pinteresses.begin() + i);
				s << shortestPath(a,b)<<"eco: "<<a<<endl;

				a = b;
				i--;
			}
		}


	}

	minW = INT_INFINITY;
	/*
	for (unsigned int i = 0; i < ecocentros.size(); i++) {
		if (mapa.getWeight(a,
				ecocentros.at(i)->getVertex()->getInfo().getRelativeId()) ==INT_MAX)
			ecocentros.erase(ecocentros.begin() + i);
		if (mapa.getWeight(a,
				ecocentros.at(i)->getVertex()->getInfo().getRelativeId())
				< minW) {
			b = ecocentros.at(i)->getVertex()->getInfo().getRelativeId();
			ecocentros.erase(ecocentros.begin() + i);
		}
	}
*/


	return s.str();



}

void Empresa::createGraphViewer() {
	vector<Vertex<Info> *> vs = mapa.getVertexSet();

	gv = new GraphViewer(100000, 100000, false);

	gv->createWindow(1366, 768);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	string line;

	double minLong = Graph<Info>::minLong;
	double minLat = Graph<Info>::minLat;

	unsigned long idNo = 0;
	int r = 10000000;
	//Read nodes
	vector<Vertex<Info> *>::const_iterator itv = vs.begin(); //typename vector<Vertex<T> *>::const_iterator
	for (; itv != vs.end(); itv++) {
		idNo = (*itv)->getInfo().getRelativeId();
		int y = (int) (((sin((*itv)->getInfo().getRlong() + M_PI)
				- sin(minLong + M_PI)) * r)) % r;
		int x = (int) (((sin((*itv)->getInfo().getRlat()) - sin(minLat)) * r))
				% r;
		gv->addNode(idNo, x, y);
	}

	cout << minLong * M_PI / 180.0 << "  " << minLat * M_PI / 180.0 << endl;

	unsigned long idNoOrigem = 0;
	unsigned long idNoDestino = 0;

	//Read Edges
	itv = vs.begin();
	int cnt = 1;
	for (; itv != vs.end(); itv++) {
		auto adj = (*itv)->getAdj();
		auto ite = adj.begin();
		for (; ite != adj.end(); ite++) {
			cnt++;
			idNoOrigem = (*itv)->getInfo().getRelativeId();
			idNoDestino = ite->getDest()->getInfo().getRelativeId();
			//cout << "S: " << idNoOrigem << " D: " << idNoDestino << " E: " << cnt << endl;
			gv->addEdge(cnt, idNoOrigem, idNoDestino, EdgeType::DIRECTED);
	//		gv->setEdgeLabel(cnt, ite->getName());
		}
	}

	gv->rearrange();
}

string Empresa::shortestPath(int ids, int idd) {
	auto v = mapa.getfloydWarshallPath(mapa.getVertexSet().at(ids)->getInfo(),
			mapa.getVertexSet().at(idd)->getInfo());
	if (v.size() == 0) {
		cout << "Pontos sem ligacao!" << endl;
		return "\0";
	}
	auto it = v.begin();
	stringstream s;
	for (; (it + 1) != v.end(); it++) {
		//cout << mapa.getEdge((*it), (*(it + 1))).getName() << endl;
		s << (*it).getRelativeId() <<"   "<<mapa.getEdge((*it), (*(it + 1))).getName() << endl;
	}
	return s.str();
}

int Empresa::geraLixo(){
	for(unsigned int i=0; i< ecopontos.size();i++){
		ecopontos.at(i).geraLixo();

	}
}

} /* namespace std */
