#include <fstream>
#include "graph.h"
#include "graph-viewer/graphviewer.h"
#include "parser/OSMParser.h"
#include "FloydWarshallAlgorithm.h"
#include "reader.h"

using namespace std;

GraphViewer gv(1000, 1000, false);

void drawGraph(Graph<Position>& graph, double minLon, double minLat) {
    int scale = 1000000;
    gv.createWindow(1000, 1000);

    for (Vertex<Position>* v: graph.getVertexSet()) {
        Position pos = v->getData();
        gv.addNode(v->getVertexID(), (pos.lon - minLon)*scale, -(pos.lat - minLat)*scale);
        gv.setVertexLabel(v->getVertexID(), to_string(v->getVertexID()));
    }

    for (Vertex<Position>* v: graph.getVertexSet()) {
        for (const Edge<Position>& e: v->getAdj()) {
            gv.addEdge(e.getEdgeID(), v->getVertexID(), e.getDest()->getVertexID(), EdgeType::DIRECTED);
        }
    }

    gv.rearrange();
}

int main() {
    ifstream inFile("corredoura.osm");

    OSMParser parser(&inFile);
    Graph<Position> graph = parser.generateGraph();

    FloydWarshallAlgorithm<Position> algo(&graph);
    algo.run();

    drawGraph(graph, parser.getMinLon(), parser.getMinLat());

    ofstream outfile("out.txt", std::ios::trunc);

    algo.save(outfile);

    outfile.close();
    Reader reader("out.txt");


    vector<unsigned long> path = reader.getPath(6360014905, 6360014917);

    for (unsigned long v: path) {
        gv.setVertexColor(v, RED);
    }

    return 0;
}