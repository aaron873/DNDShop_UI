#include "shopwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShopWindow w;
    w.show();

    return a.exec();
}
