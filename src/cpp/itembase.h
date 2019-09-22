#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <vector>
#include <string>

using namespace std;

class ItemBase
{
public:
    ItemBase(string in_itemName, vector<int> in_cost, string in_description);
    void PrintItem();

    int operator [](int i) const { return cost[i]; }
    int& operator [](int i) { return cost[i]; }

    vector<int> cost;
    string itemName;
    string description;
    double rarity;

};

#endif // ITEMBASE_H
