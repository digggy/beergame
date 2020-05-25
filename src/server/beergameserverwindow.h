#ifndef BEERGAMESERVERWINDOW_H
#define BEERGAMESERVERWINDOW_H

#include <QMainWindow>

#include "beergameserver.h"

namespace Ui {
class BeerGameServerWindow;
}

/**
 * \brief Responsible in creating a window for beergame-server
 **/

class BeerGameServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BeerGameServerWindow(QWidget *parent = nullptr);
    ~BeerGameServerWindow();

private slots:
    void on_start_server_btn_clicked();

    void on_stopServerBtn_clicked();

private:
    Ui::BeerGameServerWindow *ui;
    BeerGameServer* beerGameServer;
};

#endif // BEERGAMESERVERWINDOW_H
