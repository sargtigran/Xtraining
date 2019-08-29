
#include "shortest_path.hpp"
#include "graph.hpp"

#include <iostream>

int main ()
{
    VertSet verts = { 1, 2, 3, 4 };
    EdgeSet edges = { {1, 2, 1}, {1, 3, 0}, {2, 3, 1}, {1, 4, 99}, {4, 2, -300} };

    Graph g(verts, edges);
    std::unordered_map<Vertex, Vertex> path;
    Vertex start(1);
    
    BellmaFordMethod(g, start, path);
    return 0;
}
