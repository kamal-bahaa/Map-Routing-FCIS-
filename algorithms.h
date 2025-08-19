#pragma once
#include <vector>
#include <queue>
#include <chrono>
#include <limits>
#include <cmath>
#include "helper_functions.h"
#include "file_handling.h"
struct RoutingResult {
    std::vector<int> path_nodes;
    double shortest_time;
    double total_length;
    double walking_distance;
    double vehicle_distance;
    double exec_time;
};

RoutingResult Dykstra(Graph& graph, Map& map, Query& query);