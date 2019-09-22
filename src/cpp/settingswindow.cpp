#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    connect(ui->addItemButton, SIGNAL(clicked()), this, SLOT (AddNewItem()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT (ResetForms()));
    connect(ui->eachCheckbox, SIGNAL(clicked()), this, SLOT (SelectAllTypes()));
    connect(ui->allCheckbox, SIGNAL(clicked()), this, SLOT (SelectAllOwners()));
    connect(ui->everyCheckbox, SIGNAL(clicked()), this, SLOT (SelectAllQualities()));
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}


void SettingsWindow::SelectAllOwners() {

    // Get the checkboxes
    QObjectList checkboxes = ui->shopOwnersContainer->children();
    bool isChecked = ui->allCheckbox->isChecked();

    // Loop to set all the boxes to the AllOwners checked status
    QObjectList::iterator itr;
    for(itr = checkboxes.begin(); itr != checkboxes.end(); itr++) {
        (qobject_cast<QCheckBox*>(*itr))->setChecked(isChecked);
    }
}


void SettingsWindow::SelectAllTypes() {

    // Get the checkboxes
    QObjectList checkboxes = ui->shopTypesContainer->children();
    bool isChecked = ui->eachCheckbox->isChecked();

    // Loop to set all the boxes to the AllOwners checked status
    QObjectList::iterator itr;
    for(itr = checkboxes.begin(); itr != checkboxes.end(); itr++) {
        (qobject_cast<QCheckBox*>(*itr))->setChecked(isChecked);
    }
}


void SettingsWindow::SelectAllQualities() {

    // Get the checkboxes
    QObjectList checkboxes = ui->shopQualityContainer->children();
    bool isChecked = ui->everyCheckbox->isChecked();

    // Loop to set all the boxes to the AllOwners checked status
    QObjectList::iterator itr;
    for(itr = checkboxes.begin(); itr != checkboxes.end(); itr++) {
        (qobject_cast<QCheckBox*>(*itr))->setChecked(isChecked);
    }
}


void SettingsWindow::AddNewItem() {

    // Make sure the entered item is valid
    if(!CheckValidItem()) {
        qDebug() << "Item Invalid.";
        QMessageBox::information(this, tr("Error"), tr("Item Invalid."));
        return ;
    }

    // Get the DB file
    QFile db(FILE_DB);

    // Open the item database file
    if(!db.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Error: Item Database File Not Found";
        return ;
    }
    QTextStream itemDB(&db);
    uint64_t currPos = 0;

    // Loop until hit end of file
    while(!itemDB.atEnd()) {

        // Get the current item
        std::string currItem = itemDB.readLine().toStdString();
        std::istringstream ss(currItem);
        std::string name;
        getline(ss,name,',');

        // If found the item already in the db
        if(strcmp(StringToLower(ui->nameInput->text().toStdString()).c_str(),
                  StringToLower(name).c_str()) == 0) {
            qDebug() << "Item already in db";
            QMessageBox::information(this, tr("Error"), tr("Item already in Database"));

            return;
        }

        // If found the location for insertion
        if(strcmp(StringToLower(ui->nameInput->text().toStdString()).c_str(),
                  StringToLower(name).c_str()) < 0) {

            // Add the text from the start of the file to the buffer
            itemDB.seek(0);
            QByteArray buff(itemDB.read(currPos).toStdString().c_str());

            // Add the added item to the buffer
            buff += MakeItemLine().c_str();

            // Check if we are at the start of the file
            if(currPos == 0)
                buff += '\n';

            // Add the ending half of the file
            itemDB.seek(currPos);
            buff += itemDB.read(db.size());

            // Jump back to start of the file to overwrite the db with the new item
            db.seek(0);
            db.write(buff);
            ResetUI();
            db.close();

            return;
        }

        // If we have not yet found the location
        currPos += currItem.size() + 1;
    }

    // If we have hit the end of the file, insert there
    QByteArray buff(itemDB.readAll().toStdString().c_str());
    buff = buff + "\n" + MakeItemLine().c_str();
    db.write(buff);
    ResetUI();
    db.close();
}


std::string SettingsWindow::MakeItemLine() {
    std::string retVal;

    /* Add Item Name */
    retVal = ui->nameInput->text().toStdString() + ", ";


    /* Add Item Cost */
    retVal += "(";

    // Gold
    if(ui->goldInput->text().toStdString().empty())
        retVal += "0";
    retVal = retVal +  ui->goldInput->text().toStdString() + ",";

    // Silver
    if(ui->silverInput->text().toStdString().empty())
        retVal += "0";
    retVal = retVal +  ui->silverInput->text().toStdString() + ",";

    // Copper
    if(ui->copperInput->text().toStdString().empty())
        retVal += "0";
    retVal = retVal +  ui->copperInput->text().toStdString() + "), ";


    /* Add Item Description */
    retVal = retVal + ui->descInput->text().toStdString() + ", ";
    /* Rarity */
    retVal = retVal + GetSelectedRarity() + ", ";


    /* Shop Quality */
    retVal += "(";

    // Get the checkboxes
    QObjectList checkboxes = ui->shopQualityContainer->children();
    QObjectList::iterator itr;

    // Loop to get all the checked Shop Owners, adding it to the DB line
    for(itr = checkboxes.begin(); itr != checkboxes.end(); itr++) {
        if((qobject_cast<QCheckBox*>(*itr))->isChecked() && (qobject_cast<QCheckBox*>(*itr))->text() != "Select All") {
            retVal = retVal + (qobject_cast<QCheckBox*>(*itr))->text().toStdString() + ",";
        }
    }

    retVal += "), ";


    /* Add Shop Owners */
    retVal += "(";

    // Get the checkboxes
    checkboxes = ui->shopOwnersContainer->children();

    // Loop to get all the checked Shop Owners, adding it to the DB line
    for(itr = checkboxes.begin(); itr != checkboxes.end(); itr++) {
        if((qobject_cast<QCheckBox*>(*itr))->isChecked() && (qobject_cast<QCheckBox*>(*itr))->text() != "Select All") {
            retVal = retVal + (qobject_cast<QCheckBox*>(*itr))->text().toStdString() + ",";
        }
    }
    retVal += "), ";


    /* Add Shop Types */
    retVal += "(";

    // Get the checkboxes
    checkboxes = ui->shopTypesContainer->children();

    // Loop to get all the checked Shop Owners, adding it to the DB line
    for(itr = checkboxes.begin(); itr != checkboxes.end(); itr++) {
        if((qobject_cast<QCheckBox*>(*itr))->isChecked() && (qobject_cast<QCheckBox*>(*itr))->text() != "Select All") {
            retVal = retVal + (qobject_cast<QCheckBox*>(*itr))->text().toStdString() + ",";
        }
    }
    retVal += ")";


    return retVal;
}


void SettingsWindow::ResetUI() {
    // Reset the UI to before an item was added
    ui->nameInput->setText("");
    ui->descInput->setText("");
    ui->goldInput->setText("");
    ui->silverInput->setText("");
    ui->copperInput->setText("");
    ui->alwaysButton->click();

    // Loop to set all the boxes to off
    QObjectList checkboxes = ui->shopOwnersContainer->children();

    QObjectList::iterator itr;
    for(itr = checkboxes.begin(); itr != checkboxes.end(); itr++) {
        (qobject_cast<QCheckBox*>(*itr))->setChecked(false);
    }

    checkboxes = ui->shopTypesContainer->children();
    // Loop to set all the boxes to the AllOwners checked status
    for(itr = checkboxes.begin(); itr != checkboxes.end(); itr++) {
        (qobject_cast<QCheckBox*>(*itr))->setChecked(false);
    }

    checkboxes = ui->shopQualityContainer->children();
    // Loop to set all the boxes to the AllOwners checked status
    for(itr = checkboxes.begin(); itr != checkboxes.end(); itr++) {
        (qobject_cast<QCheckBox*>(*itr))->setChecked(false);
    }

    // Each item can be in the thrift shop
    ui->thriftCheckbox->click();
}


std::string SettingsWindow::GetSelectedRarity() {

    // Get the radiobuttons
    QObjectList radiobuttons = ui->rarityContainer->children();

    // Loop to find the checked RadioButton
    QObjectList::iterator itr;
    for(itr = radiobuttons.begin(); itr != radiobuttons.end(); itr++) {
        if((qobject_cast<QRadioButton*>(*itr))->isChecked()) {
            return (qobject_cast<QRadioButton*>(*itr))->text().toStdString();
        }
    }

    return "";
}


bool SettingsWindow::CheckValidItem() {
    bool retVal = true;

    // If no name entered
    if(ui->nameInput->text().toStdString().empty())
        retVal = false;

    // If no cost entered
    if(ui->goldInput->text().toStdString().empty() && ui->silverInput->text().toStdString().empty() && ui->copperInput->text().toStdString().empty())
        retVal = false;

    // If no desc entered
    if(ui->descInput->text().toStdString().empty())
        retVal = false;

    // If no types selected
    if(!CheckBoxChecked(ui->shopTypesContainer->children()))
        retVal = false;

    // If no owners selected
    if(!CheckBoxChecked(ui->shopOwnersContainer->children()))
        retVal = false;

    // If no rarity selected
    if(!CheckBoxChecked(ui->shopQualityContainer->children()))
        retVal = false;

    return retVal;
}


bool SettingsWindow::CheckBoxChecked(QObjectList boxes) {

    // Loop through each checkbox and see if at least one is checked
    QObjectList::iterator itr;
    for(itr = boxes.begin(); itr != boxes.end(); itr++) {
        if((qobject_cast<QCheckBox*>(*itr))->isChecked())
            return true;
    }

    // If none are checked, return false
    return false;
}


std::string SettingsWindow::StringToLower(std::string inStr) {
    std::string outStr = inStr;

    for(int x = 0; x < inStr.size(); x++) {
        outStr[x] = std::toupper(inStr[x]);
    }
    return outStr;
}


void SettingsWindow::ResetForms() { ResetUI(); }
