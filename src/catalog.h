#pragma once

#include <string>
#include <vector>
using namespace std;

struct Item{
    string name;
    string category; // Shirts, Pants, Hats
    string gender; // Mens, Ladies
    string style; // Casual, Formal, Smart Casual, Sports, Dates
    string color;
    double price;
};

vector<Item> buildCatalog();