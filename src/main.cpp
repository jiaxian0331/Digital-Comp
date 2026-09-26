#include <iostream>
#include "catalog.h"
using namespace std;

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

    return 0;
}

