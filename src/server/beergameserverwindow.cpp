#include "beergameserverwindow.h"
#include "ui_beergameserverwindow.h"

#include <iostream>

#include "beergameserver.h"

BeerGameServerWindow::BeerGameServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BeerGameServerWindow)
{
    ui->setupUi(this);
    ui->stopServerBtn->setEnabled(false);
}


BeerGameServerWindow::~BeerGameServerWindow()
{
    delete ui;
}

void BeerGameServerWindow::on_start_server_btn_clicked() {
    QString ipAddress = ui->ip_input->text();
    int portValue = ui->port_input->text().toInt();

    beerGameServer = new BeerGameServer;
    if(!beerGameServer->listen(QHostAddress(ipAddress), portValue)) {
        std::cout << "Error while establishing server" << std::endl;
        ui->stopServerBtn->setEnabled(false);
        return;
    }
    ui->input_widget->setEnabled(false);
    ui->start_server_btn->setEnabled(false);
    ui->stopServerBtn->setEnabled(true);
}

void BeerGameServerWindow::on_stopServerBtn_clicked()
{
    if(beerGameServer == nullptr) return;
    beerGameServer->stopServer();
    delete beerGameServer;
    ui->input_widget->setEnabled(true);
    ui->start_server_btn->setEnabled(true);
    ui->stopServerBtn->setEnabled(false);
}
