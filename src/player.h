#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>

#include "playerinterface.h"

class PlayerInterface;

#define CONSUMER 0
#define RETAILER 1
#define WHOLESALER 2
#define DISTRIBUTOR 3
#define FACTORY 4

const std::string PLAYER_NAMES[] = {
    "Consumer",
    "Retailer",
    "Wholesaler",
    "Distributor",
    "Factory"
};

/**
 * @brief This is the class for Player
 **/

class Player
{
private:

    
    /**
     * @brief Player's attribute for player Id 
     */
    int pId;
    
    /**
     * @brief Player's attribute for role 
     */
    int role;
    
    /**
     * @brief Player's attribute for old Inventory 
     */
    int oldInventory;
    
    /**
     * @brief Player's attribute for old BackOrder 
     */
    int oldBackOrder;
    
    /**
     * @brief Player's attribute for inventory 
     */
    int inventory = 12;
    
    /**
     * @brief Player's attribute for backOrder 
     */
    int backOrder = 0;
    
    /**
     * @brief Player's attribute for incomingOrder 
     */
    int incomingOrder = 0;
    
    /**
     * @brief Player's attribute for incomingShipment 
     */
    int incomingShipment = 0;
    
    /**
     * @brief Player's attribute for the incoming Shipment History
     */
    std::vector<int> incomingShipmentHistory= {};
    
    /**
     * @brief Player's attribute for outgoingShipment 
     */
    int outgoingShipment = 0;
    
    /**
     * @brief Player's attribute for outgoing Shipment History
     */
    std::vector<int> outgoingShipmentHistory= {};
    
    /**
     * @brief Player's attribute for demand 
     */
    int demand;
    
    /**
     * @brief Player's attribute for order History
     */
    std::vector<int> orderHistory= {};
    
    /**
     * @brief Player's attribute for holding Cost 
     */
    double holdingCost = 0.5;
    
    /**
     * @brief Player's attribute for backOrder Cost 
     */
    double backOrderCost = 1;
    
    /**
     * @brief Player's attribute for cost 
     */
    double cost = 0;
    
    /**
     * @brief Player's attribute for totalCost 
     */
    double totalCost = 0;
    
    /**
     * @brief Player's attribute for a boolean orderReceived 
     */
    bool orderReceived = false;
    
    /**
     * @brief Player's attribute for boolean shipmentReceived 
     */
    bool shipmentReceived = false;
    
    /**
     * @brief Player's attribute for boolean orderPlaced 
     */
    bool orderPlaced = false;
    
    /**
     * @brief Player's attribute for boolean shipmentPlaced 
     */
    bool shipmentPlaced = false;

    void updateData();
    int getAvailableShipment(int numberOfBeers);

    PlayerInterface* playerInterface = nullptr;

public: 
// every function here has been made void just for making template, change it accordingly
    
    /**
     * @brief Default Constructor for player
     **/
    Player() {}

    /**
     * @brief Construct player object with a given game instance and role.
     * @param role Factory, Distributor, Wholesaler, Retailer
    **/
    Player(int role);

    /**
     * @brief set a player interface to a player
     * @param playerInterface  The  player interface
     **/
    void setInterface(PlayerInterface*);

    /**
     * @brief Method to place order 
     * @param value The number of beers to order
     **/
    void placeOrder(int);

    /**
     * @brief Method to place Shipment 
     * @param value The number of beers to Ship
     **/
    void placeShipment(int);

    int getIncomingShipment();

    int getOutgoingShipment();

    /**
     * @brief Method to start the transaction with  order 
     * @param value The number of beers to order
     **/
    void startTransaction(int nOrders);

    /**
     * @brief Method to check if the transaction is received 
     * @return value  Transaction is received boolean value
     **/
    bool transactionReceived();

    /**
     * @brief Based on the demand from the downstream, it make changes to the inventory, and returns the number of beers that are available for 
     * shipments
     */

    void receiveShipment(int);
    void receiveOrder(int);
    /**
    * @brief decrease inventory by a certain number of beers
    * @param numberOfBeers number of beers
    * @return current inventory
    **/
    int decreaseInventory(int numberOfBeers);
    
    /**
    * @brief increase inventory by a certain number of beers
    * @param numberOfBeers number of beers
    * @return current inventory
    **/
    int increaseInventory(int numberOfBeers);
    
    void setPId(int);
    void setDemand(int);
    void setRole(int);
    void setInventory(int);
    void setBackorder(int);
    void setOutgoingShipment(int);
    void setOrderPlaced(int);
    void setTotalCost(double);
    void setIncomingShipment(int);
    void setCost(double);
    
    int getPId();
    bool isOrderPlaced();
    bool isShipmentPlaced();
    int getRole() const {return role;};
    int getBackorder();
    int getOldBackOrder();
    int getDemand();
    int getCost();
    int getTotalCost();
    int getInventory();
    int getOldInventory();

    bool isOrderReceived();
    bool isShipmentReceived();

    std::vector<int> getIncomingShipmentHistory() const;
    void setIncomingShipmentHistory(const std::vector<int> &value);
    std::vector<int> getOutgoingShipmentHistory() const;
    void setOutgoingShipmentHistory(const std::vector<int> &value);
    std::vector<int> getOrderHistory() const;
    void setOrderHistory(const std::vector<int> &value);
};

#endif //PLAYER_H
