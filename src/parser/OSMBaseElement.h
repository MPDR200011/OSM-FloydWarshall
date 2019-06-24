#pragma once

#include <unordered_map>
#include "../rapidxml.hpp"
#include "Tag.h"

class OSMBaseElement {
protected:
    std::unordered_map<std::string, Tag> tags;

public:
    OSMBaseElement(rapidxml::xml_node<>* node);

    bool hasTag(const std::string& key) const;
    const std::string& getTagValue(const std::string& key) const;
};