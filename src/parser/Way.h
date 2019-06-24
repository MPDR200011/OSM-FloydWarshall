#pragma once

#include <vector>
#include <unordered_map>
#include "Tag.h"
#include "OSMBaseElement.h"
#include <iostream>

class Way : public OSMBaseElement {
    std::vector<unsigned long> nodeRefArray;

public:
    Way(rapidxml::xml_node<>* wayNode);

    const std::vector<unsigned long> &getNodeRefArray() const;
};