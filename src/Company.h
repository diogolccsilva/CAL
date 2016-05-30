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
	string unlimitedRun(int ids, int idd);
	double unlimitedRunAux(int ids, int idd, queue<RecyclingBin*> &q,
			vector<RecyclingBin*> pinteresses);

	string limitedRun(int ids, int idd);
	double limitedRunAux(int ids, int idd, queue<RecyclingBin*> &q,
				vector<RecyclingBin*> &pinteresses,
				vector<RecyclingBin*> pinteressestemp, Truck camiao,
				double &totalGarbage, Colors::Color color, bool &finishedCollecting);

	void resetEdgeColors();
	void resetReBinsColors();
	void resetVertexColors();
public:

	/**
	 * Default constructor.
	 */
	Company();

	/**
	 * Default destructor.
	 */
	virtual ~Company();

	//Map
	/**
	 *
	 * @return The graph representing the map.
	 */
	const Graph<Info> getGMap() const;

	//RecyclingCenters
	/**
	 *
	 * @return The vector of recycling centers.
	 */
	const vector<RecyclingCenter>& getReCenters() const;

	/**
	 * @brief Adds a recycling center to the map.
	 * @param recenter Recycling center to be added.
	 */
	void addReCenter(const RecyclingCenter recenter);

	/**
	 * @brief Creats a recycling center in the node with the specified ID.
	 * @param idv ID of the node.
	 * @return True if the recycling center was added successfully or false otherwise.
	 */
	bool createReCenter(int idv);

	/**
	 *
	 * @return A string with the information of all recycling centers.
	 */
	string getSCenters() const;

	/**
	 * @brief Removes all existing recycling centers.
	 * @return The number of recycling centers removed.
	 */
	int eraseReCenters();

	//RecyclinBins
	/**
	 *
	 * @return The vector of recycling bins.
	 */
	const vector<RecyclingBin>& getReBins() const;

	/**
	 * @brief Adds a recycling bin to the vector.
	 * @param rebin Recycling bin to be added.
	 */
	void addReBin(const RecyclingBin rebin);

	/**
	 * @brief Creates a random amount of recycling bins.
	 * @return The amount of recycling bins created.
	 */
	int createRandomReBins();

	/**
	 * @brief Creates a recycling bin in the node with the specified ID.
	 * @param idv ID of the node.
	 * @return True if the recycling bin was successfully added or false otherwise.
	 */
	bool createReBins(int idv);

	/**
	 * @brief Removes all existing recycling bins.
	 * @return The number of recycling bins removed.
	 */
	int eraseReBins();

	/**
	 * @brief Removes the recycling bin positioned on the node with the specified ID.
	 * @param id ID of the node.
	 * @return True if the recycling bin was successfully removed or false otherwise.
	 */
	bool removeReBin(int id);

	/**
	 *
	 * @return A string with all the information of the recycling bins.
	 */
	string getSBins() const;

	/**
	 * @brief Creates random amounts of garbage in each recycling bin.
	 */
	void generateGarbage();

	/**
	 *
	 * @param color Color of the garbage.
	 * @return The total garbage to be collected of the specified color.
	 */
	double getTotalGarbage(Colors::Color color);

	//Camioes
	/**
	 *
	 * @return The map of the existing trucks.
	 */
	const map<Colors::Color, vector<Truck>>& getTrucks() const;

	/**
	 * @brief Adds a truck to the map and the vector of trucks.
	 * @param truck Truck to be added.
	 */
	void addTruck(Truck& truck);

	/**
	 * @brief Creates truck for the garbage collection.
	 * @return The number of trucks created.
	 */
	int createTrucks();

	/**
	 *
	 * @return A string with all the information of the trucks.
	 */
	string getSTrucks() const;

	/**
	 *
	 * @return
	 */
	tuple<int,int> getNecessaryTrucks(Colors::Color color);

	/**
	 *
	 * @brief Deletes all existing trucks.
	 * @return The number of trucks that got deleted.
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
	 *
	 * @return A vector with the recycling bins that need to be collected.
	 */
	vector<RecyclingBin*> getIntPoints(); //TODO: refractor

	/**
	 *
	 * @param color Color representing the type of garbage.
	 * @return A vector with the recycling bins with the specified color that need to be collected.
	 */
	vector<RecyclingBin*> getIntPoints(Colors::Color color);

	/**
	 * @brief Calculates the shortest path between two points.
	 * @param ids ID of the start vertex.
	 * @param idd ID of the end vertex.
	 * @return String with the path.
	 */
	string shortestPath(int ids, int idd);

	/**
	 * @brief Shows how many trucks are needed to collect all the garbage.
	 */
	void dynamic();

	/**
	 * @brief Calculates the route assuming there's only one truck with unlimited capacity.
	 * @param idp ID of the start vertex.
	 * @param idc ID of the end vertex.
	 * @return String with the path.
	 */
	string getUnlimitedRun(int idp, int idc);

	/**
	 * @brief Calculates the route taking into account the different trucks and their different capacities.
	 * @param idp ID of the start vertex.
	 * @param idc ID of the end vertex.
	 * @return String with the path.
	 */
	string getLimitedRun(int idp, int idc);
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
