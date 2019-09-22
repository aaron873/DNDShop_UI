#ifndef SHOPBASE_H
#define SHOPBASE_H

#include "itembase.h"
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <QFile>
#include <QTextStream>
#include <QRadioButton>
#include <QCoreApplication>
#include <QDebug>

using namespace std;

#define FILE_DB "./itemDB.csv"

class ShopBase
{
public:

    /********************
     * Member Functions *
     *******************/
    ShopBase(int quality, int owner, int type);
    void InitializeItemVector();
    ItemBase GetNextItem(QTextStream *itemDB);


    // Getters
    int GetShopQuality();
    int GetShopType();
    int GetShopOwner();
    double GetMoneyFactor();
    vector<int> GetMoneySupply();
    vector<ItemBase> GetShopItems();

    /********************
     * Member Variables *
     *******************/
    int shopQuality;
    int shopOwner;
    int shopType;
    vector<int> moneySupply;
    vector<ItemBase> shopItems;
};

#endif // SHOPBASE_H
