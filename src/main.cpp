#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cmath>
#include <set>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "graph.h"
#include "graph-viewer/graphviewer.h"
#include "parser/OSMParser.h"

using namespace std;

void drawGraph(Graph<Position>& graph, double minLon, double minLat) {
    int scale = 1000000;
    GraphViewer gv(1000, 1000, false);
    gv.createWindow(1000, 1000);

    for (Vertex<Position>* v: graph.getVertexSet()) {
        Position pos = v->getData();
        gv.addNode(v->getVertexID(), (pos.lon - minLon)*scale, -(pos.lat - minLat)*scale);
    }

    for (Vertex<Position>* v: graph.getVertexSet()) {
        for (const Edge<Position>& e: v->getAdj()) {
            gv.addEdge(e.getEdgeID(), v->getVertexID(), e.getDest()->getVertexID(), EdgeType::DIRECTED);
        }
    }

    gv.rearrange();
}

int main() {

    ifstream inFile("ponte.osm");

    OSMParser parser(&inFile);
    Graph<Position> graph = parser.generateGraph();

    drawGraph(graph, parser.getMinLon(), parser.getMinLat());

    return 0;
}