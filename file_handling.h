#pragma once
#include <vector>
#include <string>
struct Intersection
{
	int intersectionId;
	double x;
	double y;
};
struct Road
{
	int firstId;
	int secondId;
	double length;
	int speed;
};
struct Map
{
	std::vector<Intersection>intersections;
	std::vector<Road>roads;

};
struct Query
{
	double sourceX;
	double sourceY;
	double destX;
	double destY;
	double maxDist;  //meters
};
struct Edge
{
	int to;
	double length;
	double speed;
};
class Graph
{
	int numOfVertices;
	std::vector<std::vector<Edge>>adj;
public:
	Graph(int vertices);
	void addEdge(int from, int to, double length, double speed);
	const std::vector<std::vector<Edge>>& getAdjList()const;
	const int getNumVertices()const;

};
struct RoutingResult;

class FileHandler
{
	Map map;	
	std::string fileName;
	std::vector <Query> queries;
public:
	FileHandler();
	const Map& getMap() const;
	void readMaps(const std::string& filename);
	void readQueries(const std::string& filename);
	void writeOutput(const std::string& filename, const std::vector<RoutingResult>& results, int exec_time_without_io, int exec_time_with_io);
	const std::vector<Query>& getQuery()const;
	Graph buildGraph();
};


