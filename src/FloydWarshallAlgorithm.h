#pragma once

#include <unordered_map>
#include <vector>
#include <utility>
#include <limits>
#include <iostream>
#include "graph.h"

#define INF std::numeric_limits<double>::max()

template <class T>
class FloydWarshallAlgorithm {
    bool wasRun;
    Graph<T>* graph;
    double** distMatrix;
    Vertex<T>*** nextMatrix;
    std::unordered_map<Vertex<T>*, size_t> indexMap;
public:
    FloydWarshallAlgorithm(Graph<T>* graph);
    ~FloydWarshallAlgorithm();

    void run();

    std::vector<Vertex<T>*> getPath(unsigned long srcID, unsigned long destID) const;
};

template<class T>
FloydWarshallAlgorithm<T>::FloydWarshallAlgorithm(Graph<T>* graph) {
    this->wasRun = false;
    this->graph = graph;

    size_t numVertices = graph->getVertexSet().size();
    
    this->distMatrix = new double*[numVertices];
    this->nextMatrix = new Vertex<T>**[numVertices];
    for(size_t i = 0;i < numVertices; i++){
        distMatrix[i] = new double[numVertices];
        nextMatrix[i] = new Vertex<T>*[numVertices];
    }

    this->indexMap = std::unordered_map<Vertex<T>*, size_t>(numVertices);
    size_t currentPointer = 0;
    for (Vertex<T>* v: graph->getVertexSet()) {
        indexMap.insert(std::make_pair(v, currentPointer));
        currentPointer++;
    }
}

template<class T>
FloydWarshallAlgorithm<T>::~FloydWarshallAlgorithm() {
    size_t numVertices = graph->getVertexSet().size();
    for(size_t i = 0; i < numVertices; i++){
        delete [] distMatrix[i];
        delete [] nextMatrix[i];
    }
    delete [] distMatrix;
    delete [] nextMatrix;
}

template<class T>
void FloydWarshallAlgorithm<T>::run() {
    if (wasRun) {
        return;
    }

    size_t numVertices = graph->getVertexSet().size();
    for(size_t i = 0; i < numVertices; i++){
        for(size_t j = 0; j < numVertices; j++){
            distMatrix[i][j] = INF;
            nextMatrix[i][j] = nullptr;
        }
    }

    for (Vertex<T>* v :graph->getVertexSet()) {
        size_t vertexIndex = indexMap.at(v);
        distMatrix[vertexIndex][vertexIndex] = 0;
        nextMatrix[vertexIndex][vertexIndex] = v;
        for (const Edge<T>& e: v->getAdj()) {
            size_t destIndex = indexMap.at(e.getDest());
            distMatrix[vertexIndex][destIndex] = e.getWeight();
            nextMatrix[vertexIndex][destIndex] = e.getDest();
        }
    }

    for(size_t k = 0; k < numVertices; k++){
        for(size_t i = 0; i < numVertices; i++){
            for(size_t j = 0; j < numVertices; j++){
                double added = distMatrix[i][k] + distMatrix[k][j];
                if (distMatrix[i][j] > added) {
                    distMatrix[i][j] = added;
                    nextMatrix[i][j] = nextMatrix[i][k];
                }
            }
        }
    }

    wasRun = true;
}

template<class T>
std::vector<Vertex<T>*> FloydWarshallAlgorithm<T>::getPath(unsigned long srcID, unsigned long destID) const {
    std::vector<Vertex<T>*> res;
    Vertex<T>* src = graph->getVertex(srcID);
    Vertex<T>* dest = graph->getVertex(destID);

    if (src == nullptr || dest == nullptr) {
        return res;
    }

    size_t srcIndex = indexMap.at(src);
    size_t destIndex = indexMap.at(dest);

    if (nextMatrix[srcIndex][destIndex] == nullptr) {
        return res;
    }

    res.push_back(src);
    while (src != dest) {
        src = nextMatrix[srcIndex][destIndex];
        srcIndex = indexMap.at(src);
        res.push_back(src);
    }

    return res;
}