#include "instructorwindow.h"
#include "ui_instructorwindow.h"

#include "player.h"
#include "playerinterface.h"
#include "game.h"
#include "instructor.h"

#include <QIntValidator>
#include <QDoubleValidator>
#include <QDesktopWidget>

#include <iostream>

InstructorWindow::InstructorWindow(QWidget *parent) :
    QDialog(parent),
    parent(parent),
    ui(new Ui::InstructorWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());

    ui->stackedWidget->setCurrentIndex(0);

    // Disable the server button initially
    ui->stop_server_btn->setEnabled(false);

    //Set up the icon
    QPixmap user(":images/user.png");
    ui->label_user->setPixmap(user.scaled(190,170, Qt::KeepAspectRatio));

    //Set the icons for user connection status aswell
    QPixmap retailer(":images/retailer.png");
    ui->label_retailer->setPixmap(retailer.scaled(70,70, Qt::KeepAspectRatio));

    QPixmap wholesaler(":images/wholesaler.png");
    ui->label_wholesaler->setPixmap(wholesaler.scaled(70,70, Qt::KeepAspectRatio));

    QPixmap distributor(":images/distributor.png");
    ui->label_distributor->setPixmap(distributor.scaled(70,70, Qt::KeepAspectRatio));

    QPixmap factory(":images/factory.png");
    ui->label_factory->setPixmap(factory.scaled(70,70, Qt::KeepAspectRatio));

    // Disable all player icons
        ui->r_container->setEnabled(false);
        ui->w_container->setEnabled(false);
        ui->d_container->setEnabled(false);
        ui->f_container->setEnabled(false);


    QDoubleValidator* costValidator = new QDoubleValidator(0, 10, 2, this);
    costValidator->setNotation(QDoubleValidator::StandardNotation);

    ui->backlogCostIn->setValidator(costValidator);
    ui->factoryDelayIn->setValidator(new QIntValidator(1, 5, this));
    ui->holdingCostIn->setValidator(costValidator);
    ui->nWeeksIn->setValidator(new QIntValidator(1, 52, this));
    ui->orderDelayIn->setValidator(new QIntValidator(1, 5, this));
    ui->startInventoryIn->setValidator(new QIntValidator(0, 1000, this));

    Instructor* instructor = new Instructor();
    instructor->setInstrId(1);
    instructor->setInstrEmail("instructor@beergame.de");
    instructor->setInstrPassword("password");
    instructor->setUi(ui);
    instructor->setWindowParent(parent);

    this->instructor = instructor;
}

InstructorWindow::~InstructorWindow()
{
    delete ui;
}

void InstructorWindow::on_startBtn_clicked()
{
    instructor->createGame();
    this->hide();
}

void InstructorWindow::on_go_online_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void InstructorWindow::on_home_screen_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void InstructorWindow::on_start_server_btn_clicked()
{
    QString ipAddress = ui->ip_input->text();
    int portValue = ui->port_input->text().toInt();

    beerGameServer = new BeerGameServer;
    if(!beerGameServer->listen(QHostAddress(ipAddress), portValue)) {
        std::cout << "Error while establishing server" << std::endl;
        ui->stop_server_btn->setEnabled(false);
        return;
    }
    beerGameServer->setUi(this->ui);

    ui->ip_input->setEnabled(false);
    ui->port_input->setEnabled(false);
    ui->stop_server_btn->setEnabled(true);
    ui->start_server_btn->setEnabled(false);
}

void InstructorWindow::on_stop_server_btn_clicked()
{
    if(beerGameServer == nullptr) return;
    beerGameServer->stopServer();
    delete beerGameServer;
    ui->ip_input->setEnabled(true);
    ui->port_input->setEnabled(true);
    ui->stop_server_btn->setEnabled(false);
    ui->start_server_btn->setEnabled(true);
}
