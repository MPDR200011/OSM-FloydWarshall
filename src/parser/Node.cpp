#include "Node.h"

using namespace std;
using namespace rapidxml;

Node::Node(xml_node<>* nodeTag) : OSMBaseElement(nodeTag) {
    this->id = stoul(nodeTag->first_attribute("id")->value());
    this->latitude  = atof(nodeTag->first_attribute("lat")->value());
    this->longitude = atof(nodeTag->first_attribute("lon")->value());
}

unsigned long Node::getId() const {
    return id;
}

double Node::getLatitude() const {
    return latitude;
}

double Node::getLongitude() const {
    return longitude;
}
