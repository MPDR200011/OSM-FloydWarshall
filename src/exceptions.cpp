#include "exceptions.h"

#include <sstream>

using namespace std;

NonExistantNode::NonExistantNode(unsigned long id) {
    this->id = id;
}

const char* NonExistantNode::what() const {
    stringstream ss;
    ss << "Node with id " << id << " not found in table." << endl;
    return ss.str().c_str();
}