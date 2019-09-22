#include "shopbase.h"

ShopBase::ShopBase(int quality, int owner, int type) :
    shopQuality(quality), shopOwner(owner), shopType(type)
{

    InitializeItemVector();
    double moneyFactor = quality - (quality * 0.5) + 0.5;

}


void ShopBase::InitializeItemVector() {
    // get the DB file
    QFile db(FILE_DB);

    // Open the file, returning error messsage if didnt open
    if(!db.open(QIODevice::ReadOnly)) {
        printf("Error: Item Database File Not Found.\n");
        return ;
    }
    QTextStream itemDB(&db);

    // Loop to get each item in the file
    while(!itemDB.atEnd()) {

        if(true) {  //ADD CONDITION SINCE ALL ITEMS ARE CURRENTLY ADDED TO SHOP

            // Add the item to the shop
            shopItems.push_back(GetNextItem(&itemDB));
            shopItems.back().PrintItem();
        }
    }
}



ItemBase ShopBase::GetNextItem(QTextStream *itemDB) {

    // Grab the next line
    string currItem = itemDB->readLine().toStdString();

    string name;
    vector<int> cost;
    string coin;
    string desc;
    istringstream ss(currItem);

    // Get item name
    getline(ss,name,',');

    // Get item cost

    // Get gold
    getline(ss,coin,'(');
    getline(ss,coin,' ');
    cost.push_back(atoi(coin.c_str()));

    // Get silver
    getline(ss,coin,' ');
    cost.push_back(atoi(coin.c_str()));

    // Get bronze
    getline(ss,coin,',');
    cost.push_back(atoi(coin.c_str()));

    // Get item desc
    getline(ss,desc,',');

    qDebug() << cost[0] << " " << cost[1] << " " << cost[2];
    return ItemBase(name, cost, desc);
}



/* Getters */
int ShopBase::GetShopQuality() { return shopQuality; }
int ShopBase::GetShopType() { return shopQuality; }
int ShopBase::GetShopOwner() { return shopQuality; }
double ShopBase::GetMoneyFactor() { return shopQuality; }
vector<int> ShopBase::GetMoneySupply() { return moneySupply; }
vector<ItemBase> ShopBase::GetShopItems() { return shopItems; }
