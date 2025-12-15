#ifndef STORAGE_H
#define STORAGE_H

#include "Graph.h"
#include <string>

class Storage {
public:
    void saveToFile(const Graph& graph);
    void loadFromFile(Graph& graph);
};
#endif