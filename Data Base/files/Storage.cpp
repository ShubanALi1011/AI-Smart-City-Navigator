#include "Storage.h"
#include <fstream>
#include <iostream>
using namespace std;

void Storage::saveToFile(const Graph& graph) {
    ofstream file("Data Base/graph.dat", ios::binary | ios::trunc);
    if (!file.is_open())
        return;

    const auto& nodes = graph.getNodes();
    const auto& adjacency = graph.getAdjacency();

    // 1. Save number of nodes
    int nodeCount = nodes.size();
    file.write((char*)&nodeCount, sizeof(int));

    // 2. Save all nodes
    for (const auto& [name, node] : nodes) {
        int nameLen = name.size();
        file.write((char*)&nameLen, sizeof(int));
        file.write(name.c_str(), nameLen);
        file.write((char*)&node.category, sizeof(node.category));
        file.write((char*)&node.trafficHeuristic, sizeof(node.trafficHeuristic));
    }

    // 3. Save adjacency list count
    int adjCount = adjacency.size();
    file.write((char*)&adjCount, sizeof(int));

    // 4. Save adjacency list
    for (const auto& [from, edges] : adjacency) {
        int fromLen = from.size();
        file.write((char*)&fromLen, sizeof(int));
        file.write(from.c_str(), fromLen);

        int edgeCount = edges.size();
        file.write((char*)&edgeCount, sizeof(int));

        for (const auto& e : edges) {
            int toLen = e.to.size();
            file.write((char*)&toLen, sizeof(int));
            file.write(e.to.c_str(), toLen);
            file.write((char*)&e.weight, sizeof(e.weight));
            file.write((char*)&e.heuristic, sizeof(e.heuristic));
            file.write((char*)&e.oneWay, sizeof(e.oneWay));
        }
    }

    file.close();
}

void Storage::loadFromFile(Graph& graph) {
    ifstream file("Data Base/graph.dat", ios::binary);
    if (!file.is_open())
        return;

    // 1. Read number of nodes
    int nodeCount = 0;
    file.read((char*)&nodeCount, sizeof(int));
    if (nodeCount <= 0)
        return;

    // 2. Load nodes
    for (int i = 0; i < nodeCount; i++) {
        int nameLen = 0;
        file.read((char*)&nameLen, sizeof(int));

        string name(nameLen, '\0');
        file.read(&name[0], nameLen);

        NodeCategory category;
        float traffic;
        file.read((char*)&category, sizeof(category));
        file.read((char*)&traffic, sizeof(traffic));

        graph.addNode(name, category, traffic);
    }

    // 3. Read adjacency list count
    int adjCount = 0;
    file.read((char*)&adjCount, sizeof(int));

    // 4. Load adjacency data
    for (int k = 0; k < adjCount; k++) {
        int fromLen = 0;
        file.read((char*)&fromLen, sizeof(int));

        string from(fromLen, '\0');
        file.read(&from[0], fromLen);

        int edgeCount = 0;
        file.read((char*)&edgeCount, sizeof(int));

        for (int i = 0; i < edgeCount; i++) {
            int toLen = 0;
            file.read((char*)&toLen, sizeof(int));

            string to(toLen, '\0');
            file.read(&to[0], toLen);

            float weight, heuristic;
            bool oneWay;

            file.read((char*)&weight, sizeof(float));
            file.read((char*)&heuristic, sizeof(float));
            file.read((char*)&oneWay, sizeof(bool));

            graph.addEdge(from, to, weight, heuristic, oneWay);
        }
    }

    file.close();
    graph.setModified(false);
}
