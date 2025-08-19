#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <queue>
#include "file_handling.h"
#include "helper_functions.h"

using namespace std;

struct RoutingResult {
    vector<int> path_nodes;
    double shortest_time;
    double total_length;
    double walking_distance;
    double vehicle_distance;
    double exec_time;
};

const int WALK_SPEED = 5;

void findValidIntersections(Map& map, Query& query, vector<int>& start_nodes, vector<int>& end_nodes, vector<double>& start_walk_times) {
    double max_distance = query.maxDist / 1000.0;
    for (const auto& inter : map.intersections) {
        double dist_start = euclideanDistance(inter.x, query.sourceX, inter.y, query.sourceY);
        if (dist_start <= max_distance) {
            start_nodes.push_back(inter.intersectionId);
            start_walk_times.push_back((dist_start / WALK_SPEED) * 60.0);
        }
        double dist_end = euclideanDistance(inter.x, query.destX, inter.y, query.destY);
        if (dist_end <= max_distance) {
            end_nodes.push_back(inter.intersectionId);
        }
    }
}

RoutingResult dijkstra(Graph& graph, Map& map, Query& query) {
    RoutingResult result;
    vector<int> start_nodes, end_nodes;
    vector<double> start_walk_times;
    findValidIntersections(map, query, start_nodes, end_nodes, start_walk_times);

    vector<double> min_time(graph.getNumVertices(), numeric_limits<double>::max());
    vector<int> parent(graph.getNumVertices(), -1);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    for (size_t i = 0; i < start_nodes.size(); ++i) {
        min_time[start_nodes[i]] = start_walk_times[i];
        pq.push({ start_walk_times[i], start_nodes[i] });
    }

    double shortest_total_time = numeric_limits<double>::max();
    vector<int> best_path;
    double best_walking_distance = 0.0;
    double best_vehicle_distance = 0.0;
    int remaining_end_nodes = end_nodes.size();

    while (!pq.empty()) {
        double current_time = pq.top().first;
        int current_node = pq.top().second;
        pq.pop();

        if (current_time > min_time[current_node]) {
            continue;
        }

        for (int end_node : end_nodes) {
            if (current_node == end_node) {
                remaining_end_nodes--;
                double final_walk_distance = euclideanDistance(
                    map.intersections[current_node].x, query.destX,
                    map.intersections[current_node].y, query.destY
                );
                double total_time = current_time + (final_walk_distance / WALK_SPEED) * 60.0;

                if (total_time < shortest_total_time) {
                    shortest_total_time = total_time;
                    best_path.clear();
                    int temp = current_node;
                    while (temp != -1) {
                        best_path.push_back(temp);
                        temp = parent[temp];
                    }
                    reverse(best_path.begin(), best_path.end());

                    double initial_walk_distance = euclideanDistance(
                        map.intersections[best_path[0]].x, query.sourceX,
                        map.intersections[best_path[0]].y, query.sourceY
                    );

                    best_walking_distance = initial_walk_distance + final_walk_distance;
                    best_vehicle_distance = 0.0;
                    for (size_t i = 0; i < best_path.size() - 1; i++) {
                        for (const Edge& road : graph.getAdjList()[best_path[i]]) {
                            if (road.to == best_path[i + 1]) {
                                best_vehicle_distance += road.length;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (remaining_end_nodes == 0) {
            break;
        }

        for (const Edge& road : graph.getAdjList()[current_node]) {
            double travel_time = (road.length / road.speed) * 60.0;
            double new_time = current_time + travel_time;
            if (new_time < min_time[road.to]) {
                min_time[road.to] = new_time;
                parent[road.to] = current_node;
                pq.push({ new_time, road.to });
            }
        }
    }

    result.path_nodes = best_path;
    result.shortest_time = shortest_total_time;
    result.walking_distance = best_walking_distance;
    result.vehicle_distance = best_vehicle_distance;
    result.total_length = best_walking_distance + best_vehicle_distance;
    result.exec_time = 0.0;

    return result;
}