#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace std;

int main() {

    rapidxml::xml_document<> doc;

    ifstream inFile("corredoura.osm");

    stringstream ss;
    ss << inFile.rdbuf();
    char * text = new char[ss.str().length() + 1];
    strcpy(text, ss.str().c_str());

    doc.parse<0>(text);
    
    rapidxml::xml_node<>* first_node = doc.first_node();

    if (strcmp(first_node->name(), "osm") != 0) {
        exit(1);
    }

    rapidxml::xml_node<>* child_node = first_node->first_node("node");
    while (strcmp(child_node->name(), "node") == 0) {
        cout << child_node->first_attribute("id")->value() << endl;
        child_node = child_node->next_sibling();
    }

    return 0;
}