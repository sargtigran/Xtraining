#ifndef __SHORTEST_PATH__
#define __SHORTEST_PATH__

#include "graph.hpp"
#include <unordered_map>

unsigned BellmaFordMethod(const Graph& g, const Vertex& start, std::unordered_map<Vertex, Vertex>& path);

#endif // __SHORTEST_PATH__
