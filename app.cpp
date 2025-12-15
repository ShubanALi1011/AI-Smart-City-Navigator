// app.cpp
#include <iostream>
#include <stdlib.h>
#include "Data Base/files/Graph.h"
#include "Data Base/files/Admin.h"
#include "Data Base/files/User.h"
#include "Data Base/files/storage.h"
using namespace std;

void showMainMenu() {
    Graph cityGraph;
    Storage storage;
    // Auto-load data on startup
    storage.loadFromFile(cityGraph);
    system("cls");

    int choice = 0;
    do {
        cout << "=========================================\n";
        cout << "    WELCOME TO AI SMART CITY NAVIGATOR";
        cout << "\n=========================================\n";
        cout << "1. Admin Login\n";
        cout << "2. User Panel\n";
        cout << "3. Exit\n";
        cout << "--------------------------------------\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;
                
        switch(choice) {
            case 1: {
                system("cls");
                Admin admin(storage);  // give access of storage (to admin for saving in data )
                admin.login(cityGraph);
                break;
            }
            case 2:
                system("cls");
                User user;
                user.showUserMenu(cityGraph);
                break;
            case 3:
                // Auto-save on exit if modified
                if (cityGraph.isModified()) 
                    storage.saveToFile(cityGraph);
                system("cls");
                cout << "=================================================\n";
                cout << "Thank you for using AI Smart City Navigator!\n";
                cout << "         --- Have a great day! --- \n";
                cout << "=================================================\n";
                exit(0);
            default:
                cout << " Invalid choice! Please enter 1-4.\n";
        }
    } while(choice != 4);
}

int main() {    
    showMainMenu();
    return 0;
}