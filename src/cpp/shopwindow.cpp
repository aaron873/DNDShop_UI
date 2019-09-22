#include "shopwindow.h"
#include "ui_shopwindow.h"

ShopWindow::ShopWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopWindow)
{
    ui->setupUi(this);

    // Initialize UI objects

    // Initialize the button to begin random shop generation
    generateShopButton = ui->generateShopButton;
    connect(generateShopButton, SIGNAL(released()), this, SLOT (HandleGenerate()));

    // Initialize settings button
    settingsButton = ui->settingsButton;
    connect(settingsButton, SIGNAL(clicked()), this, SLOT (HandleSettings()));

    // Make description and cost width larger
    itemTable = ui->itemTable;
    itemTable->setColumnWidth(1, 150);
    itemTable->setColumnWidth(2, 330);

    // Add shop quality radio buttons to vector
    qualityButtonVector.push_back(ui->lowQualityButton);
    qualityButtonVector.push_back(ui->mediumQualityButton);
    qualityButtonVector.push_back(ui->highQualityButton);

    // Add shop type radio buttons to vector
    typeButtonVector.push_back(ui->magicItemsButton);
    typeButtonVector.push_back(ui->innButton);
    typeButtonVector.push_back(ui->generalGoodsButton);
    typeButtonVector.push_back(ui->armorerButton);
    typeButtonVector.push_back(ui->fletcherButton);
    typeButtonVector.push_back(ui->alchemistButton);
    typeButtonVector.push_back(ui->clothierButton);

    // Add shop owner radio buttons to vector
    ownerButtonVector.push_back(ui->randomButton);
    ownerButtonVector.push_back(ui->dwarfButton);
    ownerButtonVector.push_back(ui->humanButton);
    ownerButtonVector.push_back(ui->halflingButton);
    ownerButtonVector.push_back(ui->elfButton);
    ownerButtonVector.push_back(ui->halfElfButton);
    ownerButtonVector.push_back(ui->tieflingButton);
    ownerButtonVector.push_back(ui->gnomeButton);


}

ShopWindow::~ShopWindow()
{
    delete ui;
}

int ShopWindow::GetCheckedRadio(std::vector<QRadioButton*> inVect) {
    for(unsigned long x = 0; x < inVect.size(); x++) {
        // Get the radio button checked
        if(inVect[x]->isChecked())
            return x;
    }
    return 0;
}

void ShopWindow::HandleGenerate() {

    ShopBase currShop = ShopBase(GetCheckedRadio(qualityButtonVector),
                                 GetCheckedRadio(typeButtonVector),
                                 GetCheckedRadio(ownerButtonVector) );
    vector<ItemBase> shopItems = currShop.GetShopItems();

    // Loop through each item to initialize the table
    for(int itemCounter = 0; itemCounter != shopItems.size(); itemCounter++) {
        QTableWidgetItem* currBlock ;

        // Set the name of the item
        currBlock = new QTableWidgetItem() ;
        currBlock->setText(QString(shopItems[itemCounter].itemName.c_str()));
        ui->itemTable->setItem(itemCounter + 1, 0, currBlock);

        // Set the cost of the item
        currBlock = new QTableWidgetItem() ;
        vector<int> cost = shopItems[itemCounter].cost;

        char *gold = new char(100),
             *silver = new char(100),
             *bronze = new char(100);

        // Cast the integer coin values to cstrings
        itoa(cost[0],gold,10);
        itoa(cost[1],silver,10);
        itoa(cost[2],bronze,10);

        // Set table value to cost
        string costStr = "(" + string(gold) + "G, " + silver + "S, " + bronze + "B)";
        currBlock->setText(QString(costStr.c_str()));
        ui->itemTable->setItem(itemCounter + 1, 1, currBlock);

        // Set the desc of the item
        currBlock = new QTableWidgetItem() ;
        currBlock->setText(QString(shopItems[itemCounter].description.c_str()));
        ui->itemTable->setItem(itemCounter + 1, 2, currBlock);
    }
    ui->itemTable->resizeColumnsToContents();
}


void ShopWindow::HandleSettings() {
    SettingsWindow settWindow;
    settWindow.setModal(true);
    settWindow.exec();

}


