#include <QIntValidator>
#include <QRegExpValidator>

#include <string>
#include <iostream>
#include "playerinterface.h"
#include "ui_playerinterface.h"


using namespace std;

PlayerInterface::PlayerInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerInterface)
{
    player = nullptr;
    ui->setupUi(this);

    // make textbox accpet numbers only
    ui->orderIn->setValidator(new QIntValidator(0, 1000, this));
}



void PlayerInterface::setStackWidgetUI()
{
    this->setFixedSize(this->width(),this->height());
    ui->stat_btn->setEnabled(false);
    QPixmap user(":images/user.png");
    ui->label_user->setPixmap(user.scaled(120,120, Qt::KeepAspectRatio));

    QPixmap retailer(":images/retailer.png");
    ui->label_retailer->setPixmap(retailer.scaled(100,100, Qt::KeepAspectRatio));

    QPixmap wholesaler(":images/wholesaler.png");
    ui->label_wholesaler->setPixmap(wholesaler.scaled(100,100, Qt::KeepAspectRatio));

    QPixmap distributor(":images/distributor.png");
    ui->label_distributor->setPixmap(distributor.scaled(100,100, Qt::KeepAspectRatio));

    QPixmap factory(":images/factory.png");
    ui->label_factory->setPixmap(factory.scaled(100,100, Qt::KeepAspectRatio));

}

PlayerInterface::PlayerInterface(QWidget *parent,Game* game, std::vector<Player*> allPlayers) :
    QDialog(parent),
    ui(new Ui::PlayerInterface),
    game(game),
    allPlayers(allPlayers)
{
    ui->setupUi(this);
    setStackWidgetUI();
    ui->stackedWidget->setCurrentIndex(0);
}

void PlayerInterface::on_orderBtn_clicked()
{
    QString nOrder = ui->orderIn->text();
    if(nOrder.isEmpty()) {
        ui->orderIn->focusWidget();
        ui->orderIn->setStyleSheet("QLineEdit { background-color: red; }");
    } else {
        ui->orderIn->setStyleSheet("QLineEdit { background-color: white; }");
        ui->orderBtn->setDisabled(true);
        this->sendOrderToPlayer(nOrder.toUInt());
    }
}

void PlayerInterface::sendOrderToPlayer(int nBeers) {
    player->startTransaction(nBeers);
}


PlayerInterface::~PlayerInterface()
{
    delete ui;
}

void PlayerInterface::receiveOrder(int numberOfBeers) {
    player->receiveOrder(numberOfBeers);

    if(player->transactionReceived()) {
        updateUi();
    }
}

void PlayerInterface::receiveShipment(int numberOfBeers) {
    player->receiveShipment(numberOfBeers);

    if(player->getRole() == CONSUMER) {
        ui->orderIn->setText(QString::number(game->getConsumerOrderForWeek()));
        placeOrder(game->getConsumerOrderForWeek());
    }

    if(player->transactionReceived()) {
        updateUi();
    }
}

void PlayerInterface::placeOrder(int numberOfBeers) {
    game->addOrder(numberOfBeers, player->getRole());
}

void PlayerInterface::placeShipment(int numberOfBeers){
    game->addShipment(numberOfBeers, player->getRole());
}

void PlayerInterface::setGame(Game *p_game) {
    this->game = p_game;
}

void PlayerInterface::setPlayer(Player *player) {
    this->player = player;
    player->setInterface(this);

    // disable input field for CONSUMER
    if(player->getRole() == CONSUMER)
        ui->orderIn->setEnabled(false);

    string playerName = PLAYER_NAMES[player->getRole()];
    string downstreamName = PLAYER_NAMES[player->getRole() - 1];
    string upstreamName = PLAYER_NAMES[player->getRole() + 1];

    this->setWindowTitle(QString::fromStdString(playerName));
    ui->PlayerArea->setTitle(QString::fromStdString(playerName));
}

int PlayerInterface::getRole() {
    if(player == nullptr) {
        return -1;
    }
    return player->getRole();
}

void PlayerInterface::updateUi() {
    // enable button
    ui->orderBtn->setEnabled(true);
    ui->week->setNum(game->getCurrentWeek());

    ui->incomingOrder->setNum(player->getDemand());

    ui->totalCost->setNum(player->getTotalCost());

    // older
    ui->inventory->setNum(player->getOldInventory());
    ui->backLog->setNum(player->getOldBackOrder());

    // set outgoing and incoming  shipments
    ui->outgoingShipment->setNum(player->getOutgoingShipment());
    ui->incomingShipment->setNum(player->getIncomingShipment());

    // display inventory after transactions
    ui->inventoryAfter->setNum(player->getInventory());
    ui->backlogAfter->setNum(player->getBackorder());
}

void PlayerInterface::on_retailer_btn_clicked()
{
    int retailerPlayer = game->getPRetailerId();
    if(retailerPlayer == 0){
        game->setPRetailerId(game->getGId()+1);
        linkInterfaceAndGame(1);
    }else{
        QMessageBox::information(this,"Player Choose", "Role alreday chosen");
    }
}

void PlayerInterface::on_wholesaler_btn_clicked()
{
    int wholesalerPlayer = game->getPWholesalerId();
    if(wholesalerPlayer == 0){
        game->setPWholesalerId(game->getGId()+2);
        linkInterfaceAndGame(2);
    }else{
        QMessageBox::information(this,"Player Choose", "Role alreday chosen");
    }
}

void PlayerInterface::on_distributor_btn_clicked()
{
    int distributorPlayer = game->getPDistributorId();
    if(distributorPlayer == 0){
        game->setPDistributorId(game->getGId()+3);
        linkInterfaceAndGame(3);
    }else{
        QMessageBox::information(this,"Player Choose", "Role alreday chosen");
    }
}

void PlayerInterface::on_factory_btn_clicked()
{
    int factoryPlayer = game->getPFactId();
    if(factoryPlayer == 0){
        game->setPFactId(game->getGId()+4);
        linkInterfaceAndGame(4);
    }else {
        QMessageBox::information(this,"Player Choose", "Role alreday chosen");
    }
}


// Helper functions
void PlayerInterface::startGame()
{
    ui->stat_btn->setEnabled(true);
    if(game->isGamePlayable()){
        game->initGame();
        game->startGame();
    }
}

void PlayerInterface::linkInterfaceAndGame(int player_number)
{
    this->setPlayer(allPlayers[player_number]);
    ui->stackedWidget->setCurrentIndex(1);
    this->setWindowTitle(QString::fromStdString(PLAYER_NAMES[player_number]));
    ui->PlayerArea->setTitle(QString::fromStdString(PLAYER_NAMES[player_number]));
    player->setInterface(this);
    game->setPlayerInterface(this, player_number);
    startGame();
}

void PlayerInterface::on_stat_btn_clicked()
{
    // Statistics
    std::vector<int> orders = player->getOrderHistory();
    std::vector<int> incomingShipment = player->getIncomingShipmentHistory();
    std::vector<int> outgoingShipment= player->getOutgoingShipmentHistory();

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

void PlayerInterface::on_current_game_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void PlayerInterface::on_exit_game_clicked()
{
    this->close();
}

void PlayerInterface::on_linegraph_check_stateChanged(int arg1)
{
    on_stat_btn_clicked();
}

void PlayerInterface::on_show_incoming_stateChanged(int arg1)
{
    on_stat_btn_clicked();
}

void PlayerInterface::on_show_outgoing_stateChanged(int arg1)
{
    on_stat_btn_clicked();
}

