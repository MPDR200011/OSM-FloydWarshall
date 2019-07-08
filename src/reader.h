#pragma once

#include <cstddef>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include "graph.h"

class Reader {
    std::ifstream file;
    std::size_t numVertices;
    std::size_t distMatrixBase;
    std::size_t nextMatrixBase;

    std::unordered_map<unsigned long, size_t> indexMap;

public:
    Reader(std::string fileName);

    std::vector<unsigned long> getPath(unsigned long src, unsigned long dest);

private:
    unsigned long getNext(unsigned long src, unsigned long dest);
};