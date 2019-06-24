#include "OSMBaseElement.h"

using namespace std;
using namespace rapidxml;

OSMBaseElement::OSMBaseElement(rapidxml::xml_node<>* node) {
    xml_node<>* tagTag = node->first_node("tag");
    while (tagTag != nullptr) {
        string key = tagTag->first_attribute("k")->value();
        string value = tagTag->first_attribute("v")->value();

        tags.insert(make_pair(key, Tag(key, value)));

        tagTag = tagTag->next_sibling("tag");
    }
}

bool OSMBaseElement::hasTag(const string& key) const {
    return tags.find(key) != tags.end();
}

const std::string& OSMBaseElement::getTagValue(const string& key) const {
    return tags.at(key).getValue();
}