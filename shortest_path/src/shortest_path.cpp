
#include "graph.hpp"


using Vertex = unsigned;

unsigned BellmaFordMethod(const Graph& g, const Vertex& start, std::vector<vertex>& path)
{
    const int max_weight = std::numeric_limits<int>::max();
    std::vector<Vertex> distances;
    path.resize(g.NumOfVertices());

    for (unsigned v = 0; v < g.NumOfVertices(); ++v) {
        distance[v] = max_weight;
    }
    distance[start] = 0;

    for (unsigned i = 0; i < g.NumOfVertices(); ++i) {
        for (Edge e : g.edges()) {
            if (distance[e.first] + e.weight() < distance[e.second]) {
                distance[e.second] = distance[e.first] + e.weight();
                path[e.second] = e.first;
            }
        }
    }
}
