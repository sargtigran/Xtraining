
#include "graph.hpp"
#include <vector>
#include <limits>
#include <unordered_map>


unsigned BellmaFordMethod(const Graph& g, const Vertex& start, std::vector<Vertex>& path)
{
    const int max_weight = std::numeric_limits<int>::max();
    
    std::unordered_map<Vertex, int> distance;
    
    unsigned n = g.NumOfVertices();
    path.resize(n);

    for (auto v : g.vertices()) {
        distance[v] = max_weight;
    }
    distance[start] = 0;

    for (auto v : g.vertices()) {
        for (Edge e : g.edges()) {
            if (distance[e.first()] + e.weight() < distance[e.second()]) {
                distance[e.second()] = distance[e.first()] + e.weight();
                //path[e.second()] = e.first();
            }
        }
    }
    return 0;
}
