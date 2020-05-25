#include <iostream>
#include <string>

#include "player.h"
#include "game.h"
#include "order.h"
#include "shipment.h"

#include "playerinterface.h"

using namespace std;

Player::Player(int role) :
    role(role)
{};

void Player::placeOrder(int numberOfBeers) {
    orderPlaced = true;
    if(playerInterface != nullptr)
        playerInterface->placeOrder(numberOfBeers);
}

void Player::placeShipment(int numberOfBeers){
    shipmentPlaced = true;
    if(playerInterface != nullptr)
        playerInterface->placeShipment(numberOfBeers);
}

void Player::startTransaction(int nOrders) {
    orderReceived = false;
    shipmentReceived = false;
    // Adding in the orderHistory
    orderHistory.push_back(nOrders);
    placeOrder(nOrders);
    placeShipment(outgoingShipment);
}

bool Player::transactionReceived() {
    return (orderReceived && shipmentReceived);
}

std::vector<int> Player::getIncomingShipmentHistory() const
{
    return incomingShipmentHistory;
}

void Player::setIncomingShipmentHistory(const std::vector<int> &value)
{
    incomingShipmentHistory = value;
}

std::vector<int> Player::getOutgoingShipmentHistory() const
{
    return outgoingShipmentHistory;
}

void Player::setOutgoingShipmentHistory(const std::vector<int> &value)
{
    outgoingShipmentHistory = value;
}

std::vector<int> Player::getOrderHistory() const
{
    return orderHistory;
}

void Player::setOrderHistory(const std::vector<int> &value)
{
    orderHistory = value;
}

void Player::updateData() {
    oldInventory = inventory;
    oldBackOrder = backOrder;
    
    orderPlaced = false;
    shipmentPlaced = false;
    
    totalCost += (double) holdingCost * (double) inventory +
            (double) backOrderCost * (double) backOrder;

    // set outgoing and incoming  shipments
    increaseInventory(incomingShipment);
    if(role != CONSUMER)
        outgoingShipment = getAvailableShipment(demand);
}


void Player::receiveOrder(int orderedBeers) {
    orderReceived = true;
    demand = orderedBeers;

    if(orderReceived && shipmentReceived) {
        updateData();
    }
}

void Player::receiveShipment(int shipped) {
    incomingShipment = shipped;
    incomingShipmentHistory.push_back(incomingShipment);
    shipmentReceived = true;

    if((orderReceived && shipmentReceived) || role == CONSUMER ) {
        updateData();
    }
}

int Player::getAvailableShipment(int downstreamDemand){
    int previous = inventory;
    int toFulfill = downstreamDemand + backOrder;
    decreaseInventory(toFulfill);
    int outgoingShipment = previous - inventory;
    outgoingShipmentHistory.push_back(outgoingShipment);
    return outgoingShipment;
};

int Player::decreaseInventory(int numberOfBeers){
    inventory -= numberOfBeers;
    if(inventory <0) {
        backOrder = abs(inventory);
        inventory = 0;
    }

    return inventory;
};

int Player::increaseInventory(int numberOfBeers){
    inventory += numberOfBeers;
    return inventory;
};

void Player::setInterface(PlayerInterface* playerInterface) {
    this->playerInterface = playerInterface;
}

bool Player::isOrderPlaced() {
    return orderPlaced;
}

bool Player::isShipmentPlaced() {
    return shipmentPlaced;
}

int Player::getIncomingShipment() {
    return incomingShipment;
}

int Player::getOutgoingShipment() {
    return outgoingShipment;
}

int Player::getDemand() {
    return demand;
}

int Player::getBackorder(){
    if(backOrder < 0) {
        // invalid backorder. Print to error window
    }
    return backOrder;
};

int Player::getOldBackOrder() {
    return oldBackOrder;
}

int Player::getInventory(){
    if(inventory < 0) {
        // assert or print log to error window.
    }
    return inventory;
};

int Player::getOldInventory() {
    return oldInventory;
}

int Player::getTotalCost() {
    return totalCost;
}

/////
/// For the sake of test cases
/////

void Player::setPId(int id) {
    this->pId = id;
}

void Player::setDemand(int demand) {
    this->demand = demand;
}

void Player::setCost(double cost) {
    this->cost = cost;
}

void Player::setInventory(int in) {
    this->inventory = in;
}

void Player::setTotalCost(double cost) {
    this->totalCost = cost;
}

void Player::setIncomingShipment(int in) {
    this->incomingShipment = in;
}

void Player::setOutgoingShipment(int out) {
    this->outgoingShipment = out;
}

void Player::setBackorder(int o) {
    this->backOrder = o;
}

void Player::setOrderPlaced(int o) {
    this->orderPlaced = o;
}

void Player::setRole(int role) {
    this->role = role;
}

int Player::getPId() {
    return pId;
}

int Player::getCost(){
    return cost;
};

bool Player::isOrderReceived() {
    return orderReceived;
}

bool Player::isShipmentReceived() {
    return shipmentReceived;
}

