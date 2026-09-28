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
#include <iomanip>

//Zia's part
double getBudget() {
    string input;

    while (true) {
        cout << "What is your budget (RM): ";
        cin >> input;

        try {
            size_t used = 0;
            double budget = stod(input, &used);   // turn the text into a number

            if (used != input.size()) {           // e.g. "20abc"
                cout << "Invalid input. Please enter numbers only (e.g. 20 or 49.90)." << endl;
            } else if (!(budget > 0)) {           // zero or negative
                cout << "Budget must be more than RM0. Please try again." << endl;
            } else if (budget > 100000) {         // unrealistic amount
                cout << "Budget is too large. Please enter a realistic amount." << endl;
            } else {
                return budget;                    // valid budget
            }
        } catch (...) {                           // letters, symbols, etc.
            cout << "Invalid input. Please enter numbers only (e.g. 20 or 49.90)." << endl;
        }
    }
}

// Finds items with the chosen category + colour, keeps those within budget,
// and displays them. Returns the items that were displayed (for Dylan's part).
vector<Item> showMatchedItems(const vector<Item>& catalog, const string& category,
                              const string& color, double budget) {
    vector<Item> matched;   // items with the right category and colour
    vector<Item> shown;     // items we actually display

    for (const auto& item : catalog) {
        if (item.category == category && item.color == color) {
            matched.push_back(item);
        }
    }

    if (matched.empty()) {
        cout << "\nNo items found." << endl;
        return shown;
    }

    for (const auto& item : matched) {
        if (item.price <= budget) {
            shown.push_back(item);
        }
    }

    cout << fixed << setprecision(2);

    if (!shown.empty()) {
        cout << "\n" << shown.size() << " Item(s) found:" << endl;
    } else {
        // nothing affordable -> pick the cheapest = closest to the budget
        Item closest = matched[0];
        for (const auto& item : matched) {
            if (item.price < closest.price) {
                closest = item;
            }
        }
        shown.push_back(closest);
        cout << "\nSorry, no item is within your budget of RM" << budget << "." << endl;
        cout << "1 Item found (closest to your budget):" << endl;
    }

    for (size_t i = 0; i < shown.size(); ++i) {
        cout << (i + 1) << "." << shown[i].name << " | " << shown[i].style
             << " | RM" << shown[i].price << endl;
    }
    cout << (shown.size() + 1) << ".None" << endl;

    return shown;
}

// Dylan's part
void selectItem(const vector<Item>& shownItems, vector<Item>& cart) {
    int choice;

    while (true) {
        cout << "Which item would you like? (1-" << shownItems.size()
             << ", " << shownItems.size() + 1 << ". None): ";

        if (cin >> choice) {
            if (choice >= 1 && choice <= static_cast<int>(shownItems.size())) {
                cart.push_back(shownItems[choice - 1]);

                cout << shownItems[choice - 1].name
                     << " has been added to your cart!" << endl;

                return;
            } 
            else if (choice == static_cast<int>(shownItems.size()) + 1) {
                cout << "No item selected." << endl;
                return;
            } 
            else {
                cout << "Invalid number. Please choose a valid option." << endl;
            }
        } 
        else {
            cout << "Invalid input. Please enter a number." << endl;
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
    string selectedColor = getUserColor(userChoice);
    const string selectedCategory = userChoice == 1 ? "Shirts" : userChoice == 2 ? "Pants" : "Hats";
    cout << "\nAvailable " << selectedColor << " " << selectedCategory << ":\n";
    for (const auto& item : catalog) {
        if (item.category == selectedCategory && item.color == selectedColor) {
            cout << item.name << " | " << item.gender << " | " << item.style
                 << " | RM" << item.price << "\n";
        }
    }
          double budget = getBudget(); // Zia's part
    vector<Item> shownItems = showMatchedItems(catalog, selectedCategory, selectedColor, budget); // Zia's part

    // Dylan's part
    vector<Item> cart;
    selectItem(shownItems, cart);
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Press Enter to exit...";
    std::cin.get();
    
    return 0;
}
