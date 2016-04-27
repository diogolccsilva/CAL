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
}

const map<Cores::Cor, vector<Camiao*>>& Empresa::getCamioes() const {
	return camioes;
}

const vector<EcoCentro>& Empresa::getEcocentros() const {
	return ecocentros;
}

const vector<EcoPonto>& Empresa::getEcopontos() const {
	return ecopontos;
}

int Empresa::createCamioes() {
	vector<int> capacities = { 3000, 2500, 2000, 1000 };
	vector<Cores::Cor> cores = { Cores::azul, Cores::amarelo, Cores::verde,
			Cores::vermelho, Cores::preto };
	int cnt = 0;
	for (int i = 0; i < 5; i++)
		for (unsigned int j = 0; j < capacities.size(); j++)
			for (int k = 0; k < 5; k++) {
				Camiao camiao = Camiao(capacities.at(j), cores.at(i));
				addCamiao(camiao);
				cnt++;
			}
	return cnt;
}

const Graph<Info> Empresa::getMapa() const {
	return mapa;
}

void Empresa::addCamiao(Camiao& camiao) {
	vcamioes.push_back(camiao);
	camioes[camiao.getCor()].push_back(&camiao);
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

				if (tempInfo.getRlat() > Graph<Info>::maxLat) {
					Graph<Info>::maxLat = tempInfo.getRlat();
				}
				if (tempInfo.getRlat() < Graph<Info>::minLat) {
					Graph<Info>::minLat = tempInfo.getRlat();
				}
				if (tempInfo.getRlong() > Graph<Info>::maxLong) {
					Graph<Info>::maxLong = tempInfo.getRlong();
				}
				if (tempInfo.getRlong() < Graph<Info>::minLong) {
					Graph<Info>::minLong = tempInfo.getRlong();
				}
				Vertex<Info> *vertex;
				mapa.addVertex(tempInfo, vertex);
				//createRandomEcoPonto(vertex);
			}
		}
	}

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
	mapa.floydWarshallShortestPath();

}

bool Empresa::createRandomEcoPonto(Vertex<Info>* vertex) {
	int n = rand() % 100;
	if (n < 5) {
		createEcoPonto(vertex);
		return true;
	}
	return false;
}

Empresa::~Empresa() {
	// TODO Auto-generated destructor stub
}

int Empresa::createRandomEcoPontos() {
	srand(time(NULL));
	ecopontos.clear();
	int cnt = 0;
	vector<Vertex<Info> *> v = mapa.getVertexSet();
	vector<Vertex<Info> *>::const_iterator it = v.begin();
	for (; it != v.end(); it++) {
		if (createRandomEcoPonto(*it))
			cnt++;
	}
	return cnt;
}

vector<EcoPonto*> Empresa::getPontosInt() {
	vector<EcoPonto*> temp;
	for (unsigned int i = 0; i < ecopontos.size(); i++) {
		if (ecopontos.at(i).check().size() != 0) {
			gv->setVertexColor(
					ecopontos.at(i).getVertex()->getInfo().getRelativeId(),
					"blue");
			temp.push_back(&ecopontos.at(i));
		}
	}
	gv->rearrange();
	return temp;
}

double Empresa::recolhaAux(int ids, int idd, queue<EcoPonto*> &q,
		vector<EcoPonto*> pinteresses) {
	vector<EcoPonto*>::iterator it = pinteresses.begin();
	vector<EcoPonto*>::iterator ite = pinteresses.begin();
	int a = ids, c = idd;
	double best = INT_MAX;

	for (; it != pinteresses.end(); it++) {
		int b = (*it)->getVertex()->getInfo().getRelativeId();
		double dist1 = mapa.getWeight(a, b);
		if (dist1 == INT_MAX) {
			pinteresses.erase(it);
			it--;
		}

		double dist2 = mapa.getWeight(b, c);
		if (dist2 == INT_MAX) {
			pinteresses.erase(it);
			it--;
		}

		if (dist1 < best) {
			best = dist1;
			ite = it;
		}
	}
	a = (*ite)->getVertex()->getInfo().getRelativeId();
	if (best != INT_MAX) {
		q.push((*ite));
		pinteresses.erase(ite);
		if (pinteresses.size() > 1) {
			best += recolhaAux(a, c, q, pinteresses);
		}
		return best;
	}
	return 0;
}

string Empresa::recolha(int ids, int idd) {
	vector<EcoPonto*> pinteresses = getPontosInt();
	stringstream s;
	queue<EcoPonto*> q;
	if (mapa.getWeight(ids, idd) == INT_MAX) {
		return "Nao ha caminho da origem ao destino!";
	}
	gv->setVertexColor(ids, "red");
	gv->setVertexColor(idd, "red");
	gv->rearrange();
	recolhaAux(ids, idd, q, pinteresses);
	int a = ids;
	cout << "q.size(): " << q.size() << endl;
	while (q.size() > 0) {
		int b = q.front()->getVertex()->getInfo().getRelativeId();
		s << shortestPath(a, b) << "eco: " << b << endl;
		a = b;
		q.pop();
	}
	s << shortestPath(a, idd) << "Estacao de tratamento: " << idd << endl;
	gv->rearrange();
	return s.str();
}

//double Empresa::recolhaAux(int ids, queue<EcoPonto*> &q,
//		vector<EcoPonto*> pinteresses) {
//	vector<EcoPonto*>::iterator it = pinteresses.begin();
//	vector<EcoPonto*>::iterator ite = pinteresses.begin();
//	int a = ids;
//	double best = INT_MAX;
//	for (; it != pinteresses.end(); it++) {
//		int b = (*it)->getVertex()->getInfo().getRelativeId();
//		double dist = mapa.getWeight(a, b);
//		cout << "a: " << a << " b: " << b << " dist: " << dist << endl;
//		if (dist == INT_MAX) {
//			pinteresses.erase(it);
//			it--;
//		}
//		if (dist < best) {
//			best = dist;
//			ite = it;
//		}
//		//cout << "dist: " << dist << endl;
//	}
//	a = (*ite)->getVertex()->getInfo().getRelativeId();
//	cout << "best: " << best << " na: " << a << endl;
//	if (best != INT_MAX) {
//		q.push((*ite));
//		pinteresses.erase(ite);
//		if (pinteresses.size() > 1) {
//			best += recolhaAux(a, q, pinteresses);
//		}
//		cout << "Return best: " << best << endl;
//		return best;
//	}
//	return 0;
//}

//string Empresa::recolha(int ids) {
//	vector<EcoPonto*> pinteresses = getPontosInt();
//	double minW = INT_INFINITY;
//	stringstream s;
//
//	cout << "pinteresse " << pinteresses.size() << endl;
//	queue<EcoPonto*> q;
//	recolhaAux(ids, q, pinteresses);
//	int a = ids;
//	cout << "a: " << a << endl;
//	cout << "q.size: " << q.size() << endl;
//	while (q.size() > 0) {
//		int b = q.front()->getVertex()->getInfo().getRelativeId();
//		cout << "b: " << b << endl;
//		s << shortestPath(a, b) << "eco: " << b << endl;
//		a = b;
//		q.pop();
//	}
//	minW = INT_INFINITY;
//
//	return s.str();
//
//}

void Empresa::createGraphViewer() {
	vector<Vertex<Info> *> vs = mapa.getVertexSet();

	gv = new GraphViewer(100000, 100000, false);

	gv->createWindow(1366, 768);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	string line;

	double minLong = Graph<Info>::minLong - 2 * M_PI;
	double minLat = Graph<Info>::minLat - 2 * M_PI;
	double maxLat = Graph<Info>::maxLat - 2 * M_PI;
	double maxLong = Graph<Info>::maxLong - 2 * M_PI;

	int r = 60000000;
	int ymin = (minLong / M_PI) * r;
	int xmin = (log((1 + sin(minLat)) / (1 - sin(minLat))) / (4 * M_PI)) * r;
	int ymax = (maxLong / M_PI) * r;
	int xmax = (log((1 + sin(maxLat)) / (1 - sin(maxLat))) / (4 * M_PI)) * r;
	cout << "xmin: " << xmin << " xmax: " << xmax << " ymin: " << ymin
			<< " ymax: " << ymax << endl;

	unsigned long idNo = 0;
	//Read nodes
	vector<Vertex<Info> *>::const_iterator itv = vs.begin(); //typename vector<Vertex<T> *>::const_iterator
	for (; itv != vs.end(); itv++) {
		idNo = (*itv)->getInfo().getRelativeId();
		double longt = (*itv)->getInfo().getRlong() - 2 * M_PI;
		double latt = (*itv)->getInfo().getRlat() - 2 * M_PI;
		int y = -((longt / M_PI) * r - (ymax + ymin) / 2);
		int x = (log((1 + sin(latt)) / (1 - sin(latt))) / (4 * M_PI)) * r
				- (xmin + xmax) / 2;
		cout << "x: " << x << " y: " << y << endl;

//		double x = r * cos(latt) * cos(longt);
//		double y = r * cos(longt) * sin(longt);
//		int y = (int) (((sin((*itv)->getInfo().getRlong() + M_PI)
//				- sin(minLong + M_PI)) * r)) % r;
//		int x = (int) (((sin((*itv)->getInfo().getRlat()) - sin(minLat)) * r))
//				% r;
		gv->addNode(idNo, x, y);
	}

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
			int id = ite->getID();
			gv->addEdge(id, idNoOrigem, idNoDestino, EdgeType::DIRECTED);
			//gv->setEdgeLabel(cnt, ite->getName());
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
		gv->setEdgeColor(mapa.getEdge((*it), (*(it + 1))).getID(), "red");
		s << (*it).getRelativeId() << "   "
				<< mapa.getEdge((*it), (*(it + 1))).getName() << endl;
	}
	return s.str();
}

string Empresa::getSCamioes() const {
	vector<Camiao>::const_iterator it = vcamioes.begin();
	stringstream s;
	for (; it != vcamioes.end(); it++) {
		s << (*it) << endl;
	}
	return s.str();
}

string Empresa::getSCentros() const {
	vector<EcoCentro>::const_iterator it = ecocentros.begin();
	stringstream s;
	for (; it != ecocentros.end(); it++) {
		s << (*it) << endl;
	}
	return s.str();
}

string Empresa::getSPontos() const {
	vector<EcoPonto>::const_iterator it = ecopontos.begin();
	stringstream s;
	for (; it != ecopontos.end(); it++) {
		s << (*it) << endl;
	}
	return s.str();
}

int Empresa::eraseEcoPontos() {
	vector<EcoPonto>::iterator it = ecopontos.begin();
	int cnt = 0;
	for (; it != ecopontos.end(); it++) {
		gv->setVertexColor(it->getVertex()->getInfo().getRelativeId(),
				"yellow");
		cnt++;
	}
	gv->rearrange();
	ecopontos.clear();
	EcoPonto::resetCnt();
	return cnt;
}

bool Empresa::removeEcoPonto(int id) {
	vector<EcoPonto>::iterator it = ecopontos.begin();
	for (; it != ecopontos.end(); it++) {
		if (it->getId() == id) {
			gv->setVertexColor(it->getVertex()->getInfo().getRelativeId(),
					"yellow");
			gv->rearrange();
			ecopontos.erase(it);
			return true;
		}
	}
	return false;
}

bool Empresa::createEcoPonto(int idv) {
	vector<Vertex<Info> *>::const_iterator it = mapa.getVertexSet().begin();
	for (; it != mapa.getVertexSet().end(); it++) {
		if ((*it)->getInfo().getRelativeId() == idv) {
			createEcoPonto((*it));
			return true;
		}
	}
	return false;
}

bool Empresa::createEcoCentro(int idv) {
	vector<Vertex<Info> *>::const_iterator it = mapa.getVertexSet().begin();
	for (; it != mapa.getVertexSet().end(); it++) {
		if ((*it)->getInfo().getRelativeId() == idv) {
			createEcoCentro((*it));
			return true;
		}
	}
	return false;
}

void Empresa::createEcoPonto(Vertex<Info>* vertex) {
	vector<Contentor> contentores;
	contentores.push_back(Contentor(2500, Cores::amarelo));
	contentores.push_back(Contentor(2500, Cores::azul));
	contentores.push_back(Contentor(2500, Cores::preto));
	contentores.push_back(Contentor(2500, Cores::verde));
	contentores.push_back(Contentor(2500, Cores::vermelho));
	EcoPonto ecoponto = EcoPonto();
	ecoponto.setContentores(contentores);
	ecoponto.setVertex(vertex);
	if (gv != NULL) {
		gv->setVertexColor(vertex->getInfo().getRelativeId(), "green");
		gv->rearrange();
	}
	ecopontos.push_back(ecoponto);
}

void Empresa::createEcoCentro(Vertex<Info>* vertex) {
	EcoCentro ecc(vertex);
	if (gv != NULL) {
		gv->setVertexColor(vertex->getInfo().getRelativeId(), "black");
		gv->rearrange();
	}
	ecocentros.push_back(ecc);
}

//string Empresa::shortestPath(int ids, int idd) {
//	auto v = mapa.getfloydWarshallPath(mapa.getVertexSet().at(ids)->getInfo(),
//			mapa.getVertexSet().at(idd)->getInfo());
//	if (v.size() == 0) {
//		cout << "Pontos sem ligacao!" << endl;
//		return "\0";
//	}
//	auto it = v.begin();
//	stringstream s;
//	for (; (it + 1) != v.end(); it++) {
//		//cout << mapa.getEdge((*it), (*(it + 1))).getName() << endl;
//		s << (*it).getRelativeId() << "   "
//				<< mapa.getEdge((*it), (*(it + 1))).getName() << endl;
//	}
//	return s.str();
//}

int Empresa::geraLixo() {
	for (unsigned int i = 0; i < ecopontos.size(); i++) {
		ecopontos.at(i).geraLixo();
	}
}

//alterado
double Empresa::getLixoTotal(Cores::Cor cor) {
	double maxLixo = 0;
	vector<EcoPonto*> pint = getPontosInt();
	vector<EcoPonto*>::const_iterator it = pint.begin();

	for (; it != pint.end(); it++) {
		vector<Contentor>::const_iterator ite = (*it)->getContentores().begin();
		for (; ite != (*it)->getContentores().end(); ite++) {
			if ((*ite).getCor() == cor
					&& ((*ite).getOcupada() / (*ite).getUtil()) >= 0.7) {
				//cout << (*ite).getCor() << " " << ((*ite).getOcupada() / (*ite).getUtil()) << endl;
				maxLixo += (*ite).getOcupada();
			}
		}
	}
	cout << "Lixo a recolher: " << maxLixo << endl;
	return maxLixo;
}

//alterado
void Empresa::dynamic() {
	vector<Cores::Cor> cores = { Cores::azul, Cores::amarelo, Cores::verde,
			Cores::vermelho, Cores::preto };
	for (int i = 0; i < 5; i++) {
		if (i == 0)
			cout
					<< "--------------------------------   Contetor Azul   -----------------------------------"
					<< endl;
		else if (i == 1)
			cout
					<< "--------------------------------  Contetor Amarelo -----------------------------------"
					<< endl;
		else if (i == 2)
			cout
					<< "--------------------------------   Contetor Verde  -----------------------------------"
					<< endl;
		else if (i == 3)
			cout
					<< "-------------------------------- Contetor Vermelho -----------------------------------"
					<< endl;
		else
			cout
					<< "-------------------------------- Contetor Generico -----------------------------------"
					<< endl;

		int n = ceil(getLixoTotal(cores.at(i)));
		vector<int> capacityDone;
		vector<int> lastTruck;
		vector<int> capacities = { 0, 3000, 2500, 2000, 1000 }; //0 is an invalid coin

		for (int i = 0; i <= n; i++) {
			capacityDone.push_back(0);
			lastTruck.push_back(0);
		}

		//exactly like the backpack problem (just a little tuneup)
		for (unsigned int i = 1; i < capacities.size(); i++) {
			int capacity = capacities.at(i);
			if (capacity <= n) {
				for (int j = capacity; j <= n; j++) {
					//consider also the value already saved
					int remainder = j - capacity;
					if (capacityDone.at(j) + capacity <= j
							&& (capacity + capacityDone.at(remainder)) <= j) {
						capacityDone.at(j) = capacity
								+ capacityDone.at(remainder);
						lastTruck.at(j) = i;
					}
				}
			}
		}

		int temp = n, counter = 0, extraTruck = 0;

		if (capacityDone.at(n) != n) {
			temp -= (n - capacityDone.at(n));
			counter++;
			for (unsigned int i = 0; i < capacities.size(); i++)
				if ((n - capacityDone.at(n)) <= capacities.at(i))
					extraTruck = capacities.at(i);
		}

		while (temp > 0) {
			//cout << "temp " << temp << endl;
			cout << capacities.at(lastTruck.at(temp)) << endl;
			temp -= capacities.at(lastTruck.at(temp));
			counter++;
		}
		if (extraTruck != 0)
			cout << "Requires extra Truck " << extraTruck << endl;
		cout << "Number of Trucks: " << counter << endl;
	}
}

} /* namespace std */
