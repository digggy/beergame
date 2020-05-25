#include "clientinterface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientInterface w;
    w.show();
    return a.exec();
}
