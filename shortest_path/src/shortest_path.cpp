
#include "graph.hpp"
#include <vector>
#include <limits>
#include <unordered_map>


#include <iostream>

unsigned BellmaFordMethod(const Graph& g, const Vertex& start, std::unordered_map<Vertex, Vertex>& path)
{
    const int max_weight = std::numeric_limits<int>::max() - 100; // dirty fix for prevent overflow
    
    std::unordered_map<Vertex, int> distance;
    
    for (auto v : g.vertices()) {
        distance[v] = max_weight;
    }
    distance[start] = 0;

    for (auto v : g.vertices()) {
        for (Edge e : g.edges()) {
            if (distance[e.first()] + e.weight() < distance[e.second()]) {
                distance[e.second()] = distance[e.first()] + e.weight();
                path[e.second()] = e.first();
            }
        }
    }
    for (auto d : distance) {
        std::cout << "Vertex: " << d.first << " Weight: " <<  d.second << std::endl;
    }
    return 0;
}
