#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

enum class NodeCategory {
    Stop, Hospital, PetrolPump, PoliceStation
};

struct Node {
    string name;
    NodeCategory category;
    float trafficHeuristic;
};

struct Edge {
    string to;
    float weight;
    float heuristic;
    bool oneWay;
};

class Graph {
private:
    unordered_map<string, Node> nodes; // is ma kya huga k pehly name store huga or phr pori actual node hugi , yeh hamny apni asani k liye map bnaya ha ta k jab koi node dhondni ho to usky name sy easily dhond skein
    unordered_map<string, vector<Edge>> adjacency; // yeh jo ha wo actuall hamara adjancy list ha 
    bool modified = false;  // Track if graph was modified

public:
    // Core graph operations
    void addNode(const string& name, NodeCategory cat, float traffic = 0.0f); // default parameter float literal
    void addEdge(const string& from, const string& to, float weight, float heuristic, bool oneWay = false);
    void removeNode(const string& name);
    void removeEdge(const string& from, const string& to);
    void editNode(const string& oldName, const string& newName, NodeCategory newCat, float newTraffic);
    void editEdge(const string& from, const string& to, float newWeight, float newHeuristic, bool newOneWay);
    
    // Query operations
    void printMap() const;    // after () const -> mean constant member fun / read-only
    bool nodeExists(const string& name) const;
    bool edgeExists(const string& from, const string& to) const;
    
    // Accessors
    const unordered_map<string, Node>& getNodes() const { 
        return nodes; // & used so it return ref to the node not copy
    }
    const unordered_map<string, vector<Edge>>& getAdjacency() const { 
        return adjacency; 
    }
    bool isModified() const { 
        return modified; 
    }
    void setModified(bool status) { 
        modified = status; 
    }
    
    // Algorithm implementations
    void findShortestPath(const string& from, const string& to);
    void findSmartPath(const string& from, const string& to);
    void findNearestSpecialPlace(const string& from, NodeCategory category);
};

#endif
