#include <utility>
#include "Way.h"

using namespace std;
using namespace rapidxml;

Way::Way(xml_node<>* wayTag) : OSMBaseElement(wayTag) {
    xml_node<>* ndTag = wayTag->first_node("nd");
    while (ndTag != nullptr) {
        unsigned long currentID = stoul(ndTag->first_attribute("ref")->value());
        nodeRefArray.push_back(currentID);
        ndTag = ndTag->next_sibling("nd");
    }
}

const vector<unsigned long> &Way::getNodeRefArray() const {
    return nodeRefArray;
}
