#include "file_handling.h"
#include<fstream>
#include<iostream>
#include <iomanip>
#include "algorithms.h"
using namespace std;

FileHandler::FileHandler()
{}
const Map& FileHandler::getMap() const
{
	return map;
}
void FileHandler::readMaps(const string& filename)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Cannot open map file: " + filename;
	}
	int N;
	file >> N;
	for (int i = 0; i < N; i++)
	{
		Intersection intersection;
		file >> intersection.intersectionId >> intersection.x >> intersection.y;
		map.intersections.push_back(intersection);
	}
	int M;
	file >> M;
	for (int i = 0; i < M; i++)
	{
		Road road;
		file >> road.firstId >> road.secondId >> road.length >> road.speed;
		map.roads.push_back(road);
	}
	file.close();
}
void FileHandler::readQueries(const string& filename)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Cannot open map file: " + filename;
	}
	int Q;
	file >> Q;
	for (int i = 0; i < Q; i++)
	{
		Query query;
		file >> query.sourceX >> query.sourceY >> query.destX >> query.destY >> query.maxDist;
		//query.maxDist /=  1000.0;
		queries.push_back(query);
	}
	file.close();
}
const vector<Query>& FileHandler::getQuery() const
{
	return queries;
}
Graph FileHandler::buildGraph()
{
	int vertices = map.intersections.size();
	Graph graph(vertices);
	for ( Road& road : map.roads)
	{
		graph.addEdge(road.firstId, road.secondId, road.length, road.speed);
		graph.addEdge(road.secondId, road.firstId, road.length, road.speed);
	}
	return graph;
}
void FileHandler:: writeOutput(const std::string& filename, const std::vector<RoutingResult>& results, int exec_time_without_io, int exec_time_with_io)
{
	ofstream outfile(filename);

	if (!outfile.is_open()) {
		cerr << "Cannot open output file: " << filename << endl;
		return;
	}

	for (const auto& res : results)
	{
		for (size_t i = 0; i < res.path_nodes.size(); ++i) {
			outfile << res.path_nodes[i];
			if (i + 1 < res.path_nodes.size()) outfile << " ";
		}
		outfile << "\n";

		outfile << fixed << setprecision(2) << res.shortest_time << " mins\n";
		outfile << fixed << setprecision(2) << res.total_length << " km\n";
		outfile << fixed << setprecision(2) << res.walking_distance << " km\n";
		outfile << fixed << setprecision(2) << res.vehicle_distance << " km\n";
		outfile << "\n";
	}

	outfile << exec_time_without_io << " ms\n\n";
	outfile << exec_time_with_io << " ms\n";

	outfile.close();
}
Graph::Graph(int vertices)
{
	numOfVertices = vertices;
	adj.resize(vertices);
}
void Graph::addEdge(int from, int to, double length, double speed)
{
	adj[from].push_back({ to, length, speed });
}
const vector<std::vector<Edge>>&Graph::getAdjList() const
{
	return adj;
}
const int Graph::getNumVertices() const
{
	return numOfVertices;
}