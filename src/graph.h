#pragma once

#include <unordered_map>

class Vertex {
    double latitude;
    double longitude;
};

class Edge;

class Graph {
    std::unordered_map<unsigned long, Vertex*> vertexSet;
public:
    void addVertex(Vertex* v);
    
    void addEdge(unsigned long source, unsigned long dest);
    Vertex* getVertex(unsigned long id) const;
};