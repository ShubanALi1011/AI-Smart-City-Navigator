#ifndef USER_H
#define USER_H

#include "Graph.h"

class User {
public:
    void showUserMenu(Graph& cityGraph);
    
    // User operations
    void findShortestPath(Graph& cityGraph);
    void findSmartPath(Graph& cityGraph);
    void findNearestSpecialPlace(Graph& cityGraph);
    void viewMap(Graph& cityGraph);
};

#endif