#include "Admin.h"
#include <iostream>
#include <limits>

bool Admin::authenticate() {
    cout << "\n=====================================\n";
    cout << "       Administrator Login";
    cout << "\n=====================================\n";
    
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    return (username == "shuban" && password == "alien") ||
           (username == "taimoor" && password == "alien1") ||
           (username == "huzaifa" && password == "alien2");
}

void Admin::login(Graph& cityGraph) {
    if (!authenticate()) {
        system("cls");
        cout << "    Invalid credentials! Access denied.\n\n";
        return;
    }
    system("cls");
    cout << "Login successful! Welcome, " << username << "!\n";
    showAdminMenu(cityGraph);
}

void Admin::showAdminMenu(Graph& cityGraph) {
    int choice = 0;
    do {
        cout << "\n=====================================\n";
        cout << "          Admin Panel - " << username;
        cout << "\n=====================================\n";
        cout << "1. Add Location\n";
        cout << "2. Add Road\n";
        cout << "3. Edit Location\n";
        cout << "4. Edit Road\n";
        cout << "5. Remove Location\n";
        cout << "6. Remove Road\n";
        cout << "7. View Map\n";
        cout << "8. Logout\n";
        cout << "--------------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: 
                addNode(cityGraph); 
                break;
            case 2: 
                addEdge(cityGraph); 
                break;
            case 3: 
                editNode(cityGraph); 
                break;
            case 4: 
                editEdge(cityGraph); 
                break;
            case 5: 
                removeNode(cityGraph); 
                break;
            case 6: 
                removeEdge(cityGraph); 
                break;
            case 7: 
                viewMap(cityGraph); 
                break;
            case 8:
                system("cls");
                // Auto-save on logout if modified
                if (cityGraph.isModified()) {
                    storage.saveToFile(cityGraph);
                    cityGraph.setModified(false);
                }
                return;
            default: 
                cout << "Invalid choice!\n";
        }
    } while(choice != 9);
}

void Admin::addNode(Graph& cityGraph) {
    string name;
    int category;
    float traffic;
    system("cls");
    cout << "\n=====================================\n";
    cout << "       Adding New Location to Map";
    cout << "\n=====================================\n";
    cout << "Enter Location name : \n";
    cout << "-----------------------\n";
    cin.ignore();
    getline(cin, name);
    cout<<"\nSelect category below.\n";
    cout << "-----------------------\n";
    cout << "Categories (0:Stop, 1:Hospital, \n2:PetrolPump, 3:PoliceStation, \n4:School, 5:Landmark): ";
    cin >> category;
    cout << "\n-----------------------\n";
    cout << "Traffic heuristic: ";
    cin >> traffic;
    
    if (category >= 0 && category <= 5) {
        cityGraph.addNode(name, static_cast<NodeCategory>(category), traffic);
    } else {
        cout << "Invalid category!\n";
    }
}

void Admin::addEdge(Graph& cityGraph) {
    string from, to;
    float weight, heuristic;
    int oneWay;
    system("cls");
    cout << "\n=====================================\n";
    cout << "       Adding New Road in Map";
    cout << "\n=====================================\n";
    cout << "From Location : ";
    cin.ignore();
    getline(cin, from);
    cout << "To Location : ";
    getline(cin, to);
    cout << "Distance/Weight: ";
    cin >> weight;
    cout << "Traffic heuristic: ";
    cin >> heuristic;
    cout << "One-way? (0=No, 1=Yes): ";
    cin >> oneWay;
    cityGraph.addEdge(from, to, weight, heuristic, oneWay);
}

void Admin::editNode(Graph& cityGraph) {
    system("cls");
    cout << "\n=====================================\n";
    cout << "        Edit Your Location";
    cout << "\n=====================================\n";

    string oldName, newName;
    int category;
    float traffic;

    cout << "Enter Location name to edit: ";
    cin.ignore();
    getline(cin, oldName);
    cout<<endl;
    cout << "Enter new name : ";
    getline(cin, newName);
    cout<<endl;
    cout << "Enter new category (0:Stop, 1:Hospital, \n2:PetrolPump, 3:PoliceStation, \n4:School, 5:Landmark): ";
    cin >> category;
    cout<<endl;
    cout << "Enter new traffic heuristic: ";
    cin >> traffic;

    if (category >= 0 && category <= 5){
        cityGraph.editNode(oldName, newName, static_cast<NodeCategory>(category), traffic);
    }
    else{
        cout << "Invalid category!\n";
    }

}

void Admin::editEdge(Graph& cityGraph) {
    system("cls");
    cout << "\n=====================================\n";
    cout << "          Edit Your Road";
    cout << "\n=====================================\n";

    string from, to;
    float weight, heuristic;
    bool oneWay;

    cout << "Enter source Location : ";
    cin.ignore();
    getline(cin, from);

    cout << "Enter destination Location : ";
    getline(cin, to);

    cout << "Enter new distance/weight: ";
    cin >> weight;

    cout << "Enter new traffic heuristic: ";
    cin >> heuristic;

    cout << "One-way? (0=No, 1=Yes): ";
    cin >> oneWay;

    cityGraph.editEdge(from, to, weight, heuristic, oneWay);
}

void Admin::removeNode(Graph& cityGraph) {
    system("cls");
    cout << "\n=====================================\n";
    cout << "        Remove Location From Map";
    cout << "\n=====================================\n";
    string name;
    cout << "Enter Location name to remove: ";
    cin.ignore();
    getline(cin, name);
    
    cityGraph.removeNode(name);
}

void Admin::removeEdge(Graph& cityGraph) {
    system("cls");
    cout << "\n=====================================\n";
    cout << "        Remove Road From Map";
    cout << "\n=====================================\n";
    string from, to;
    cout << "Enter source Location : ";
    cin.ignore();
    getline(cin, from);
    cout << "Enter destination Location : ";
    getline(cin, to);
    
    cityGraph.removeEdge(from, to);
}

void Admin::viewMap(Graph& cityGraph) {
    cityGraph.printMap();
}