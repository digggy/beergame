#include "beergamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BeerGameWindow w;
    w.setWindowIcon(QIcon(":images/beer-icon.png"));
    w.show();
    return a.exec();
}
