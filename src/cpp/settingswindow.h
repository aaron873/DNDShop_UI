#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <stdio.h>
#include <QDialog>
#include <QCheckBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>

#define FILE_DB "./itemDB.csv"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

private slots:
    void SelectAllOwners();
    void SelectAllTypes();
    void SelectAllQualities();
    void AddNewItem();
    void ResetForms();

private:
    Ui::SettingsWindow *ui;
    std::string MakeItemLine();
    bool CheckValidItem();
    bool CheckBoxChecked(QObjectList boxes);
    std::string GetSelectedRarity();
    std::string StringToLower(std::string inStr);
    void ResetUI();
};

#endif // SETTINGSWINDOW_H
