#ifndef SHOPWINDOW_H
#define SHOPWINDOW_H

#include "shopbase.h"
#include "itembase.h"
#include "settingswindow.h"
#include <stdlib.h>
#include <vector>
#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QToolButton>
#include <QRadioButton>
#include <QDebug>

namespace Ui {
class ShopWindow;
}

class ShopWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopWindow(QWidget *parent = nullptr);
    ~ShopWindow();

private slots:
    void HandleGenerate();
    void HandleSettings();

private:

    /********************
     * Member Variables *
     *******************/
    Ui::ShopWindow *ui;

    // Custom UI objects
    QPushButton *generateShopButton;
    QToolButton *settingsButton;
    QTableView *itemTable;

    // Radio Button Vectors
    std::vector<QRadioButton*> qualityButtonVector;
    std::vector<QRadioButton*> typeButtonVector;
    std::vector<QRadioButton*> ownerButtonVector;

    /********************
     * Member Functions *
     *******************/
    int GetCheckedRadio(std::vector<QRadioButton*> inVect);

};

#endif // SHOPWINDOW_H
