#include <iostream>
#include "catalog.h"
#include <limits>
#include <algorithm>
#include <cctype>
#include <iomanip>
using namespace std;

//Lavan's part
int getUserSelection() {
        int choice;

        while (true) {
            cout << "\nWhat item are you looking for?" << endl;
            cout << "(1. shirts, 2. pants, 3. hats)" << endl << "\nPlease enter your choice: ";

            if (cin >> choice) {
                if (choice == 1) {
                    cout << "You have selected 1 shirt."<< endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return choice;
                } else if (choice == 2) {
                    cout << "You have selected 1 pair of pants."<< endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return choice;
                }else if (choice == 3) {
                    cout << "You have selected 1 hat."<< endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return choice;
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice. Please enter 1, 2, or 3."<< endl;
                }
            } else {
                cout << "Invalid input detected. Please avoid letters and enter a number."<< endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

// Sujiva's part
string getUserColor(int category) {
    const vector<string> clothingColors = {"red", "green", "blue"};
    const vector<string> hatColors = {"black", "brown", "white"};
    const vector<string>& colors = category == 3 ? hatColors : clothingColors;

    while (true) {
        cout << "\nWhich colour would you like?" << endl << "(";
        for (size_t index = 0; index < colors.size(); ++index) {
            if (index > 0) cout << ", ";
            cout << colors[index];
        }
        cout << ")" << endl << "\nPlease enter your choice: ";

        string color;
        cin >> color;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

//Zia's part
double getBudget() {
    string input;

    while (true) {
        cout << "\nWhat is your budget (RM): ";
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try {
            size_t used = 0;
            double budget = stod(input, &used);   

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
        cout << "==================================================" << endl;
    } else {
        
        Item closest = matched[0];
        for (const auto& item : matched) {
            if (item.price < closest.price) {
                closest = item;
            }
        }
        shown.push_back(closest);
        cout << "\nSorry, no item is within your budget of RM" << budget << "." << endl;
        cout << "1 Item found (closest to your budget):" << endl;
        cout << "==================================================" << endl;
    }

    for (size_t i = 0; i < shown.size(); ++i) {
        cout << (i + 1) << "." << shown[i].name << " | " << shown[i].style
             << " | RM" << shown[i].price << endl;
    }
    cout << (shown.size() + 1) << ".None" << endl;
    cout << "==================================================" << endl;

    return shown;
}

// Dylan's part
void selectItem(const vector<Item>& shownItems, vector<Item>& cart) {
    int choice;

    while (true) {
        cout << "\nWhich item would you like? (1-" << shownItems.size() + 1 << "): ";

        if (cin >> choice) {
            if (choice >= 1 && choice <= static_cast<int>(shownItems.size())) {
                cart.push_back(shownItems[choice - 1]);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << shownItems[choice - 1].name
                     << " has been added to your cart!" << endl;

                return;
            } 
            else if (choice == static_cast<int>(shownItems.size()) + 1) {
                cout << "No item selected." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            } 
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

// Jia Xian's part
void displayCart(const vector<Item>& cart) {
    cout << "\n==================================================" << endl;
    cout << "                 YOUR CART SUMMARY                " << endl;
    cout << "==================================================" << endl;

    if (cart.empty()) {
        cout << "Your cart is empty. No items were added." << endl;
    } else {
        double total = 0.0;
        cout << fixed << setprecision(2);
        for (size_t i = 0; i < cart.size(); ++i) {
            cout << (i + 1) << ". " << cart[i].name
                 << " | RM" << cart[i].price << endl;
            total += cart[i].price;
        }
        cout << "--------------------------------------------------" << endl;
        cout << "Total: RM" << total << endl;
    }
    cout << "==================================================" << endl;
}

int askNextAction() {
    while (true) {
        cout << "\nWhat would you like to do next?" << endl;
        cout << "(1. View Cart, 2. Add Items, 3. Checkout)" << endl;
        cout << "\nPlease enter your choice: ";

        int choice;
        if (cin >> choice) {
            if (choice >= 1 && choice <= 3) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return choice;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}


// Main Program
int main() {
    cout << "=====================================" << endl;
    cout << "== Welcome to Uniqlo Online Store! ==" << endl;
    cout << "=====================================" << endl;

    vector<Item> catalog = buildCatalog();
    vector<Item> cart;

    bool keepShopping = true;

    while (keepShopping) {
        int userChoice = getUserSelection();                          // Lavan's part
        string selectedColor = getUserColor(userChoice);
        const string selectedCategory =
            userChoice == 1 ? "Shirts" : userChoice == 2 ? "Pants" : "Hats";

        double budget = getBudget();                                  // Zia's part
        vector<Item> shownItems =
            showMatchedItems(catalog, selectedCategory, selectedColor, budget);

        if (!shownItems.empty()) {                                    // Dylan's part
            selectItem(shownItems, cart);
        } else {
            cout << "Nothing to select this round." << endl;
        }

        bool checkout = false;
        while (!checkout) {
            int action = askNextAction();

            if (action == 1) {
                displayCart(cart);
            }
            else if (action == 2) {
                break;
            }
            else {
                checkout = true;
                keepShopping = false;
            }
        }
    }

    displayCart(cart);

    cout << "\nPress Enter to exit the program...";
    cin.get();

    return 0;
}