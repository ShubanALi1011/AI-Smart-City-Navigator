#include "User.h"
#include <iostream>

void User::showUserMenu(Graph& cityGraph) {
    int choice = 0;
    do {
        cout << "\n=====================================\n";
        cout << "          --- User Panel ---";
        cout << "\n=====================================\n";
        cout << "1. Shortest Path\n";
        cout << "2. Smart Path (Traffic Aware)\n";
        cout << "3. Nearest Special Place\n";
        cout << "  -- Hospital\n";
        cout << "  -- Police Station\n";
        cout << "  -- Fire Brigade\n";
        cout << "  -- Stop\n";
        cout << "4. View City Map\n";
        cout << "5. Back to Main Menu\n";
        cout << "--------------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        cin.ignore();

        switch(choice) {
            case 1: 
                findShortestPath(cityGraph); 
                break;
            case 2: 
                findSmartPath(cityGraph); 
                break;
            case 3: 
                findNearestSpecialPlace(cityGraph); 
                break;
            case 4: 
                viewMap(cityGraph); 
                break;
            case 5:
                system("cls");
                break;
            default: 
                cout << "Invalid choice!\n";
        }
    } while(choice != 5);
}

void User::findShortestPath(Graph& cityGraph) {
    system("cls");
    cout << "\n=====================================\n";
    cout << "         Find Shortest Path";
    cout << "\n=====================================\n";
    string from, to;
    cout << "Enter starting point: ";
    getline(cin, from);
    cout << "Enter destination: ";
    getline(cin, to);
    cityGraph.findShortestPath(from, to);
}

void User::findSmartPath(Graph& cityGraph) {
    system("cls");
    cout << "\n=====================================\n";
    cout << "         Find Smart AI Path";
    cout << "\n=====================================\n";
    string from, to;
    cout << "Enter starting point: ";
    getline(cin, from);
    cout << "Enter destination: ";
    getline(cin, to);
    cityGraph.findSmartPath(from, to);
}

void User::findNearestSpecialPlace(Graph& cityGraph) {
    system("cls");
    cout << "\n=====================================\n";
    cout << "     Find Nearest Special Location";
    cout << "\n=====================================\n";
    string from;
    int category;
    cout << "Enter your location: ";
    getline(cin, from);
    cout<<"----------------------\n";
    cout << "Find nearest (0:Stop, 1:Hospital, \n2:PetrolPump, 3:PoliceStation, \n4:School, 5:Landmark): ";
    cin >> category;
    cityGraph.findNearestSpecialPlace(from, static_cast<NodeCategory>(category));
}

void User::viewMap(Graph& cityGraph) {
    cityGraph.printMap();
}