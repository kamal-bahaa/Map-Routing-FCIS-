#include <iostream>
#include <chrono>
#include "file_handling.h"
#include "algorithms.h"

using namespace std;


int main() {
    using namespace std::chrono;

    auto start_with_io = high_resolution_clock::now();

    FileHandler file;
    file.readMaps("SFMap.txt");
    Map map = file.getMap();

    Graph graph = file.buildGraph();

    file.readQueries("SFQueries.txt");
    vector<Query> queries = file.getQuery();

    vector<RoutingResult> results;

    auto start_without_io = high_resolution_clock::now();

    for (Query& q : queries) {
        RoutingResult result = Dykstra(graph, map, q);
        results.push_back(result);
    }

    auto end_without_io = high_resolution_clock::now();

    int exec_time_without_io = duration_cast<milliseconds>(end_without_io - start_without_io).count();


    auto end_with_io = high_resolution_clock::now();

    int exec_time_with_io = duration_cast<milliseconds>(end_with_io - start_with_io).count();

   file.writeOutput("OLOutput.txt", results, exec_time_without_io, exec_time_with_io);

    cout << "Execution time without IO: " << exec_time_without_io << " ms\n";
    cout << "Execution time with IO: " << exec_time_with_io << " ms\n";

    return 0;
}
