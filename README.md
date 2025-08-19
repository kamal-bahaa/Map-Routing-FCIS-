# Map Routing Project

## Overview
This project implements a C++ map routing system to find the shortest travel time path from a source to a destination. It models roads as graphs (intersections as nodes with (x, y) coordinates, roads as bidirectional edges with length in km and speed in km/h). Travelers can walk (5 km/h) up to R meters to/from intersections and drive at road speeds. Dijkstra's algorithm optimizes for time, supporting large maps like San Francisco (174,956 intersections, 221,802 roads).

### Key Constraints
- Walking limited to Euclidean distance ≤ R meters from source/destination.
- Single vehicle ride (no transfers).
- Speed changes only at road transitions.
- Entry/exit time negligible.
- Focuses on constant speeds; bonus time-varying speeds not implemented.

## Features
- **Graph Construction**: Builds weighted undirected graph from map data.
- **Valid Intersection Search**: Identifies start/end intersections within R meters using Euclidean distance.
- **Shortest Path Calculation**: Uses Dijkstra's algorithm, prioritizing time (minutes) from all start nodes.
- **Output Details**: Provides path node IDs, total time (minutes), total distance (km), walking distance (km), and vehicle distance (km).
- **Performance Measurement**: Tracks execution time with/without I/O.
- **Scalability**: Handles small (<20 nodes), medium (Oldenburg: 6,105 nodes), and large (San Francisco: 174,956 nodes) cases (<3 min for 1,000 queries).

## Requirements
- C++ compiler (e.g., g++ with C++11+).
- Standard STL libraries (`<vector>`, `<queue>`, `<chrono>`).

## Installation
```
git clone https://github.com/kamal-bahaa/Map-Routing-FCIS-.git
cd Map-Routing-FCIS-
g++ -std=c++11 src/*.cpp -o map_routing
```

## Performance Analysis
- Graph Construction: O(|E|) where |E| is # roads.
- Intersection Search: O(|V|) per query, where |V| is # intersections.
- Dijkstra: O(|S| * |E'| log |V'|) per query, where |S| is # start nodes, |V'|, |E'| are explored nodes/edges.
- Path Reconstruction: O(|V'|).
- Meets large-case efficiency.


## License
- MIT License.

