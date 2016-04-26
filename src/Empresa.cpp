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
	mapa = readMapa();

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

Graph<Info> Empresa::readMapa() {
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
				grafo.addVertex(tempInfo, vertex);
				createRandomEcoPonto(vertex);
			}
		}
	}

	cout << Graph<Info>::minLong << "  " << Graph<Info>::minLat << endl;

	//grafo.setP();

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

bool Empresa::createRandomEcoPonto(Vertex<Info>* vertex) {
	srand(time(NULL));
	int n = rand() % 100;
	if (n < 20) {
		vector<Contentor> contentores;
		contentores.push_back(Contentor(2500, Contentor::amarelo));
		contentores.push_back(Contentor(2500, Contentor::azul));
		contentores.push_back(Contentor(2500, Contentor::preto));
		contentores.push_back(Contentor(2500, Contentor::verde));
		contentores.push_back(Contentor(2500, Contentor::vermelho));
		EcoPonto ecoponto = EcoPonto();
		ecoponto.setContentores(contentores);
		ecoponto.setVertex(vertex);
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
	ecopontos.clear();
	vector<Vertex<Info> *> v = mapa.getVertexSet();
	vector<Vertex<Info> *>::const_iterator it = v.begin();
	for (; it != v.end(); it++) {
		createRandomEcoPonto(*it);
	}
}

vector<EcoPonto*> Empresa::getPontosInt() {
	vector<EcoPonto*> temp;
	for (unsigned int i = 0; i < ecopontos.size(); i++) {
		if (ecopontos.at(i).check().size() != 0)
			temp.push_back(&ecopontos.at(i));
	}

	return temp;
}

void Empresa::recolha() {
	int ids, idd, a, b;
	cin >> ids >> idd;
	vector<EcoPonto*> pinteresses = getPontosInt();
	double minW = INT_INFINITY;

	while (pinteresses.size() > 0) {
		for (unsigned int i = 0; i < pinteresses.size(); i++) {
			if (mapa.getWeight(ids,
					pinteresses.at(i)->getVertex()->getInfo().getRelativeId()) ==INT_MAX)
				pinteresses.erase(pinteresses.begin() + i);
			if (mapa.getWeight(ids,
					pinteresses.at(i)->getVertex()->getInfo().getRelativeId())
					< minW) {
				b = pinteresses.at(i)->getVertex()->getInfo().getRelativeId();
				pinteresses.erase(pinteresses.begin() + i);
			}
		}
		auto v = mapa.getfloydWarshallPath(mapa.getVertexSet().at(a)->getInfo(),
				mapa.getVertexSet().at(b)->getInfo());
		a = b;
	}

	/*
	 auto v = mapa.getfloydWarshallPath(mapa.getVertexSet().at(ids)->getInfo(),
	 mapa.getVertexSet().at(idd)->getInfo());
	 if (v.size() == 0) {
	 cout << "Pontos sem ligacao!" << endl;
	 return;
	 }
	 auto it = v.begin();
	 for (; it != v.end(); it++) {
	 cout << it->getRelativeId() << endl;
	 }*/

}

string Empresa::shortestPath() {
	int ids, idd;
	cin >> ids >> idd;
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
		s << mapa.getEdge((*it), (*(it + 1))).getName() << endl;
	}
	return s.str();
}

} /* namespace std */
