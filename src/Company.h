/*
 * Empresa.h
 *
 */

#ifndef SRC_COMPANY_H_
#define SRC_COMPANY_H_

#include <map>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <cstdlib>
#include <unordered_set>

#include "Color.h"
#include "Graph.h"
#include "Info.h"
#include "RecyclingBin.h"
#include "RecyclingCenter.h"
#include "Street.h"
#include "Truck.h"
#include "Vertex.h"
#include "Driver.h"

#define _USE_MATH_DEFINES

#include <cmath>
#include <algorithm>

namespace std {

class Company {
	//Mapa
	Graph<Info> gmap;
	GraphViewer *gv;
	void readMap();
	void createGraphViewer();

	//EcoCentros
	vector<RecyclingCenter> recenters;
	void createReCenter(Vertex<Info>* vertex);

	//EcoPontos
	vector<RecyclingBin> rebins;
	bool createRandomReBin(Vertex<Info> *vertex);
	void createReBin(Vertex<Info>* vertex);

	//Camioes
	vector<Truck> vtrucks;
	vector<Driver> drivers;
	map<Colors::Color, vector<Truck>> trucks;

	//Utilidades
	double unlimitedRunAux(int ids, int idd, queue<RecyclingBin*> &q,
			vector<RecyclingBin*> pinteresses);
	void resetEdgeColors();
	void resetReBinsColors();
	void resetVertexColors();
public:
	Company();
	virtual ~Company();
	//Map
	/**
	 * @brief
	 * @return
	 */
	const Graph<Info> getGMap() const;

	//RecyclingCenters
	/**
	 * @brief
	 * @return
	 */
	const vector<RecyclingCenter>& getReCenters() const;
	/**
	 * @brief
	 * @param recenter
	 */
	void addReCenter(const RecyclingCenter recenter);
	/**
	 * @brief
	 * @param idv
	 * @return
	 */
	bool createReCenter(int idv);
	/**
	 * @brief
	 * @return
	 */
	string getSCenters() const;
	/**
	 * @brief
	 * @return
	 */
	int eraseReCenters();

	//RecyclinBins
	/**
	 * @brief
	 * @return
	 */
	const vector<RecyclingBin>& getReBins() const;
	/**
	 * @brief
	 * @param rebin
	 */
	void addReBin(const RecyclingBin rebin);
	/**
	 * @brief
	 * @return
	 */
	int createRandomReBins();
	/**
	 * @brief
	 * @param idv
	 * @return
	 */
	bool createReBins(int idv);
	/**
	 * @brief
	 * @return
	 */
	int eraseReBins();
	/**
	 * @brief
	 * @param id
	 * @return
	 */
	bool removeReBin(int id);
	/**
	 * @brief
	 * @return
	 */
	string getSBins() const;
	/**
	 * @brief
	 * @return
	 */
	void generateGarbage();
	/**
	 * @brief
	 * @param cor
	 * @return
	 */
	double getTotalGarbage(Colors::Color cor);

	//Camioes
	/**
	 * @brief
	 * @return
	 */
	const map<Colors::Color, vector<Truck>>& getTrucks() const;
	/**
	 * @brief
	 * @param camiao
	 */
	void addTruck(Truck& camiao);
	/**
	 * @brief
	 * @return
	 */
	int createTrucks();
	/**
	 * @brief
	 * @return
	 */
	string getSTrucks() const;
	/**
	 *
	 * @return
	 */
	tuple<int,int> getNecessaryTrucks(Colors::Color color);
	/**
	 * @brief deletes all existing trucks
	 * @return number of trucks that got deleted
	 */
	int eraseTrucks();
	/**
	 *
	 * @param driver
	 */
	void addDriver(const Driver driver);
	/**
	 *
	 * @param n
	 */
	void addRandomDrivers(int n);
	/**
	 *
	 * @return
	 */
	string getSDrivers() const;
	/**
	 *
	 * @param name
	 * @return
	 */
	vector<Driver> getExactDriver(string name) const;
	/**
	 *
	 * @param name
	 * @return
	 */
	vector<Driver> getApproxDriver(string name) const;
	/**
	 *
	 * @return
	 */
	bool removeDriver(int id);
	/**
	 *
	 * @return
	 */
	int eraseDrivers();

	//Utilidades
	/**
	 * @brief
	 * @param ids
	 * @param idd
	 * @return
	 */
	string unlimitedRun(int ids, int idd);
	/**
	 * @brief
	 * @return
	 */
	vector<RecyclingBin*> getIntPoints();
	/**
	 * @brief
	 * @param ids
	 * @param idd
	 * @return
	 */
	string shortestPath(int ids, int idd);
	/**
	 * @brief shows how many trucks are needed to take all the garbage
	 */
	void dynamic();
	/**
	 * @brief
	 * @param idp
	 * @param idc
	 * @return
	 */
	string getUnlimitedRun(int idp, int idc);
	/**
	 *
	 * @param idp
	 * @param idc
	 * @return
	 */
	string getLimitedRun(int idp, int idc);
	/**
	 *
	 * @param ids
	 * @param idd
	 * @param q
	 * @param pinteresses
	 * @param pinteressestemp
	 * @param camiao
	 * @param totalGarbage
	 * @param color
	 * @return
	 */
	double limitedRunAux(int ids, int idd, queue<RecyclingBin*> &q,
			vector<RecyclingBin*> &pinteresses,
			vector<RecyclingBin*> pinteressestemp, Truck camiao,
			double &totalGarbage, Colors::Color color,
			bool &finishedCollecting);
	/**
	 *
	 * @param ids
	 * @param idd
	 * @return
	 */
	string limitedRun(int ids, int idd);
	/**
	 *
	 * @param color
	 * @return
	 */
	vector<RecyclingBin*> getIntPoints(Colors::Color color);
	/**
	 *
	 * @param name
	 * @return
	 */
	vector<int> getStreet(string name);
	/**
	 *
	 * @param toSearch
	 * @return
	 */
	vector<string> findAproxRoad(string toSearch);
};

} /* namespace std */

#endif /* SRC_COMPANY_H_ */
