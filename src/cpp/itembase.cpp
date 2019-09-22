#include "itembase.h"

ItemBase::ItemBase(string in_itemName, vector<int> in_cost, string in_description):
    itemName(in_itemName), cost(in_cost), description(in_description) { }


// Prints the item
void ItemBase::PrintItem() { printf("%s, (%d %d %d), %s\n",itemName.c_str(),cost[0],cost[1],cost[2],description.c_str()); }
