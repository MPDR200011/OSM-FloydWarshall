#pragma once

#include <istream>
#include <vector>
#include "Node.h"
#include "Way.h"
#include "../graph.h"

struct Position {
    double lat;
    double lon;
    
    Position(double lat, double lon) : lat(lat), lon(lon) {}
};

class OSMParser {
    std::vector<Node> nodes;
    std::vector<Way> ways;
    double minLat;
    double minLon;

public:
    OSMParser(std::istream* XMLStream);

    Graph<Position> generateGraph() const;

    double getMinLat() const;
    double getMinLon() const;

private:
    void fetchNodes(rapidxml::xml_node<>* rootTag);
    void fetchWays(rapidxml::xml_node<>* rootTag);

};