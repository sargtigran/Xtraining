#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <unordered_set>
#include <set>

using Vertex = unsigned;
using VertSet = std::unordered_set<Vertex>;


struct Edge {
private:
    Vertex mFirst;
    Vertex mSecond;
    int mWeight;

public:
    
    Edge() {}
    Edge (const Vertex& f, const Vertex& s, const size_t w) 
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

    Vertex weight() {
        return mWeight;
    }
};


using EdgeSet = std::set<Edge>;

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
