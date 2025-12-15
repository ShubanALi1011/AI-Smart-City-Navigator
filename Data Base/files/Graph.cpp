#include "Graph.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include<queue>

void Graph::addNode(const string& name, NodeCategory cat, float traffic) {
    if (nodeExists(name)) {
        system("cls");
        cout << "Location " << name << " already exists!\n";
        return;
    }
    nodes[name] = {name, cat, traffic};
    adjacency[name] = vector<Edge>(); // yeh intially jab node create hugi to uski empty list create kry ga
    modified = true;
    system("cls");
    cout << "Location '" << name << "' added successfully!\n";
    return;
}

void Graph::addEdge(const string& from, const string& to, float weight, float heuristic, bool oneWay) {
    if (!nodeExists(from) || !nodeExists(to)) {
        system("cls");
        cout << "One or both Locations don't exist!\n";
        return;
    }
    
    // Check if edge already exists
    if (edgeExists(from, to)) {
        system("cls");
        cout << "Road from '" << from << "' to '" << to << "' \nalready exists!\n";
        return;
    }
    
    adjacency[from].push_back({to, weight, heuristic, oneWay});
    
    if (!oneWay && !edgeExists(to, from)) {
        adjacency[to].push_back({from, weight, heuristic, false});
    }
    
    modified = true;
    system("cls");
    cout << "Road from '" << from << "' to '" << to << "' \n   added successfully!\n";
}

bool Graph::nodeExists(const string& name) const {
    return nodes.find(name) != nodes.end();
}

bool Graph::edgeExists(const string& from, const string& to) const {
    if (!nodeExists(from)) 
        return false;
    for (const auto& edge : adjacency.at(from)) { // matlab k from sy jitni b roads ja rhi hn usko check kro agr koi to wali sy match krti ha to exist krta huga
        if (edge.to == to) 
            return true;
    }
    return false;
}

void Graph::printMap() const {
    system("cls");
    cout << "---------------------------------------------------------\n";
    cout << "                  === CITY MAP ===\n";
    cout << "---------------------------------------------------------\n";
    cout << "Total Regions : " << nodes.size() << "\n";
    cout << "===================\n";
    
    for (const auto& [nodeName, node] : nodes) {
        cout << " " << nodeName << " [";
        switch(node.category) {
            case NodeCategory::Stop: cout << "Stop"; break;
            case NodeCategory::Hospital: cout << "Hospital"; break;
            case NodeCategory::PetrolPump: cout << "PetrolPump"; break;
            case NodeCategory::PoliceStation: cout << "PoliceStation"; break;
        }
        cout << "] - Traffic: " << node.trafficHeuristic << "\n";
        
        if (adjacency.at(nodeName).empty()) {
            cout << "    No connections\n";
        } 
        else {
            for (const auto& edge : adjacency.at(nodeName)) {
                cout << "     " << edge.to << " [Distance: " << edge.weight 
                     << ", Traffic: " << edge.heuristic << "]";
                if (edge.oneWay) 
                    cout << "  (One Way)";
                cout << "\n";
            }
        }
        cout << "---------------------------------------------------------\n";
    }
    cout<<"Press enter for exit.";
    cin.ignore(); 
    cin.get();
    system("cls");
}
void Graph::removeNode(const string& name) {
    if (!nodeExists(name)) {
        system("cls");
        cout << " Location '" << name << "' doesn't exist!\n";
        return;
    }
    
    // Remove all edges pointing to this node
    for (auto& [nodeName, edges] : adjacency) {
        for (int i = 0; i < edges.size(); ) {
            if (edges[i].to == name) {
                edges.erase(edges.begin() + i); // remove edge
            } 
            else {
                i++; // only move forward if not erased
            }
        }
    }
    // Remove the node
    nodes.erase(name);
    adjacency.erase(name);
    modified = true;
    system("cls");
    cout << " Location '" << name << "' removed \nsuccessfully!\n";
}

void Graph::removeEdge(const string& from, const string& to) {
    if (!edgeExists(from, to)) {
        system("cls");
        cout << " Location from '" << from << "' to '" << to << "' \ndoesn't exist!\n";
        return;
    }

    auto& edges = adjacency[from];  // reference to vector of edges

    // Use simple loop with index
    for (int i = 0; i < edges.size(); ) {
        if (edges[i].to == to) {
            edges.erase(edges.begin() + i); // remove edge
        } 
        else {
            i++; // move to next only if not erased
        }
    }

    modified = true;
    system("cls");
    cout << " Location from '" << from << "' to '" << to << "' \nremoved successfully!\n";
}
void Graph::editNode(const string& oldName, const string& newName, NodeCategory newCat, float newTraffic){
     if (!nodeExists(oldName)) {
        system("cls");
        cout << " Location '" << oldName << "' doesn't exist!\n";
        return;
    }

    // If name is changing, check for duplicate
    if (oldName != newName && nodeExists(newName)) {
        system("cls");
        cout << " Node '" << newName << "' already exists!\n";
        return;
    }

    nodes[oldName].category = newCat;
    nodes[oldName].trafficHeuristic = newTraffic;

     // If name is same, no rename needed
    if (oldName == newName) {
        modified = true;
        cout << " Location updated successfully!\n";
        return;
    }

    // Now rename the node
    Node updatedNode = nodes[oldName];
    updatedNode.name = newName;

    nodes.erase(oldName);
    nodes[newName] = updatedNode;

    // Move adjancey list to new name
    adjacency[newName] = adjacency[oldName];
    adjacency.erase(oldName);

    // update all edges pointing to this node
    for(auto &pair : adjacency){
        for(auto &edge : pair.second){
            if(edge.to == oldName){
                edge.to = newName;
            }
        }
    }

    modified = true;
    system("cls");
    cout << " Location '" << oldName << "' updated to '" << newName << "' \n\t\tsuccessfully!\n";
}

void Graph::editEdge(const string& from, const string& to, float newWeight, float newHeuristic, bool newOneWay){
     if (!edgeExists(from, to)){
         system("cls");
         cout << " Road from '" << from << "' to '" << to << "' doesn't exist!\n";
         return;
     }

     for (auto& edge : adjacency[from]){
         if(edge.to == to){
             edge.weight = newWeight;
             edge.heuristic = newHeuristic;
             edge.oneWay = newOneWay;
             break;
         }
     }

    // if now one way, update the reverse edge
    if(newOneWay){
        auto &revEdges = adjacency[to];
        revEdges.erase(remove_if(revEdges.begin(), revEdges.end(),[&](const Edge &e){ return e.to == from; }),revEdges.end());
    }
    else{
        if(!edgeExists(to,from)){
            adjacency[to].push_back({from, newWeight, newHeuristic, false});
        }
    }
    modified = true;
    system("cls");
    cout << " Road from '" << from << "' to '" << to << "' \nupdated successfully!\n";
       
}
void Graph::findShortestPath(const string& src, const string& dest) {

    if (!nodeExists(src) || !nodeExists(dest)) {
        system("cls");
        cout << "One or both Locations don't exist!\n";
        return;
    }

    // Distance map
    unordered_map<string, float> dist;
    for (const auto& node : nodes) {
        dist[node.first] = 1e9;
    }

    // Parent map (for path printing)
    unordered_map<string, string> parent;

    // Min-heap (distance, node)
    priority_queue<
        pair<float, string>,
        vector<pair<float, string>>,
        greater<pair<float, string>>
    > pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {

        auto top = pq.top();
        pq.pop();

        float currDistance = top.first;
        string currNode = top.second;

        if (currDistance > dist[currNode])
            continue;

        if (currNode == dest)
            break;

        for (const auto& edge : adjacency[currNode]) {

            float newDistance = currDistance + edge.weight;

            if (newDistance < dist[edge.to]) {
                dist[edge.to] = newDistance;
                parent[edge.to] = currNode;
                pq.push({newDistance, edge.to});
            }
        }
    }

    // If destination unreachable
    if (dist[dest] == 1e9) {
        cout << "No path found!\n";
        return;
    }

    // 🔹 PRINT PATH
    vector<string> path;
    string current = dest;

    while (current != src) {
        path.push_back(current);
        current = parent[current];
    }
    path.push_back(src);

    reverse(path.begin(), path.end());

    cout << "\nShortest Path:\n";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1)
            cout << " -> ";
    }

    cout << "\nTotal Distance: " << dist[dest] << " km "<<endl;
    cout<<"------------------------------------------\n";
    cout<<endl<<"Press a key for exit.";
    cin.get();
    system("cls");
}

void Graph::findSmartPath(const string& from, const string& to) {

    if (!nodeExists(from) || !nodeExists(to)) {
        cout << " One or both Locations don't exist!\n";
        return;
    }

    unordered_map<string, float> gCost;   // actual cost from source
    unordered_map<string, string> parent; // for path

    for (const auto& n : nodes) {
        gCost[n.first] = 1e9;
    }

    // min-heap → (fCost, node)
    priority_queue<
        pair<float, string>,
        vector<pair<float, string>>,
        greater<pair<float, string>>
    > pq;

    gCost[from] = 0;
    pq.push({nodes[from].trafficHeuristic, from}); // f = g + h

    while (!pq.empty()) {

        float currFCost = pq.top().first;
        string currNode = pq.top().second;
        pq.pop();

        if (currNode == to)
            break;

        for (const auto& edge : adjacency[currNode]) {

            // g(n) = distance + edge weight
            float newG = gCost[currNode] + edge.weight;

            if (newG < gCost[edge.to]) {

                gCost[edge.to] = newG;
                parent[edge.to] = currNode;

                // h(n) = node heuristic + edge heuristic
                float h = nodes[edge.to].trafficHeuristic + edge.heuristic;

                float f = newG + h;
                pq.push({f, edge.to});
            }
        }
    }

    // no path
    if (gCost[to] == 1e9) {
        cout << " No smart path found!\n";
        return;
    }

    // print path
    vector<string> path;
    string cur = to;

    while (cur != from) {
        path.push_back(cur);
        cur = parent[cur];
    }
    path.push_back(from);

    reverse(path.begin(), path.end());
    cout<<"------------------------------------------------\n";
    cout << " Smart Path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1)
            cout << " -> ";
    }

    cout << "\n Total Distance: " << gCost[to] << endl;
    cout<<"------------------------------------------------\n";
    cout<<endl<<"Press a key for exit.";
    cin.get();
    system("cls");
}
void Graph::findNearestSpecialPlace(const string& from, NodeCategory category) {
    if (!nodeExists(from)) {
        system("cls");
        cout << " Starting Location doesn't exist!\n";
        return;
    }
    /// BFS for finding nearest special place
    unordered_map<string, bool> visited;
    queue<string> q;
    unordered_map<string, string> parent;    // To rebuild path

    q.push(from);
    visited[from] = true;
    parent[from] = "";

    string foundNode = "";

    while(!q.empty()){
        string current = q.front();
        q.pop();

        if(nodes[current].category == category && current != from){
            foundNode = current;
            break;
        }

        // Explore neighbors
        for(const auto& edge : adjacency[current]){
            if(!visited[edge.to]){
                visited[edge.to] = true;
                parent[edge.to] = current;
                q.push(edge.to);
            }
        }
    }


    if(foundNode == ""){
        cout << " No special place of this type found near " << from << "!\n";
        return;
    }

    // Rebuild path
    vector<string> path;
    string temp = foundNode;
    
    while(temp != ""){
        path.push_back(temp);
        temp = parent[temp];
    }

    reverse(path.begin(), path.end());  // Reverse to get from -> to

    // count edge distance 
    int edgeDistance = path.size() - 1;

    // calculate weight distance
    float weightDistance = 0.0f;

    for(int i = 0; i < edgeDistance; i++){
        string u = path[i];
        string v = path[i+1];

        // find weight of edge u -> v
        for(const auto& edge : adjacency[u]){
            if(edge.to == v){
                weightDistance += edge.weight;
                break;
            }
        }
    }

    system("cls");
    cout << "\n======== Nearest ";
    switch(category){
        case NodeCategory::Stop: cout << "Stop"; break;
        case NodeCategory::Hospital: cout << "Hospital"; break;
        case NodeCategory::PetrolPump: cout << "Petrol Pump"; break;
        case NodeCategory::PoliceStation: cout << "Police Station"; break;
    }
    cout<<"=========\n";
    switch(category){
        case NodeCategory::Stop: cout << "Stop"; break;
        case NodeCategory::Hospital: cout << "Hospital"; break;
        case NodeCategory::PetrolPump: cout << "Petrol Pump"; break;
        case NodeCategory::PoliceStation: cout << "Police Station"; break;
    }
    cout << " Found at : " << foundNode << "\n";
    cout << "Distance : " << weightDistance << " km\n";

    cout << "Path: ";
    for(int i = 0; i < path.size(); i++){
        cout << " " << path[i];
        if(i != path.size() - 1){
            cout << " -> ";
        }
    }
    cout<<endl<<"----------------------------------------------------------\n";
    cout<<"Press any key for exit.";
    cin.ignore();
    cin.get();
    system("cls");
}