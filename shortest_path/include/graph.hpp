#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <vector>

using Vertex = unsigned;
using VertSet = std::vector<Vertex>;
using WeightType = double;


struct Edge {
private:
    Vertex mFirst;
    Vertex mSecond;
    WeightType mWeight;

public:
    
    Edge() {}
    Edge (const Vertex& f, const Vertex& s, const WeightType w) 
        : mFirst(f)
        , mSecond(s)
        , mWeight(w)
    {}

    Vertex first() {
        return mFirst;
    }

    Vertex second() {
        return mSecond;
    }

    WeightType weight() {
        return mWeight;
    }
};


using EdgeSet = std::vector<Edge>;

class Graph 
{
private:
    size_t mVertNum;
    VertSet mVertices;
    EdgeSet mEdges;

public:
    Graph() : mVertNum(0) {}
    
    Graph(const VertSet& verts, const EdgeSet& edges)
        : mVertNum(verts.size())
        , mVertices(verts)
        , mEdges(edges)
    {
    }

    size_t NumOfVertices() const;
    
    const VertSet& vertices() const;

    const EdgeSet& edges() const;

};

#endif // __GRAPH_HPP__
