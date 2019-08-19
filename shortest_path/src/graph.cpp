#include "graph.hpp"

size_t Graph::NumOfVertices() const {
    return mVertNum;
}

const VertSet& Graph::vertices() const {
    return mVertices;
}

const EdgeSet& Graph::edges() const {
    return mEdges;
}
