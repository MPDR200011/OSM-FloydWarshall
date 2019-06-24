#pragma once

#include "OSMBaseElement.h"

class Node : public OSMBaseElement {
    unsigned long id;
    double latitude;
    double longitude;
public:
    Node(rapidxml::xml_node<>* nodeTag);

    unsigned long getId() const;
    double getLatitude() const;
    double getLongitude() const;
};