/*
 * Empresa.cpp
 *
 */

#include "Company.h"

using namespace std;

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

Company::Company() {
	readMap();
	createGraphViewer();
}

Company::~Company() {
}

const map<Colors::Color, vector<Truck>>& Company::getTrucks() const {
	return trucks;
}

int Company::getNTrucks() const {
	return vtrucks.size();
}

const vector<RecyclingCenter>& Company::getReCenters() const {
	return recenters;
}

const vector<RecyclingBin>& Company::getReBins() const {
	return rebins;
}

int Company::createTrucks() {
	vector<int> capacities = { 3000, 2500, 2000, 1000 };
	vector<Colors::Color> cores = { Colors::blue, Colors::yellow, Colors::green,
			Colors::red, Colors::black };
	int cnt = 0;
	for (int i = 0; i < 5; i++)
		for (unsigned int j = 0; j < capacities.size(); j++)
			for (int k = 0; k < 5; k++) {
				Truck camiao = Truck(capacities.at(j), cores.at(i));
				addTruck(camiao);
				cnt++;
			}
	return cnt;
}

const Graph<Info> Company::getGMap() const {
	return gmap;
}

void Company::addTruck(Truck& camiao) {
	vtrucks.push_back(camiao);
	trucks[camiao.getColor()].push_back(camiao);
}

void Company::addReCenter(const RecyclingCenter ecocentro) {
	recenters.push_back(ecocentro);
}

void Company::addReBin(const RecyclingBin ecoponto) {
	rebins.push_back(ecoponto);
}

void Company::readMap() {
	string temp;
	vector<Street> ruas;
	gmap = Graph<Info>();
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
				Vertex<Info> *vertex = NULL;
				gmap.addVertex(tempInfo, vertex);
				//createRandomEcoPonto(vertex);
			}
		}
	}

	//mapa.setP();

	if (map2.is_open()) {
		while (!map2.eof()) {
			Street tempRua = Street();
			getline(map2, temp, ';');
			if (temp != "") {
				tempRua.setId(atol(temp.c_str()));
				getline(map2, temp, ';');
				tempRua.setName(temp);
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
				vector<Vertex<Info> *> vertexSet = gmap.getVertexSet();

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
							gmap.addEdge(tempDest->getInfo(), tempNo->getInfo(),
									nodeDistance(tempNo, tempDest),
									ruas.at(i).getName());
						gmap.addEdge(tempNo->getInfo(), tempDest->getInfo(),
								nodeDistance(tempNo, tempDest),
								ruas.at(i).getName());
					}
				}
			}
		}
	}

	map1.close();
	map2.close();
	map3.close();

	gmap.floydWarshallShortestPath();

}

bool Company::createRandomReBin(Vertex<Info>* vertex) {
	int n = rand() % 100;
	if (n < 5) {
		createReBin(vertex);
		return true;
	}
	return false;
}

int Company::createRandomReBins() {
	srand(time(NULL));
	eraseReBins();

	int cnt = 0;
	vector<Vertex<Info> *> v = gmap.getVertexSet();
	vector<Vertex<Info> *>::const_iterator it = v.begin();
	for (; it != v.end(); it++) {
		if (createRandomReBin(*it))
			cnt++;
	}
	return cnt;
}

vector<RecyclingBin*> Company::getIntPoints() {
	vector<RecyclingBin*> temp;

	resetReBinsColors();
	for (unsigned int i = 0; i < rebins.size(); i++) {
		if (rebins.at(i).check().size() != 0) {
			gv->setVertexColor(
					rebins.at(i).getVertex()->getInfo().getRelativeId(),
					ORANGE);
			temp.push_back(&rebins.at(i));
		}
	}
	gv->rearrange();
	return temp;
}

double Company::unlimitedRunAux(int ids, int idd, queue<RecyclingBin*> &q,
		vector<RecyclingBin*> pinteresses) {
	vector<RecyclingBin*>::iterator it = pinteresses.begin();
	vector<RecyclingBin*>::iterator ite = pinteresses.begin();
	int a = ids, c = idd;
	double best = INT_MAX;

	for (; it != pinteresses.end(); it++) {
		int b = (*it)->getVertex()->getInfo().getRelativeId();
		double dist1 = gmap.getWeight(a, b);
		if (dist1 == INT_MAX) {
			pinteresses.erase(it);
			it--;
		}

		double dist2 = gmap.getWeight(b, c);
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
			best += unlimitedRunAux(a, c, q, pinteresses);
		}
		return best;
	}
	return 0;
}

string Company::unlimitedRun(int ids, int idd) {
	vector<RecyclingBin*> pinteresses = getIntPoints();
	stringstream s;
	queue<RecyclingBin*> q;
	if (gmap.getWeight(ids, idd) == INT_MAX) {
		return "Nao ha caminho da origem ao destino!";
	}
	gv->setVertexColor(ids, "red");
	gv->setVertexColor(idd, "red");
	gv->rearrange();
	unlimitedRunAux(ids, idd, q, pinteresses);
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

void Company::createGraphViewer() {
	vector<Vertex<Info> *> vs = gmap.getVertexSet();

	gv = new GraphViewer(100000, 100000, false);

	gv->createWindow(1366, 768);

	gv->defineEdgeColor(BLACK);
	gv->defineVertexColor(LIGHT_GRAY);

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

string Company::shortestPath(int ids, int idd) {
	auto v = gmap.getfloydWarshallPath(gmap.getVertexSet().at(ids)->getInfo(),
			gmap.getVertexSet().at(idd)->getInfo());

	if (v.size() == 0) {
		cout << "Pontos sem ligacao!" << endl;
		return "\0";
	}
	auto it = v.begin();
	stringstream s;
	for (; (it + 1) != v.end(); it++) {
		gv->setEdgeColor(gmap.getEdge((*it), (*(it + 1))).getID(), "red");
		s << (*it).getRelativeId() << "   "
				<< gmap.getEdge((*it), (*(it + 1))).getName() << endl;
	}
	return s.str();
}

string Company::getSTrucks() const {
	vector<Truck>::const_iterator it = vtrucks.begin();
	stringstream s;
	for (; it != vtrucks.end(); it++) {
		s << (*it) << endl;
	}
	return s.str();
}

string Company::getSCenters() const {
	vector<RecyclingCenter>::const_iterator it = recenters.begin();
	stringstream s;
	for (; it != recenters.end(); it++) {
		s << (*it) << endl;
	}
	return s.str();
}

string Company::getSBins() const {
	vector<RecyclingBin>::const_iterator it = rebins.begin();
	stringstream s;
	for (; it != rebins.end(); it++) {
		s << (*it) << endl;
	}
	return s.str();
}

int Company::eraseReBins() {
	vector<RecyclingBin>::iterator it = rebins.begin();
	int cnt = 0;

	for (; it != rebins.end(); it++) {
		gv->setVertexColor(it->getVertex()->getInfo().getRelativeId(),
		LIGHT_GRAY);
		cnt++;
	}
	gv->rearrange();
	rebins.clear();
	RecyclingBin::resetCnt();
	return cnt;
}

int Company::eraseReCenters() {
	vector<RecyclingCenter>::iterator it = recenters.begin();
	int cnt = 0;
	for (; it != recenters.end(); it++) {
		gv->setVertexColor(it->getVertex()->getInfo().getRelativeId(),
		LIGHT_GRAY);
		cnt++;
	}
	gv->rearrange();
	recenters.clear();
	RecyclingCenter::resetCnt();
	return cnt;
}

int Company::eraseTrucks() {
	int cnt = vtrucks.size();
	trucks.clear();
	vtrucks.clear();
	Truck::resetCnt();
	return cnt;
}

void Company::addDriver(const Driver driver) {
	drivers.push_back(driver);
}

void Company::createRandomDrivers(int n) {
	vector<string> firstname = { "Maria", "Davi", "Joao", "Miguel", "Pedro",
			"Arthur", "Ana", "Alice", "Gabriel", "Lucas", "Laura", "Julia",
			"Bernardo", "Heitor", "Enzo", "Valentina", "Guilherme", "Helena",
			"Sophia", "Rafael", "Sofia", "Manuela", "Beatriz", "Gustavo",
			"Matheus", "Lorenzo", "Samuel", "Luiza", "Mariana", "Henrique",
			"Theo", "Isabella", "Lara", "Felipe", "Livia", "Nicolas", "Daniel",
			"Heloisa", "Isabela", "Leonardo", "Leticia", "Lorena", "Giovanna",
			"Isadora", "Eduardo", "Luiz", "Anna", "Jose", "Luisa", "Rafaela" };
	vector<string> lastname = { };
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> fn(0, firstname.size() - 1);
	for (int i = 0; i < n; i++) {
		string name = firstname[fn(gen)];
		Driver d(name);
		addDriver(d);
	}
}

string Company::getSDrivers() const {
	vector<Driver>::const_iterator it;
	stringstream s;
	for (it = drivers.begin(); it != drivers.end(); it++) {
		s << (*it) << endl;
	}
	return s.str();
}

bool Company::setDriverOccupied(Driver driver) {
	vector<Driver>::iterator it;
	for (it = drivers.begin(); it != drivers.end(); it++) {
		if (it->getId() == driver.getId()) {
			it->setOccupied(true);
			return true;
		}
	}
	return false;
}

bool Company::setDriverFree(Driver driver) {
	vector<Driver>::iterator it;
	for (it = drivers.begin(); it != drivers.end(); it++) {
		if (it->getId() == driver.getId()) {
			it->setOccupied(false);
			return true;
		}
	}
	return false;
}

vector<Driver> Company::getDriver(string name) const {
	vector<Driver> res;
	vector<Driver>::const_iterator it;
	string tmp2 = name;
	transform(tmp2.begin(), tmp2.end(), tmp2.begin(), towlower);

	for (it = drivers.begin(); it != drivers.end(); it++) {
		string tmp1 = it->getName();
		transform(tmp1.begin(), tmp1.end(), tmp1.begin(), towlower);
		if (editDistance(tmp2, tmp1) <= (tmp1.size() / 2)
				|| exactCmp(tmp1, tmp2) > 0) {
			res.push_back((*it));
		}
	}

	sort(res.begin(), res.end(), [tmp2](const Driver& a, const Driver& b)
	{
		string an = a.getName();
		transform(an.begin(), an.end(), an.begin(), towlower);
		string bn = b.getName();
		transform(bn.begin(), bn.end(), bn.begin(), towlower);
		if(exactCmp(an,tmp2) != 0 && exactCmp(bn,tmp2) != 0)
		return editDistance(tmp2, an) < editDistance(tmp2, bn);
		return (exactCmp(an,tmp2) != 0);
	});

	return res;
}

vector<Driver> Company::getExactDriver(string name) const {
	vector<Driver> res;
	vector<Driver>::const_iterator it;
	string tmp2 = name;
	transform(tmp2.begin(), tmp2.end(), tmp2.begin(), towlower);
	for (it = drivers.begin(); it != drivers.end(); it++) {
		string tmp1 = it->getName();
		transform(tmp1.begin(), tmp1.end(), tmp1.begin(), towlower);
		if (exactCmp(tmp1, tmp2)) {
			res.push_back(*it);
		}
	}
	return res;
}

vector<Driver> Company::getApproxDriver(string name) const {
	vector<Driver> res;
	vector<Driver>::const_iterator it;
	string tmp2 = name;
	transform(tmp2.begin(), tmp2.end(), tmp2.begin(), towlower);
	for (it = drivers.begin(); it != drivers.end(); it++) {
		string tmp1 = it->getName();
		transform(tmp1.begin(), tmp1.end(), tmp1.begin(), towlower);
		if (editDistance(tmp2, tmp1) <= (tmp1.size() / 2)) {
			res.push_back((*it));
		}
	}
	sort(res.begin(), res.end(), [tmp2](const Driver& a, const Driver& b)
	{
		string an = a.getName();
		transform(an.begin(), an.end(), an.begin(), towlower);
		string bn = b.getName();
		transform(bn.begin(), bn.end(), bn.begin(), towlower);
		return editDistance(tmp2, an) < editDistance(tmp2, bn);
	});
	return res;
}

bool Company::removeDriver(int id) {
	vector<Driver>::iterator it;
	for (it = drivers.begin(); it != drivers.end(); it++) {
		if (it->getId() == id) {
			drivers.erase(it);
			return true;
		}
	}
	return false;
}

int Company::eraseDrivers() {
	int cnt = drivers.size();
	drivers.clear();
	Driver::resetCnt();
	return cnt;
}

bool Company::removeReBin(int id) {
	vector<RecyclingBin>::iterator it = rebins.begin();
	for (; it != rebins.end(); it++) {
		if (it->getId() == id) {
			gv->setVertexColor(it->getVertex()->getInfo().getRelativeId(),
			LIGHT_GRAY);
			gv->rearrange();
			rebins.erase(it);
			return true;
		}
	}
	return false;
}

bool Company::createReBins(int idv) {
	vector<Vertex<Info> *>::const_iterator it = gmap.getVertexSet().begin();
	for (; it != gmap.getVertexSet().end(); it++) {
		if ((*it)->getInfo().getRelativeId() == idv) {
			createReBin((*it));
			return true;
		}
	}
	return false;
}

bool Company::createReCenter(int idv) {
	vector<Vertex<Info> *>::const_iterator it = gmap.getVertexSet().begin();
	for (; it != gmap.getVertexSet().end(); it++) {
		if ((*it)->getInfo().getRelativeId() == idv) {
			createReCenter((*it));
			return true;
		}
	}
	return false;
}

void Company::createReBin(Vertex<Info>* vertex) {
	vector<Container> contentores;
	contentores.push_back(Container(2500, Colors::yellow));
	contentores.push_back(Container(2500, Colors::blue));
	contentores.push_back(Container(2500, Colors::black));
	contentores.push_back(Container(2500, Colors::green));
	contentores.push_back(Container(2500, Colors::red));
	RecyclingBin ecoponto = RecyclingBin();
	ecoponto.setContainers(contentores);
	ecoponto.setVertex(vertex);

	if (gv != NULL) {
		gv->setVertexColor(vertex->getInfo().getRelativeId(), CYAN);
		gv->rearrange();
	}
	rebins.push_back(ecoponto);
}

void Company::createReCenter(Vertex<Info>* vertex) {
	RecyclingCenter ecc(vertex);
	if (gv != NULL) {
		gv->setVertexColor(vertex->getInfo().getRelativeId(), "black");
		gv->rearrange();
	}
	recenters.push_back(ecc);
}

void Company::generateGarbage() {
	for (unsigned int i = 0; i < rebins.size(); i++) {
		rebins.at(i).generateGarbage();
	}
}

double Company::getTotalGarbage(Colors::Color cor) {
	double maxLixo = 0;
	vector<RecyclingBin*> pint = getIntPoints();
	vector<RecyclingBin*>::const_iterator it = pint.begin();

	for (; it != pint.end(); it++) {
		vector<Container>::const_iterator ite = (*it)->getContainers().begin();
		for (; ite != (*it)->getContainers().end(); ite++) {
			if ((*ite).getColor() == cor
					&& ((*ite).getOcupiedCapacity() / (*ite).getUsableCapacity())
							>= 0.7) {
				//cout << (*ite).getCor() << " " << ((*ite).getOcupada() / (*ite).getUtil()) << endl;
				maxLixo += (*ite).getOcupiedCapacity();
			}
		}
	}
	//cout << "Lixo a recolher: " << maxLixo << endl;
	return maxLixo;
}

void Company::dynamic() {
	vector<Colors::Color> cores = { Colors::blue, Colors::yellow, Colors::green,
			Colors::red, Colors::black };

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

		int n = ceil(getTotalGarbage(cores.at(i)));
		vector<int> capacityDone;
		vector<int> lastTruck;
		vector<int> capacities = { 0, 3000, 2500, 2000, 1000 }; //0 is an invalid capacity

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
			cout << capacities.at(lastTruck.at(temp)) << endl;
			temp -= capacities.at(lastTruck.at(temp));
			counter++;
		}
		if (extraTruck != 0)
			cout << "Requires extra Truck " << extraTruck << endl;
		cout << "Number of Trucks: " << counter << endl;
	}
}

pair<int, int> Company::getNecessaryTrucks(Colors::Color color) {
	pair<int, int> res;
	int n = ceil(getTotalGarbage(color));
	vector<int> capacityDone;
	vector<int> lastTruck;
	vector<int> capacities = { 0, 3000, 2500, 2000, 1000 }; //0 is an invalid capacity
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
					capacityDone.at(j) = capacity + capacityDone.at(remainder);
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
		temp -= capacities.at(lastTruck.at(temp));
		counter++;
	}
	res.first = counter;
	res.second = extraTruck;
	return res;
}

pair<int, int> Company::getNecessaryTrucks() {
	vector<Colors::Color> colors = { Colors::blue, Colors::yellow,
			Colors::green, Colors::red, Colors::black };
	pair<int, int> total;
	total.first = 0;
	total.second = 0;
	for (unsigned int i = 0; i < colors.size(); i++) {
		pair<int, int> temp = getNecessaryTrucks(colors.at(i));
		total.first += temp.first;
		total.second += temp.second;
	}
	return total;
}

vector<int> Company::getStreet(string name) {
	vector<int> ids;
	resetEdgeColors();
	for (unsigned int i = 0; i < gmap.getVertexSet().size(); i++) {
		for (unsigned int j = 0; j < gmap.getVertexSet().at(i)->getAdj().size();
				j++) {
			string tmp1 = gmap.getVertexSet().at(i)->getAdj().at(j).getName();
			transform(tmp1.begin(), tmp1.end(), tmp1.begin(), towlower);

			if (tmp1 == name) {
				gv->setEdgeColor(
						gmap.getVertexSet().at(i)->getAdj().at(j).getID(),
						"red");
				auto a = gmap.getVertexSet().at(i)->getAdj().at(j);
				auto s = a.getDest()->getInfo();
				ids.push_back(s.getRelativeId());

			}
		}
	}
	gv->rearrange();
	return ids;
}

vector<string> Company::findAproxRoad(string toSearch) {
	unordered_set<string> ruas;
	string rua, tmp2 = toSearch;
	int idv;

	transform(tmp2.begin(), tmp2.end(), tmp2.begin(), towlower);

	for (unsigned int i = 0; i < gmap.getVertexSet().size(); i++) {
		for (unsigned int j = 0; j < gmap.getVertexSet().at(i)->getAdj().size();
				j++) {
			string tmp1 = gmap.getVertexSet().at(i)->getAdj().at(j).getName();
			transform(tmp1.begin(), tmp1.end(), tmp1.begin(), towlower);
			//	cout<<tmp1<< " "<<editDistance(tmp2,tmp1)<<" "<<exactCmp(tmp1,tmp2)<<endl;
			if (tmp1 != ""
					&& ((editDistance(tmp2, tmp1) <= 10)
							|| exactCmp(tmp1, tmp2) > 0)) {
				ruas.insert(tmp1);
				//	cout << tmp1 << " exact " <<exactCmp(tmp1, tmp2) <<	" aprox "<< editDistance(tmp2, tmp1)<<endl;
			}
		}
	}
	vector<string> ruas2(ruas.begin(), ruas.end());
	if (ruas.size() > 0) {
		sort(ruas2.begin(), ruas2.end(),
				[tmp2](const string& a, const string& b)
				{	if(exactCmp(a,tmp2) != 0 && exactCmp(b,tmp2) != 0)
					return editDistance(tmp2, a) < editDistance(tmp2, b);
					else return (exactCmp(a,tmp2) != 0);});
		int i = 1;
		if (editDistance(tmp2, ruas2.at(0)) == 0)
			cout << i << " " << ruas2.at(0) << endl;
		else {
			for (auto rua : ruas2)
				cout << i++ << " " << rua << endl;
		}
	}
	return ruas2;
}

string Company::getUnlimitedRun(int idp, int idc) {
	vector<RecyclingCenter>::const_iterator itp, itc;
	vector<RecyclingCenter>::const_iterator it = recenters.begin();
	int cnt = 0;
	for (; it != recenters.end(); it++) {
		if (it->getId() == idp) {
			itp = it;
			cnt++;
		}
		if (it->getId() == idc) {
			itc = it;
			cnt++;
		}
		if (cnt == 2) {
			return unlimitedRun(itp->getVertex()->getInfo().getRelativeId(),
					itc->getVertex()->getInfo().getRelativeId());
		}
	}
	return "Ecocentros inexistentes!\n";
}

vector<Driver> Company::getDrivers() const {
	return drivers;
}

bool Company::recCenterExists(int id) {
	vector<RecyclingCenter>::const_iterator it = recenters.begin();
	for (; it != recenters.end(); it++) {
		if (it->getId() == id)
			return true;
	}
	return false;
}

string Company::getLimitedRun(int idp, int idc) {
	vector<RecyclingCenter>::const_iterator itp, itc;
	vector<RecyclingCenter>::const_iterator it = recenters.begin();
	int cnt = 0;

	for (; it != recenters.end(); it++) {
		if (it->getId() == idp) {
			itp = it;
			cnt++;
		}
		if (it->getId() == idc) {
			itc = it;
			cnt++;
		}
		if (cnt == 2) {
			return limitedRun(itp->getVertex()->getInfo().getRelativeId(),
					itc->getVertex()->getInfo().getRelativeId());
		}
	}
	return "Ecocentros inexistentes!\n";
}

double Company::limitedRunAux(int ids, int idd, queue<RecyclingBin*> &q,
		vector<RecyclingBin*> &pinteresses,
		vector<RecyclingBin*> pinteressestemp, Truck camiao,
		double &totalGarbage, Colors::Color color, bool &finishedCollecting) {
	vector<RecyclingBin*>::iterator it = pinteressestemp.begin();
	vector<RecyclingBin*>::iterator ite = pinteressestemp.begin();
	int a = ids, c = idd;
	double best = INT_MAX;

	//cout << "Entrou recursiva " << endl;

	for (; it != pinteressestemp.end(); it++) {

		int b = (*it)->getVertex()->getInfo().getRelativeId();
		double dist1 = gmap.getWeight(a, b);
		if (dist1 == INT_MAX) {
			vector<RecyclingBin*>::iterator itc = pinteresses.begin();
			/*for (; itc != pinteresses.end(); itc++) {
			 if ((*it)->getId() == (*itc)->getId()) {
			 pinteresses.erase(itc);
			 break;
			 }
			 }*/
			pinteressestemp.erase(it);
			it--;
		} else {
			double dist2 = gmap.getWeight(b, c);
			if (dist2 == INT_MAX) {
				vector<RecyclingBin*>::iterator itc = pinteresses.begin();
				/*for (; itc != pinteresses.end(); itc++) {
				 if ((*it)->getId() == (*itc)->getId()) {
				 pinteresses.erase(itc);
				 break;
				 }
				 }*/
				pinteressestemp.erase(it);
				it--;
			} else {
				if (dist1 < best) {
					best = dist1;
					ite = it;
				}
			}
		}
	}
	if (ite != pinteressestemp.end()) {
		a = (*ite)->getVertex()->getInfo().getRelativeId();
		if (best != INT_MAX) {
			//cout << "Lixo do contentor " << (*ite)->getGarbage(color) << endl;
			//cout << "capacidade utilizada do camiao " << (camiao.getOcupiedCapacity()) << endl;
			//cout << "capacidade total do camiao " << (camiao.getUsableCapacity()) << endl;
			//cout << "capacidade disponivel do camiao " << (camiao.getUsableCapacity() - camiao.getOcupiedCapacity()) << endl;
			if ((*ite)->getGarbage(color)
					<= (camiao.getUsableCapacity() - camiao.getOcupiedCapacity())) {
				//cout << "Recolhendo Lixo" << endl;
				q.push((*ite));
				camiao.setOcupiedCapacity(
						camiao.getOcupiedCapacity()
								+ (*ite)->getGarbage(color));
				totalGarbage += (*ite)->getGarbage(color);
				(*ite)->setCapacity(color, 0);
				//cout << "New capacity " << (*ite)->getGarbage(color) << endl;
				vector<RecyclingBin*>::iterator itc = pinteresses.begin();
				for (; itc != pinteresses.end(); itc++) {
					if ((*ite)->getId() == (*itc)->getId()) {
						pinteresses.erase(itc);
						break;
					}
				}
				pinteressestemp.erase(ite);
				//cout << "Capacidade depois de lixo " << (camiao.getUsableCapacity() - camiao.getOcupiedCapacity()) << endl;
				//cout << pinteressestemp.size() << endl;

				if (pinteressestemp.size() == 0)
					finishedCollecting = true;
				if (pinteressestemp.size() > 1)
					best += limitedRunAux(a, c, q, pinteresses, pinteressestemp,
							camiao, totalGarbage, color, finishedCollecting);
			} else {
				pinteressestemp.erase(ite);
				if (pinteressestemp.size() > 1)
					best += limitedRunAux(a, c, q, pinteresses, pinteressestemp,
							camiao, totalGarbage, color, finishedCollecting);
			}
			return best;
		}
	}

	return 0;
}

string Company::limitedRun(int ids, int idd) {
	vector<Colors::Color> colors = { Colors::blue, Colors::yellow,
			Colors::green, Colors::red, Colors::black };
	bool finishedCollecting = false;

	if (gmap.getWeight(ids, idd) == INT_MAX) {
		return "Nao ha caminho da origem ao destino!";
	}

	gv->setVertexColor(ids, "red");
	gv->setVertexColor(idd, "red");
	gv->rearrange();

	if (trucks.size() == 0)
		return "Nao ha camioes!";

	for (unsigned int i = 0; i < trucks.size(); i++) {
		finishedCollecting = false;
		queue<RecyclingBin*> q;
		double totalGarbage = getTotalGarbage(colors.at(i));
		double garbage = 0;
		stringstream s;
		cout << "Camioes " << Colors::colors[colors.at(i)] << endl;
		vector<RecyclingBin*> pinteresses = getIntPoints(colors.at(i));
		//cout << "Numero de pontos de interesse: " << pinteresses.size() << endl;

		if (pinteresses.size() == 0) {
			stringstream s;
			s << "Nao ha lixo para recolher da cor "
					<< Colors::colors[colors.at(i)] << "!";
			return s.str();
		}

		for (unsigned int j = 0; j < trucks[colors.at(i)].size(); j++) {
			resetEdgeColors();
			int a = ids;
			s << "Camiao " << j << endl;
			vector<RecyclingBin*> pinteressescopy = pinteresses;

			if (pinteresses.size() > 0) {
				limitedRunAux(ids, idd, q, pinteresses, pinteressescopy,
						trucks[colors.at(i)].at(j), garbage, colors.at(i),
						finishedCollecting);

				while (q.size() > 0) {
					int b = q.front()->getVertex()->getInfo().getRelativeId();
					s << shortestPath(a, b) << "eco: " << b << endl;
					a = b;
					q.pop();
				}
				s << shortestPath(a, idd) << "Estacao de tratamento: " << idd
						<< endl;
				gv->rearrange();
			}

			if (finishedCollecting)
				break;

			cout << s.str() << endl;
			s.str("");
			cout << "Press any key to continue..." << endl;
			getch();
		}
		if (pinteresses.size() > 0)
			s << "Nao fui possivel recolher tudo" << endl;
		else if (pinteresses.size() == 0 && garbage != totalGarbage)
			s << "Nao fui possivel recolher tudo! Sobrou "
					<< (totalGarbage - garbage) << endl;

	}
	return "";
}

vector<RecyclingBin*> Company::getIntPoints(Colors::Color color) {
	vector<RecyclingBin*> temp;
	resetReBinsColors();

	for (unsigned int i = 0; i < rebins.size(); i++) {
		if (rebins.at(i).check(color).size() != 0) {
			gv->setVertexColor(
					rebins.at(i).getVertex()->getInfo().getRelativeId(),
					Colors::colors[color]);
			temp.push_back(&rebins.at(i));
		}
	}
	gv->rearrange();
	return temp;
}

void Company::resetEdgeColors() {
	gmap.resetEdgeColors(gv);
}

void Company::resetVertexColors() {
	gmap.resetVertexColors(gv);
}

void Company::resetReBinsColors() {
	vector<RecyclingBin>::iterator it = rebins.begin();

	for (; it != rebins.end(); it++) {
		gv->setVertexColor(it->getVertex()->getInfo().getRelativeId(),
		CYAN);
	}
}
