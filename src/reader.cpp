#include "reader.h"
#include "exceptions.h"
#include <utility>
#include <iostream>

using namespace std;


Reader::Reader(string fileName) {
    this->file.open(fileName);

    file.seekg(0, file.beg);
    file.read((char*) &numVertices, sizeof(size_t));
    file.read((char*) &distMatrixBase, sizeof(size_t));
    file.read((char*) &nextMatrixBase, sizeof(size_t));

    for (size_t i = 0; i < numVertices; i++) {
        unsigned long id;
        size_t index;

        file.read((char*) &id, sizeof(unsigned long));
        cout << id << endl;
        file.read((char*) &index, sizeof(size_t));

        indexMap.insert(make_pair(id, index));
    }
}

std::vector<unsigned long> Reader::getPath(unsigned long src, unsigned long dest) {
    vector<unsigned long> path;

    if (getNext(src, dest) == 0) {
        return path;
    }

    path.push_back(src);
    while (src != dest) {
        src = getNext(src,dest);
        path.push_back(src);
    }

    return path;
}

unsigned long Reader::getNext(unsigned long src, unsigned long dest) {
    unsigned long next;

    size_t srcIndex;
    size_t destIndex;

    try {
        srcIndex = indexMap.at(src);
    } catch (out_of_range &e) {
        throw NonExistantNode(srcIndex);
    }
    try {
        destIndex = indexMap.at(dest);
    } catch (out_of_range &e) {
        throw NonExistantNode(destIndex);
    }

    file.seekg(nextMatrixBase + (srcIndex*numVertices + destIndex) * sizeof(unsigned long), file.beg);
    file.read((char*) &next, sizeof(unsigned long));

    return next;
}