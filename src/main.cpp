#include <iostream>
#include <vector>
#include "catalog.h"
#include <limits>
#include <string>
using namespace std;

//Lavan's part
int getUserSelection() {
        int choice;

        while (true) {
            cout << "what item do you want? (1. shirts, 2. pants, 3. hats): ";

            if (cin >> choice) {
                if (choice == 1) {
                    cout << "You have selected 1 shirt."<< endl;
                    return choice;
                } else if (choice == 2) {
                    cout << "You have selected 1 pair of pants."<< endl;
                    return choice;
                }else if (choice == 3) {
                    cout << "You have selected 1 hat."<< endl;
                    return choice;
                } else {
                    cout << "Invalid choice. Please enter 1, 2, or 3."<< endl;
                }
            } else {
                cout << "Invalid input detected. Please avoid letters and enter a number."<< endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }


int main() {
    vector<Item> catalog = buildCatalog();

    cout << "Total Items: " << catalog.size() << "\n\n";
    
    int shirtCount = 0, pantsCount = 0, hatsCount = 0;

    for (const auto& it : catalog) {
        cout << it.category << " | " << it.gender << " | " << it.style << " | " << it.color << " | " << it.name << " | RM" << it.price << "\n";
    
        if (it.category == "Shirts") shirtCount++;
        else if (it.category == "Pants") pantsCount++;
        else if (it.category == "Hats") hatsCount++;
    }

    cout << "\n--- Counts ---\n";
    cout << "Shirts: " << shirtCount << "\n";
    cout << "Pants: " << pantsCount << "\n";  
    cout << "Hats: " << hatsCount << "\n";

    int userChoice = getUserSelection(); // Lavan's part
        
    return 0;
}
