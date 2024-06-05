#include "menu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menu m;
    m.show();
    return a.exec();
}
