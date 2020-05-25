#include <iostream>
#include <vector>
#include <string>

#include "game.h"
#include "player.h"
#include "playerinterface.h"
#include "instructor.h"
#include "instructorwindow.h"
#include "ui_instructorwindow.h"

using namespace std;

void Instructor::setUi(Ui::InstructorWindow* ui) {
    this->ui = ui;
}

void Instructor::setWindowParent(QWidget* uiParent) {
    this->uiParent = uiParent;
}

void Instructor::showGameStatus(){};

int Instructor::createGame(){
    createGames(1);

    return 0; // game succesfully created
}

vector<Game> Instructor::createGames(int numberOfGames){

    if(numberOfGames == 1) {
        // As of now only one game can be created

        QString backlogCostStr = ui->backlogCostIn->text();
        QString factoryDelayStr = ui->factoryDelayIn->text();
        QString holdingCostStr = ui->holdingCostIn->text();
        QString nWeeksStr = ui->nWeeksIn->text();
        QString orderDelayStr = ui->orderDelayIn->text();
        QString startInventoryStr = ui->startInventoryIn->text();
        Qt::CheckState botCheckState = ui->botCheckBox->checkState();

        double backlogCost = backlogCostStr.toDouble();
        int factoryDelay = factoryDelayStr.toInt();
        double holdingCost = holdingCostStr.toDouble();
        int nWeeks = nWeeksStr.toUInt();
        int orderDelay = orderDelayStr.toUInt();
        int startInventory = startInventoryStr.toInt();

        Game* game = new Game();
        game->setHoldingCost(holdingCost);
        game->setBackorderCost(backlogCost);
        game->setFactoryDelay(factoryDelay);
        game->setWeeksToBePlayed(nWeeks);
        game->setOrderDelay(orderDelay);
        game->setStartingInventory(startInventory);

        Player* consumer = new Player(CONSUMER);
        Player* retailer = new Player(RETAILER);
        Player* wholesaler = new Player(WHOLESALER);
        Player* distributor = new Player(DISTRIBUTOR);
        Player* factory = new Player(FACTORY);

        std::vector<Player*> allPlayers {consumer, retailer, wholesaler, distributor, factory};

        PlayerInterface* consumerI = new PlayerInterface(uiParent);
        PlayerInterface* retailerI = new PlayerInterface(uiParent, game, allPlayers);
        PlayerInterface* wholesalerI = new PlayerInterface(uiParent, game, allPlayers);
        PlayerInterface* distributorI = new PlayerInterface(uiParent, game, allPlayers);
        PlayerInterface* factoryI = new PlayerInterface(uiParent, game, allPlayers);

        consumer->setInterface(consumerI);
        consumerI->setGame(game);
        consumerI->setPlayer(consumer);

        //Setting games for all players interfaces
        retailerI->setGame(game);
        wholesalerI->setGame(game);
        distributorI->setGame(game);
        factoryI->setGame(game);

        //Adding the player interface to the games
        game->addPlayerInterface(consumerI);
        game->addPlayerInterface(retailerI);
        game->addPlayerInterface(wholesalerI);
        game->addPlayerInterface(distributorI);
        game->addPlayerInterface(factoryI);


//        retailer->setInterface(retailerI);
//        retailerI->setPlayer(retailer);

//        wholesaler->setInterface(wholesalerI);
//        wholesalerI->setPlayer(wholesaler);

//        distributor->setInterface(distributorI);
//        distributorI->setPlayer(distributor);

//        factory->setInterface(factoryI);
//        factoryI->setPlayer(factory);

//        game->initGame();
//        game->startGame();
//        if(botCheckState == Qt::CheckState::Checked)
//            consumerI->show();


        retailerI->show();
        retailerI->move(0, 0);
        wholesalerI->show();
        wholesalerI->move(1000, 0);
        distributorI->show();
        distributorI->move(0, 800);
        factoryI->show();
        factoryI->move(1000, 800);
    }

    return vector<Game>();
}

/////
/// Instructor setters and getters
/////

void Instructor::setInstrEmail(string instrEmail) {
    this->instrEmail = instrEmail;
}

void Instructor::setInstrPassword(string instrPassword) {
    this->instrPassword = instrPassword;
}

void Instructor::setInstrId(int instrId) {
    this->instrId = instrId;
}

string Instructor::getInstrEmail() {
    return instrEmail;
}

string Instructor::getInstrPassword() {
    return instrPassword;
}

int Instructor::getInstrId() {
    return instrId;
}
