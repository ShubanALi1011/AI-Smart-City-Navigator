#ifndef ADMIN_H
#define ADMIN_H

#include "Graph.h"
#include "storage.h"
#include <string>

using namespace std;

class Admin {
private:
    string username;
    string password;
    Storage& storage;  // Reference to storage
    
    bool authenticate();
    void showAdminMenu(Graph& cityGraph);

public:
    Admin(Storage& storageManager) : storage(storageManager) {}
    
    void login(Graph& cityGraph);
    
    // Admin operations
    void addNode(Graph& cityGraph);
    void addEdge(Graph& cityGraph);
    void editNode(Graph& cityGraph);
    void editEdge(Graph& cityGraph);
    void removeNode(Graph& cityGraph);
    void removeEdge(Graph& cityGraph);
    void viewMap(Graph& cityGraph);
};

#endif