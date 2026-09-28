#include <iostream>
#include "catalog.h"
#include <limits>
#include <algorithm>
#include <cctype>
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

string getUserColor(int category) {
    const vector<string> clothingColors = {"red", "green", "blue"};
    const vector<string> hatColors = {"black", "brown", "white"};
    const vector<string>& colors = category == 3 ? hatColors : clothingColors;

    while (true) {
        cout << "Which colour would you like? (";
        for (size_t index = 0; index < colors.size(); ++index) {
            if (index > 0) cout << ", ";
            cout << colors[index];
        }
        cout << "): ";

        string color;
        cin >> color;
        transform(color.begin(), color.end(), color.begin(), [](unsigned char character) {
            return static_cast<char>(tolower(character));
        });

        for (const string& option : colors) {
            if (color == option) {
                string selectedColor = option;
                selectedColor[0] = static_cast<char>(toupper(static_cast<unsigned char>(selectedColor[0])));
                return selectedColor;
            }
        }

        cout << "Please enter the right colour option." << endl;
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
    string selectedColor = getUserColor(userChoice);
    const string selectedCategory = userChoice == 1 ? "Shirts" : userChoice == 2 ? "Pants" : "Hats";
    cout << "\nAvailable " << selectedColor << " " << selectedCategory << ":\n";
    for (const auto& item : catalog) {
        if (item.category == selectedCategory && item.color == selectedColor) {
            cout << item.name << " | " << item.gender << " | " << item.style
                 << " | RM" << item.price << "\n";
        }
    }
      
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Press Enter to exit...";
    std::cin.get();
    
    return 0;
}
