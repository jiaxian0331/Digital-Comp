#include "catalog.h"
using namespace std;

namespace {

    struct BaseItem {
        string name;
        string gender;
        string style;
        double price;
    };

    const vector<BaseItem> shirtBases = {
        {"Graphic Tee", "Mens", "Casual", 20.0},
        {"Business Shirt", "Mens", "Formal", 40.0},
        {"Button-Down Shirt", "Mens", "Smart Casual", 30.0},
        {"Sports Cool-Tech Shirt", "Mens", "Sports", 25.0},
        {"Elegant Date Night Shirt", "Mens", "Dates", 40.0},

        {"Casual Blouse", "Ladies", "Casual", 20.0},
        {"FormalBlouse", "Ladies", "Formal", 40.0},
        {"Button-Down Top", "Ladies", "Smart Casual", 30.0},
        {"Sports Cool-Tech Shirt", "Ladies", "Sports", 25.0},
        {"Date Night Top", "Ladies", "Dates", 40.0}
    };

    const vector<BaseItem> pantsBases = {
        {"Casual Jeans", "Mens", "Casual", 35.0},
        {"Formal Trousers", "Mens", "Formal", 50.0},
        {"Slacks", "Mens", "Smart Casual", 25.0},
        {"Sports Shorts", "Mens", "Sports", 15.0},
        {"Tailored Pants", "Mens", "Dates", 45.0},

        {"Casual Jeans", "Ladies", "Casual", 35.0},
        {"Formal Skirt", "Ladies", "Formal", 40.0},
        {"Ankle-Length Pants", "Ladies", "Smart Casual", 25.0},
        {"Sports Leggings", "Ladies", "Sports", 20.0},
        {"Long Skirt", "Ladies", "Dates", 35.0}
    };

    const vector<Item> hats = {
        {"Baseball Cap", "Hats", "Mens", "Casual", "White", 5.0},
        {"Top Hat", "Hats", "Mens", "Formal", "Black", 30.0},
        {"Flat Cap", "Hats", "Mens", "Smart Casual", "Brown", 10.0},
        {"Sports Cap", "Hats", "Mens", "Sports", "Black", 15.0},
        {"Fedora", "Hats", "Mens", "Dates", "Brown", 20.0},

        {"Sun Hat", "Hats", "Ladies", "Casual", "Brown", 10.0},
        {"Cloche Hat", "Hats", "Ladies", "Formal", "Black", 15.0},
        {"Beret", "Hats", "Ladies", "Smart Casual", "Brown", 25.0},
        {"Sports Headband", "Hats", "Ladies", "Sports", "Black", 5.0},
        {"Wide-Brim Hat", "Hats", "Ladies", "Dates", "White", 20.0}
    };

    const vector<string> shirtPantColors = {"Red", "Blue", "Green"};

    vector<Item> expandwithColors(const vector<BaseItem>& bases, const string& category) {
        vector<Item> result;
        for (const auto& base : bases)
        {
            for (const auto& color : shirtPantColors)
            {
                result.push_back({base.name, category, base.gender, base.style, color, base.price});
            }
        }
        return result;
    }
}

vector<Item> buildCatalog() {
    vector<Item> catalog;

    vector<Item> shirts = expandwithColors(shirtBases, "Shirts");
    vector<Item> pants = expandwithColors(pantsBases, "Pants");

    catalog.insert(catalog.end(), shirts.begin(), shirts.end());
    catalog.insert(catalog.end(), pants.begin(), pants.end());
    catalog.insert(catalog.end(), hats.begin(), hats.end());

    return catalog;
}