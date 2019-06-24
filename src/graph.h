#pragma once

#include <set>
#include <unordered_map>
#include <vector>
#include <utility>

template <class T>
class Vertex;

template <class T>
class Edge {
    static unsigned long nextID;

    unsigned long edgeID;
    Vertex<T>* dest;
    double weight;
public:
    Edge(Vertex<T>* dest, double weight);

    unsigned long getEdgeID() const;

    Vertex<T> *getDest() const;

    double getWeight() const;
};

template <class T> unsigned long Edge<T>::nextID = 0;

template<class T>
Edge<T>::Edge(Vertex<T> *dest, double weight) {
    this->edgeID = nextID++;
    this->dest = dest;
    this->weight = weight;
}

template<class T>
unsigned long Edge<T>::getEdgeID() const {
    return edgeID;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
double Edge<T>::getWeight() const {
    return weight;
}

template <class T>
class Vertex {
    unsigned long vertexID;
    T data;
    std::vector<Edge<T>> adj;
public:
    Vertex(unsigned long vertexID, T data);

    const T& getData() const;
    void addEdge(Vertex<T>* dest, double weight);
    const std::vector<Edge<T>>& getAdj() const;

    unsigned long getVertexID() const;
};

template <class T>
Vertex<T>::Vertex(unsigned long id, T data) : data(data) {
    this->vertexID = id;
}

template <class T>
const T& Vertex<T>::getData() const {
    return data;
}

template<class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double weight) {
    adj.push_back(Edge<T>(dest, weight));
}

template<class T>
const std::vector<Edge<T>>& Vertex<T>::getAdj() const {
    return adj;
}

template<class T>
unsigned long Vertex<T>::getVertexID() const {
    return vertexID;
}


template <class T>
class Graph {
    std::unordered_map<unsigned long, Vertex<T>*> vertexMap;
    std::set<Vertex<T>*> vertexSet;
public:
    ~Graph();
    void addVertex(unsigned long id, T data);
    
    void addEdge(unsigned long source, unsigned long dest, double weight);
    Vertex<T>* getVertex(unsigned long id) const;

    const std::set<Vertex<T> *> &getVertexSet() const;
};

template <class T>
Graph<T>::~Graph() {
    for (Vertex<T>* v: vertexSet) {
        delete v;
    }
}

template<class T>
const std::set<Vertex<T> *> &Graph<T>::getVertexSet() const {
    return vertexSet;
}

template<class T>
void Graph<T>::addVertex(unsigned long id, T data) {
    Vertex<T>* vertex = new Vertex<T>(id, data);
    vertexMap.insert(std::make_pair(id, vertex));
    vertexSet.insert(vertex);
}

template<class T>
void Graph<T>::addEdge(unsigned long source, unsigned long dest, double weight) {
    Vertex<T>* src = getVertex(source);
    Vertex<T>* dst = getVertex(dest);

    if (src == nullptr || dst == nullptr) {
        return;
    }

    src->addEdge(dst, weight);
}

template<class T>
Vertex<T> *Graph<T>::getVertex(unsigned long id) const {
    try {
        return vertexMap.at(id);
    } catch (std::out_of_range& e) {
        return nullptr;
    }
} 