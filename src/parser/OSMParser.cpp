#include <cmath>
#include <sstream>
#include <iostream>
#include <cstring>
#include "OSMParser.h"

using namespace std;
using namespace rapidxml;

OSMParser::OSMParser(istream* XMLStream) {
    stringstream ss;
    ss << XMLStream->rdbuf();
    char * text = new char[ss.str().length() + 1];
    strcpy(text, ss.str().c_str());

    rapidxml::xml_document<> doc;
    doc.parse<0>(text);

    rapidxml::xml_node<>* root_node = doc.first_node("osm");
    if (root_node == nullptr) {
        cerr << "nullptr" << endl;
        exit(1);
    }

    rapidxml::xml_node<>* bounds_node = root_node->first_node("bounds");
    this->minLat = atof(bounds_node->first_attribute("minlat")->value());
    this->minLon = atof(bounds_node->first_attribute("minlon")->value());

    fetchNodes(root_node);
    fetchWays(root_node);

}

void OSMParser::fetchNodes(rapidxml::xml_node<>* rootTag) {
    rapidxml::xml_node<>* nodeTag = rootTag->first_node("node");
    while (nodeTag != nullptr) {
        nodes.push_back(Node(nodeTag));
        nodeTag = nodeTag->next_sibling("node");
    }
}

void OSMParser::fetchWays(rapidxml::xml_node<>* rootTag) {
    rapidxml::xml_node<>* wayTag = rootTag->first_node("way");
    while (wayTag != nullptr) {
        ways.push_back(Way(wayTag));
        wayTag = wayTag->next_sibling("way");
    }
}

double toRadians(double degrees) {
    return degrees * M_PI / 180;
}

double distance(Position p1, Position p2) {
    double R = 6371e3; // metres
    double phi1 = toRadians(p1.lat);
    double phi2 = toRadians(p2.lat);
    double dPhi = toRadians(p2.lat-p1.lat);
    double dGamma = toRadians(p2.lon-p1.lon);

    double a = sin(dPhi/2) * sin(dPhi/2) +
        cos(phi1) * cos(phi2) *
        sin(dGamma/2) * sin(dGamma/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return R * c;
}

Graph<Position> OSMParser::generateGraph() const {
    Graph<Position> graph;

    for (const Node& n: nodes) {
        graph.addVertex(n.getId(), Position(n.getLatitude(), n.getLongitude()));
    }

    for (const Way& way: ways) {
        if (way.getNodeRefArray().size() == 0) {
            continue;
        }
        auto it = way.getNodeRefArray().begin();
        unsigned long prevID = (*it);
        it++;
        for (;it != way.getNodeRefArray().end(); it++) {
            Vertex<Position>* src = graph.getVertex(prevID);
            Vertex<Position>* dest = graph.getVertex(*it);

            graph.addEdge(prevID, *it, distance(src->getData(), dest->getData()));

            bool oneway = false;
            oneway |= way.hasTag("oneway") && way.getTagValue("oneway") == "yes";
            oneway |= way.hasTag("junction") && way.getTagValue("junction") == "roundabout";

            if (!oneway) {
                graph.addEdge(*it, prevID, distance(src->getData(), dest->getData()));
            }

            prevID = *it;
        }
    }

    return graph;
}

double OSMParser::getMinLat() const {
    return minLat;
}

double OSMParser::getMinLon() const {
    return minLon;
}

