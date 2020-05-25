#include <iostream>
#include <vector>
#include <map>

#include "game.h"
#include "order.h"
#include "playerinterface.h"

using namespace std;

std::vector<int> Game::getDemandPerWeek() const
{
    return demandPerWeek;
}

void Game::setDemandPerWeek(const std::vector<int> &value)
{
    demandPerWeek = value;
}

std::map<int, std::vector<Order> > Game::getOrdersToBeExecuted() const
{
    return ordersToBeExecuted;
}

void Game::setOrdersToBeExecuted(const std::map<int, std::vector<Order> > &value)
{
    ordersToBeExecuted = value;
}

std::map<int, std::vector<Shipment> > Game::getShipmentsToBeExecuted() const
{
    return shipmentsToBeExecuted;
}

void Game::setShipmentsToBeExecuted(const std::map<int, std::vector<Shipment> > &value)
{
    shipmentsToBeExecuted = value;
}

Game::Game() {
    this->gId = 1;
    this->pRetailerId = 0;
    this->pWholesalerId = 0;
    this->pDistributorId = 0;
    this->pFactId = 0;
}

void Game::initGame() {
    //########
    //## Orders and Shipments for week 1
    //########
    // Consumer ----> Retailer
    ordersToBeExecuted[0].push_back(Order(10, 4, 1, getUpstream(CONSUMER)));

    // Consumer <----- Retailer ----> Wholesaler
    ordersToBeExecuted[0].push_back(Order(11, 4, 1, getUpstream(RETAILER)));
    shipmentsToBeExecuted[0].push_back(Shipment(11, 4, 1, getDownstream(RETAILER)));

    // Retailer <----- Wholesaler ----> Distributor
    ordersToBeExecuted[0].push_back(Order(12, 4, 1, getUpstream(WHOLESALER)));
    shipmentsToBeExecuted[0].push_back(Shipment(12, 4, 1, getDownstream(WHOLESALER)));

    // Wholesaler <----- Distributoer ----> Factory
    ordersToBeExecuted[0].push_back(Order(13, 4, 1, getUpstream(DISTRIBUTOR)));
    shipmentsToBeExecuted[0].push_back(Shipment(13, 4, 1, getDownstream(DISTRIBUTOR)));

    // Wholesaler <----- Factory ----> Factory
    shipmentsToBeExecuted[0].push_back(Shipment(14, 4, 1, getUpstream(FACTORY)));
    shipmentsToBeExecuted[0].push_back(Shipment(14, 4, 1, getDownstream(FACTORY)));

    //########
    //## Orders and Shipments for week 2
    //########
    // Consumer ----> Retailer
    ordersToBeExecuted[1].push_back(Order(20, 4, 1, getUpstream(CONSUMER)));

    // Consumer <----- Retailer ----> Wholesaler
    ordersToBeExecuted[1].push_back(Order(21, 4, 1, getUpstream(RETAILER)));
    shipmentsToBeExecuted[1].push_back(Shipment(11, 4, 1, getDownstream(RETAILER)));

    // Retailer <----- Wholesaler ----> Distributor
    ordersToBeExecuted[1].push_back(Order(22, 4, 1, getUpstream(WHOLESALER)));
    shipmentsToBeExecuted[1].push_back(Shipment(12, 4, 1, getDownstream(WHOLESALER)));

    // Wholesaler <----- Distributoer ----> Factory
    ordersToBeExecuted[1].push_back(Order(23, 4, 1, getUpstream(DISTRIBUTOR)));
    shipmentsToBeExecuted[1].push_back(Shipment(13, 4, 1, getDownstream(DISTRIBUTOR)));

    // Wholesaler <----- Factory ----> Factory
    shipmentsToBeExecuted[1].push_back(Shipment(24, 4, 1, getUpstream(FACTORY)));
    shipmentsToBeExecuted[1].push_back(Shipment(24, 4, 1, getDownstream(FACTORY)));
}

void Game::startGame() {
    // start executing orders and shipment for 1st week
    currentWeek++;
    executeOrdersForCurrentWeek();
    executeShipmentsForCurrentWeek();
}

void Game::executeOrdersForCurrentWeek(){
    vector<Order> weekOrders = ordersToBeExecuted[currentWeek-1];
    for(Order order : weekOrders) {
        order.executeOrder();
    }        
};

void Game::executeShipmentsForCurrentWeek(){
    vector<Shipment> weeksShipments = shipmentsToBeExecuted[currentWeek-1];
    for(Shipment shipment : weeksShipments) {
        shipment.executeShipment();
    }
};

int Game::getConsumerOrderForWeek() {
    return demandPerWeek[currentWeek-1];
}

int Game::advanceWeek(){
    nOrdersReceived = 0;
    nShipmentsReceived = 0;
    currentWeek++;

    // NOTIFY PLAYERS THAT THE WEEK HAS ADVANCED
    executeOrdersForCurrentWeek();
    executeShipmentsForCurrentWeek();

    return currentWeek;
};

void Game::addOrder(int numberOfBeers, int role){
    // For Order
    int orderWeek, shipmentWeek;
    if(role != FACTORY) {
        orderWeek = orderDelay + currentWeek;
        Order order(99, numberOfBeers, orderWeek, this->getUpstream(role));
        ordersToBeExecuted[orderWeek - 1].push_back(order);
        nOrdersReceived++;
    } else {
        // for factory, order is made to itself. So it will deliver to itself in 2 * factoryDelay
        shipmentWeek = factoryDelay * 2 + currentWeek;
        Shipment shipment(99, numberOfBeers, shipmentWeek, this->getUpstream(role));
        shipmentsToBeExecuted[shipmentWeek - 1].push_back(shipment);
        nShipmentsReceived++;
    }

    if(nOrdersReceived == nPlayers - 1 && nShipmentsReceived == nPlayers) {
        advanceWeek();
    }
};

void Game::addShipment(int numberOfBeers, int role){
    // For shipment
    int shipmentWeek;
    if(role != CONSUMER) {
        // TODO: Add a new variable for shipment delay
        // TODO: Add a function for genOrderId()
        shipmentWeek = orderDelay + currentWeek;
        Shipment shipment(99, numberOfBeers, shipmentWeek, this->getDownstream(role));
        shipmentsToBeExecuted[shipmentWeek - 1].push_back(shipment);
        nShipmentsReceived++;
    }

    if(nOrdersReceived == nPlayers - 1 && nShipmentsReceived == nPlayers) {
        advanceWeek();
    }
};

void Game::addPlayerInterface(PlayerInterface* player) {
    (players).push_back(player);
}

PlayerInterface* Game::getDownstream(int role) {
    if(role == CONSUMER) {
        return (players)[role];
    } else {
        return (players)[role - 1];
    }
}

PlayerInterface* Game::getUpstream(int role) {
    if(role == FACTORY) {
        return (players)[role];
    } else {
        return (players)[role + 1];
    }
}

bool Game::isGamePlayable() {
    std::cout << "Player Size: " << players.size() << std::endl;
    if(players.size() == 5) {
        if (pFactId != 0 && pDistributorId != 0 && pWholesalerId != 0 && pRetailerId != 0)
        {
            return true;
        }
    }
    return false;
}

void Game::setGId(int gId) {
    this->gId = gId;
}

void Game::setWeeksToBePlayed(int w){
    weeksToBePlayed = w;
};

void Game::setInfoCode(int code){
    infoCode = code;
};

void Game::setStartingInventory(int si){
    startingInventory = si;
};

void Game::setBackorderCost(double cost){
    backorderCost = cost;
};

void Game::setHoldingCost(double hc){
    holdingCost = hc;
};

void Game::setFactoryDelay(int factoryDelay) {
    this->factoryDelay = factoryDelay;
}

void Game::setOrderDelay(int orderDelay) {
    this->orderDelay = orderDelay;
}

void Game::setShipmentDelay(int s) {
    this->shipmentDelay = s;
}

int Game::getGId() {
    return gId;
}

int Game::getShipmentDelay() {
    return shipmentDelay;
}

int Game::getWeeksToBePlayed() {
    return weeksToBePlayed;
}

int Game::getInfoCode() {
    return infoCode;
}

double Game::getBackorderCost() {
    return backorderCost;
}

double Game::getHoldingCost() {
    return holdingCost;
}

int Game::getFactoryDelay() {
    return factoryDelay;
}

int Game::getOrderDelay() {
    return orderDelay;
}

int Game::getStartingInventory() {
    return startingInventory;
}

int Game::getCurrentWeek() {
    return currentWeek;
}

vector<string> Game::generatePasswords(){
    return vector<string>();
};

/**
* @brief what does it do?
*/
void Game::setCurrentWeek(int week){
    this->currentWeek = week;
};


std::vector<PlayerInterface *> Game::getPlayers() const
{
    return players;
}

void Game::setPlayers(const std::vector<PlayerInterface *> &value)
{
    players = value;
}

void Game::setPlayerInterface(PlayerInterface *value, int player_number)
{
    this->players[player_number] = value;
}

PlayerInterface * Game::getPlayerInterface(int player_number)
{
    return this->players[player_number];
}


std::vector<bool> Game::getRolesTaken() const
{
    return rolesTaken;
}

void Game::setRolesTaken(const std::vector<bool> &value)
{
    rolesTaken = value;
}
