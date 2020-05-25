#include "clientinterface.h"
#include "ui_ClientInterface.h"
#include <iostream>
#include <QStandardItemModel>
#include <QInputDialog>
#include <QMessageBox>
#include <QHostAddress>
#include <QLabel>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QDebug>
#include <QStyle>
#include <QJsonArray>

void ClientInterface::setStackWidgetUI()
{
    ui->connection_label->setText("Connected !");
    ui->proceed->show();

    ui->ip_input->setEnabled(false);
    ui->port_input->setEnabled(false);

    QMovie *gif = new QMovie(":images/connected.gif");
    gif->setScaledSize(QSize(140,140));
    ui->connection_status_logo->setMovie(gif);
    gif->start();

    QPixmap retailer(":images/retailer.png");
    ui->label_retailer->setPixmap(retailer.scaled(100,100, Qt::KeepAspectRatio));

    QPixmap wholesaler(":images/wholesaler.png");
    ui->label_wholesaler->setPixmap(wholesaler.scaled(100,100, Qt::KeepAspectRatio));

    QPixmap distributor(":images/distributor.png");
    ui->label_distributor->setPixmap(distributor.scaled(100,100, Qt::KeepAspectRatio));

    QPixmap factory(":images/factory.png");
    ui->label_factory->setPixmap(factory.scaled(100,100, Qt::KeepAspectRatio));

}


ClientInterface::ClientInterface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientInterface) // create the elements defined in the .ui file
    , m_PlayerClient(new PlayerClient(this)) // create the chat client
{
    // set up of the .ui file
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    ui->stackedWidget->setCurrentIndex(0);
    ui->orderBtn->setDisabled(true);
    ui->proceed->hide();
    ui->stat_btn->setEnabled(false);


    connect(m_PlayerClient, &PlayerClient::connected, this, &ClientInterface::connectedToServer);
    //Set stacked widget UI
    connect(m_PlayerClient, &PlayerClient::connected, this, &ClientInterface::setStackWidgetUI);
    connect(m_PlayerClient, &PlayerClient::loggedIn, this, &ClientInterface::loggedIn);
    connect(m_PlayerClient, &PlayerClient::roleTaken, this, &ClientInterface::roleTaken);
    connect(m_PlayerClient, &PlayerClient::loginError, this, &ClientInterface::loginFailed);
    connect(m_PlayerClient, &PlayerClient::messageReceived, this, &ClientInterface::messageReceived);
    connect(m_PlayerClient, &PlayerClient::setPlayerStatistics, this, &ClientInterface::setPlayerStatistics);
    connect(ui->Connect, &QPushButton::clicked, this, &ClientInterface::attemptConnection);
    connect(ui->orderBtn, &QPushButton::clicked, this, &ClientInterface::sendMessage);

    // Set UI inital settings
    ui->lineEdit_gameId->setEnabled(true);
    ui->select_role->setVisible(false);
    ui->connection_setup->setCurrentIndex(0);
    // The gif connection status Icon
    QMovie *gif = new QMovie(":images/not-connected.gif");
    gif->setScaledSize(ui->connection_status_logo->size());
    ui->connection_status_logo->setMovie(gif);
    gif->start();

    // User Image
    QPixmap user(":images/user.png");
    ui->label_user->setPixmap(user.scaled(120,120, Qt::KeepAspectRatio));
}

ClientInterface::~ClientInterface()
{
    // delete the elements created from the .ui file
    delete ui;
}

void ClientInterface::attemptConnection()
{
    int portNum;
    QString hostAddress;

    hostAddress = ui->ip_input->text();
    portNum = ui->port_input->text().toInt();

    m_PlayerClient->connectToServer(QHostAddress(hostAddress), portNum);
    ui->ip_input->setProperty("error",true);
    ui->port_input->setProperty("error",true);

    ui->ip_input->style()->polish(ui->ip_input);
    ui->ip_input->style()->unpolish(ui->ip_input);

    ui->port_input->style()->polish(ui->port_input);
    ui->port_input->style()->unpolish(ui->port_input);

    ui->ip_input->update();
    ui->port_input->update();
}

void ClientInterface::connectedToServer()
{
    ui->Connect->setEnabled(false);
    ui->lineEdit_gameId->setEnabled(false);

    ui->ip_input->setProperty("success",true);
    ui->port_input->setProperty("success",true);

    ui->ip_input->style()->polish(ui->ip_input);
    ui->ip_input->style()->unpolish(ui->ip_input);

    ui->port_input->style()->polish(ui->port_input);
    ui->port_input->style()->unpolish(ui->port_input);

    ui->ip_input->update();
    ui->port_input->update();

    attemptGameJoin(ui->lineEdit_gameId->text().toInt());
}

void ClientInterface::attemptLogin(const int &GameId, const int &role)
{
    // use the client to attempt a log in with the given username
    m_PlayerClient->login(GameId, role);
}

void ClientInterface::attemptGameJoin(const int &GameId)
{
    // use the client to attempt a log in with the given username
    m_PlayerClient->joinGame(GameId);
}

void ClientInterface::loggedIn()
{
    // once we successully log in we enable the ui to display and send messages
    ui->stackedWidget->setCurrentIndex(1);
    ui->PlayerArea->setTitle(m_PlayerClient->playerName);

    // clear the user name record
    m_lastUserName.clear();
}

void ClientInterface::roleTaken(QJsonArray &takenRole)
{
    std::vector<bool> roles_occupied;
    foreach (const QJsonValue & v, takenRole){
         roles_occupied.push_back(v.toBool());
    }
    if(roles_occupied[0]){
        ui->r_container->setEnabled(false);
    }

    if(roles_occupied[1]){
        ui->w_container->setEnabled(false);
    }

    if(roles_occupied[2]){
        ui->d_container->setEnabled(false);
    }

    if(roles_occupied[3]){
        ui->f_container->setEnabled(false);
    }
}

void ClientInterface::setPlayerStatistics(QJsonArray & value)
{
    ui->stat_btn->setEnabled(true);
    playerHistory = {};
    foreach (const QJsonValue & history, value){
        std::vector<int> phistory;
        foreach (const QJsonValue & v, history.toArray()){
             phistory.push_back(v.toInt());
        }
        playerHistory.push_back(phistory);
    }
    std::cout<<"Player history receiver : Ok";
}

void ClientInterface::loginFailed(const QString &reason)
{
    // the server rejected the login attempt
    // display the reason for the rejection in a message box
    QMessageBox::critical(this, tr("Error"), reason);
    // allow the user to retry, execute the same slot as when just connected
    connectedToServer();
}

void ClientInterface::messageReceived(const QString &text, const QString &sender)
{
    ui->orderBtn->setEnabled(true);
    QLabel* q =  this->findChild<QLabel*>(sender);   // store the index of the new row to append to the model containing the messages
    if(q==nullptr)
           return;
    q->setText(text);
}

void ClientInterface::sendMessage()
{
    ui->orderBtn->setDisabled(true);
     m_PlayerClient->sendMessage(ui->orderIn->text());
    // we use the client to send the message that the user typed

}
void ClientInterface::disconnectedFromServer()
{
    // if the client loses connection to the server

}

void ClientInterface::on_proceed_clicked()
{
    ui->connection_setup->setCurrentIndex(1);
    ui->proceed->hide();
}

// Player choose button
void ClientInterface::on_retailer_btn_clicked()
{
    int game_id = ui->lineEdit_gameId->text().toInt();
    attemptLogin(game_id, 1);
}

void ClientInterface::on_wholesaler_btn_clicked()
{
    int game_id = ui->lineEdit_gameId->text().toInt();
    attemptLogin(game_id, 2);
}

void ClientInterface::on_distributor_btn_clicked()
{
    int game_id = ui->lineEdit_gameId->text().toInt();
    attemptLogin(game_id, 3);
}

void ClientInterface::on_factory_btn_clicked()
{
    int game_id = ui->lineEdit_gameId->text().toInt();
    attemptLogin(game_id, 4);
}

void ClientInterface::on_stat_btn_clicked()
{
    // Statistics
    std::vector<int> orders = playerHistory[0];
    std::vector<int> incomingShipment = playerHistory[1];
    std::vector<int> outgoingShipment= playerHistory[2];

    ui->stat_widget->removeWidget(chartView);

    //Setting charts
    chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->setTitle("Player Stats");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    // setting different types of series

    if(ui->linegraph_check->isChecked()){
        series = new QtCharts::QLineSeries();

        QtCharts::QLineSeries *set_incoming = new QtCharts::QLineSeries();
        QtCharts::QLineSeries *set_outgoing = new QtCharts::QLineSeries();

        QtCharts::QValueAxis *axisX = new  QtCharts::QValueAxis();
        QtCharts::QValueAxis *axisY = new  QtCharts::QValueAxis();
        for(int i =0 ; i < (int) orders.size();i++){
            series->append(i,orders[i]);
            set_incoming->append(i,incomingShipment[i]);
            set_outgoing->append(i,outgoingShipment[i]);
        }
        chart->addSeries(series);

        if(ui->show_incoming->isChecked()){
            chart->addSeries(set_incoming);
        }
        if(ui->show_outgoing->isChecked()){
            chart->addSeries(set_outgoing);
        }

        axisX->setLabelFormat("%d");
        chart->addAxis(axisX, Qt::AlignBottom);
        axisY->setLabelFormat("%.1f");
        chart->addAxis(axisY, Qt::AlignLeft);
        axisX->setTickCount(orders.size());
        series->attachAxis(axisX);
        series->attachAxis(axisY);

     } else {
        // Enable Barchart
        bseries = new QtCharts::QStackedBarSeries(chart);
        QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
        QStringList categories;
        QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
        QtCharts::QBarSet *set = new QtCharts::QBarSet("Order");


        QtCharts::QBarSet *set_incoming = new QtCharts::QBarSet("Incoming ");
        QtCharts::QBarSet *set_outgoing = new QtCharts::QBarSet("Outgoing ");

        for (int i= 0; i < orders.size(); i++) {
            *set << orders[i];
            *set_incoming << incomingShipment[i];
            *set_outgoing<< outgoingShipment[i];
            categories << QString::number(i);

            bseries->append(set);

            if(ui->show_incoming->isChecked()){
                bseries->append(set_incoming);
            }
            if(ui->show_outgoing->isChecked()){
                bseries->append(set_outgoing);
            }
        }
        axisX->append(categories);
        chart->addSeries(bseries);

        chart->addAxis(axisX, Qt::AlignBottom);
        bseries->attachAxis(axisX);
        axisY->setLabelFormat("%d");
        chart->addAxis(axisY, Qt::AlignLeft);
        bseries->attachAxis(axisY);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
    }
   // Setting series to the charts
   chartView = new QtCharts::QChartView(chart);
   chartView->setRenderHint(QPainter::Antialiasing);

   ui->stat_widget->addWidget(chartView);
   ui->stackedWidget->setCurrentIndex(2);
}

void ClientInterface::on_current_game_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void ClientInterface::on_linegraph_check_stateChanged(int arg1)
{
    on_stat_btn_clicked();
}

void ClientInterface::on_show_incoming_stateChanged(int arg1)
{
    on_stat_btn_clicked();
}

void ClientInterface::on_show_outgoing_stateChanged(int arg1)
{
    on_stat_btn_clicked();
}
