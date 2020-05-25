#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <map>

#include "order.h"
#include "shipment.h"
#include "player.h"
#include "playerinterface.h"

class Order;
class PlayerInterface;

/**
 * \brief Responsible in handling the game logic 
 */

class Game
{
private:
    /**
     * @brief Game's attribute for game Id
     */
    int gId;
    std::map<int, std::vector<Order>> ordersToBeExecuted;
    std::map<int, std::vector<Shipment>> shipmentsToBeExecuted;

    std::vector<PlayerInterface*> players;
    std::vector<int> demandPerWeek =
        {6, 6, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};

    /**
     * @brief Game's attribute for game's orderDelay
     */
    int orderDelay = 2;
    /**
     * @brief Game's attribute for game's holdingCost
     */
    double holdingCost = 0.5;
    /**
     * @brief Game's attribute for game's backorderCost
     */
    double backorderCost = 1;
    /**
     * @brief Game's attribute for game's startingInventory
     */
    int startingInventory = 12;
    /**
     * @brief Game's attribute for game's weeksToBePlayed
     */
    int weeksToBePlayed = 26;
    /**
     * @brief Game's attribute for game's currentWeek
     */
    int currentWeek = 0;
    /**
     * @brief Game's attribute for game's infoCode
     */
    int infoCode = 0;
    /**
     * @brief Game's attribute for game's factoryDelay
     */
    int factoryDelay = 1;
    /**
     * @brief Game's attribute for game's number of orders received
     */
    int nOrdersReceived = 0;
    /**
     * @brief Game's attribute for game's number of shipment received
     */
    int nShipmentsReceived = 0;
    /**
     * @brief Game's attribute for game's number of players
     */
    int nPlayers = 5;

    // test
    
    /**
     * @brief Game's attribute for game's instructor id 
     */
    int instrid;
    
    /**
     * @brief Game's attribute for game's Factory Id 
     */
    int pFactId;
    
    /**
     * @brief Game's attribute for game's Distributor Id 
     */
    int pDistributorId;
    
    /**
     * @brief Game's attribute for game's Wholesaler Id 
     */
    int pWholesalerId;
    
    /**
     * @brief Game's attribute for game's Retailer Id 
     */
    int pRetailerId;
    
    /**
     * @brief Game's attribute for game's shipment Delay 
     */
    int shipmentDelay;

    /**
     * @brief Game's attribute for player roles taken
     */
    std::vector<bool> rolesTaken = {false,false,false,false};

public:
    Game();

    /**
     * @brief Initializes a game based on supplied setters.
     * 
     * One main responsibility of this method is to create orders and shipments based on the order delay. For example, if the orderDelay is 2 weeks, orders and shipments for 
     * two weeks should be created. These values are either set by default or accessed using instructor. However, as of Sprint2, the functionality 
     * for instructor to enter these values does not exist
     */
    void initGame();

    /**
     * @brief This method is called by the instructor to start the game
     * 
     * Basically when this function is called, it starts executing orders and shipments for the 1st week
     */
    void startGame();

    /**
     * @brief Takes the order vector for the current week based on currentWeek proerty. Then loops through the vector and 
     * executes the orders by calling order.executeEvent() 
     */
    void executeOrdersForCurrentWeek();

    /**
     * @brief Takes the shipment vector for the current week based on currentWeek proerty. Then loops through the vector and 
     * executes the shipments by calling shipment.executeEvent() 
     */
    void executeShipmentsForCurrentWeek();

    /**
     * @brief This method was listed in the initial documentation, but has been deprecated
     * 
     * @deprecated
     */
    void updatePlayerInventories();

    /**
     * @brief For the current week return the consumer order.
     * 
     * The values for consumer order are set by default. These values can be overriden by values provided by the instructor. However, as of Sprint2 
     * this functionality in instructor does not exist
     * 
     * @return Consumer order for the current week.
     * 
     */
    int getConsumerOrderForWeek();

    /**
    * @brief Call executeOrderForCurrentWeek() and executeShipmentForCurrentWeek()
    */
    int advanceWeek();

    /**
     * @brief Add the parameter to the vector of orders
     * 
     * The order contains a property that says in which week it is going to be executed. Using this property, the order is placed in 
     * ordertoBeExecuted vector's correct location
     * 
     * @param order The order object that is to be added to ordersToBeExecuted
     */
    void addOrder(int numberOfBeers, int role);

    /**
     * @brief Add the parameter to the vector of shipments
     * 
     * The shipment contains a property that says in which week it is going to be executed. Using this property, the shipment is placed in 
     * shipmentsToBeExecuted vector's correct location
     * 
     * @param order The shipment object that is to be added to shipmentsToBeExecuted
     */
    void addShipment(int numberOfBeers, int role);

    /**
     * @brief Adds a player pointer to the list of player
     * 
     * Note that the order of addition matters. The order should be from downstream to upstream.
     */
    void addPlayerInterface(PlayerInterface* player);

    /**
     * @brief Returns the pointer to the downstream player for the player whose role is 'role'
     */
    PlayerInterface* getDownstream(int role);

    /**
     * @brief Returns the pointer to the upstream player for the player whose role is 'role'
     */
    PlayerInterface* getUpstream(int role);

    bool isGamePlayable();

    //////
    /// Setters
    //////

    /**
     * @brief Setter Method for the game's Id
     * @param int The games's Id
     */
    void setGId(int gId);
    
    /**
     * @brief Setter Method for the game's total weeks to be played
     * @param int The total number of weeks the game is going to be played
     */
    void setWeeksToBePlayed(int w);
    
    /**
     * @brief Setter Method for the game's info code
     * @param int Game's info code 
     */
    void setInfoCode(int code);
    
    /**
     * @brief Setter Method for the game's backorder cost
     * @param double Game's backorder cost
     */
    void setBackorderCost(double cost);
    
    /**
     * @brief Setter Method for the game's holding cost
     * @param double Game's  holding cost
     */
    void setHoldingCost(double hc);
    
    /**
     * @brief Setter Method for the Game's Factory Delay
     * @param int Game's Factory Delay
     */
    void setFactoryDelay(int);
    
    /**
     * @brief Setter Method for the Game's Order Delay
     * @param int Game's Order Delay
     */
    void setOrderDelay(int);
    
    /**
     * @brief Setter Method for the Game's Starting Inventory
     * @param int Game's  Starting Inventory
     */
    void setStartingInventory(int si);
    
    /**
     * @brief Setter Method for the game's current week
     * @param int Current Game week
     */
    void setCurrentWeek(int week);
    
    /**
     * @brief Setter Method for the game's Shipment Delay
     * @param int Game's  Shipment Delay
     */
    void setShipmentDelay(int);

    //////
    /// Getters
    //////
        
    /**
     * @brief Getter Method for the game's Id
     * @return int The games's Id
     */
    int getGId();
    
    /**
     * @brief Getter Method for the game's total weeks to be played
     * @return int The total number of weeks the game is going to be played
     */
    int getWeeksToBePlayed();
    
    /**
     * @brief Getter Method for the game's info code
     * @return int Game's info code 
     */
    int getInfoCode();
    
    /**
     * @brief Getter Method for the game's backorder cost
     * @return double Game's backorder cost
     */
    double getBackorderCost();
    
    /**
     * @brief Getter Method for the game's holding cost
     * @return double Game's  holding cost
     */
    double getHoldingCost();
    
    /**
     * @brief Getter Method for the Game's Factory Delay
     * @return int Game's Factory Delay
     */
    int getFactoryDelay();
    
    /**
     * @brief Getter Method for the Game's Order Delay
     * @return int Game's Order Delay
     */
    int getOrderDelay();
    
    /**
     * @brief Getter Method for the Game's Starting Inventory
     * @return int Game's  Starting Inventory
     */
    int getStartingInventory();
    
    /**
     * @brief Getter Method for the game's current week
     * @return int Current Game week
     */
    int getCurrentWeek();
    
    /**
     * @brief Getter Method for the game's Shipment Delay
     * @return int Game's  Shipment Delay
     */
    int getShipmentDelay();

    /// 
    // For test cases
    ///

    /**
     * @brief Setter Method for the game's order delay
     * @param int Game's order delay
     */
    void setOrderTimeDelay(int i) {setOrderDelay(i);};
    
    /**
     * @brief Getter Method for the game's order delay
     * @return int Game's order delay
     */
    int getOrderTimeDelay() {return orderDelay;}

    /**
     * @brief Setter Method for the game's Instructor Id
     * @param int Game's creator (instructor) id 
     */
    void setInstrId(int id) {this->instrid = id;};   
    
    /**
     * @brief Setter Method for the game's Factory Player Id
     * @param int Game's factory player id 
     */
    void setPFactId(int id) {
        this->pFactId = id;
        if(this->pFactId != 0){
            this->rolesTaken[3]=true;
        }
    };

    /**
     * @brief Setter Method for the game's Distributor Player Id
     * @param int Game's Distributor player id 
     */
    void setPDistributorId(int id) {
        this->pDistributorId = id;
        if(this->pDistributorId != 0){
            this->rolesTaken[2]=true;
        }
    };

    /**
     * @brief Setter Method for the game's Wholesaler Player Id
     * @param int Game's Wholesaler player id 
     */
    void setPWholesalerId(int id) {
        this->pWholesalerId = id;
        if(this->pWholesalerId != 0){
            this->rolesTaken[1]=true;
        }
    };

    /**
     * @brief Setter Method for the game's Retailer Player Id
     * @param int Game's Retailer player id 
     */
    void setPRetailerId(int id) {
        this->pRetailerId = id;
        if(this->pRetailerId != 0){
            this->rolesTaken[0]=true;
        }
    };

    /**
     * @brief Getter Method for the game's Instructor Player Id
     * @return int Game's Instructor player id 
     */
    int getInstrId() {return this->instrid;};
    
    /**
     * @brief Getter Method for the game's Factory Player Id
     * @return int Game's Factory player id 
     */
    int getPFactId() {return this->pFactId;};
    
    /**
     * @brief Getter Method for the game's Distributor Player Id
     * @return int Game's Distributor player id 
     */
    
    int getPDistributorId() {return this->pDistributorId;};

    /**
     * @brief Getter Method for the game's Wholesaler Player Id
     * @return int Game's Wholesaler player id 
     */
    int getPWholesalerId() {return this->pWholesalerId;};
    
    /**
     * @brief Getter Method for the game's Retailer Player Id
     * @return int Game's Retailer player id 
     */
    int getPRetailerId() {return this->pRetailerId;};

    /**
     * @brief Method to create the player passwords
     * @return vector<string> The password for game players  
     */
    std::vector<std::string> generatePasswords();

    /**
     * @brief Getter Method for the player Interfaces
     * @return value The vector of Player Interfaces
     */
    std::vector<PlayerInterface *> getPlayers() const;
    
    /**
     * @brief Setter Method for the Player Interfaces
     * @param value The vector of Player Interfaces
     */
    void setPlayers(const std::vector<PlayerInterface *> &value);

    /**
     * @brief Setter Method for the Player Interface
     * @param value The Player Interface
     */
    void setPlayerInterface(PlayerInterface *value, int player_number);
    /**
     * @brief Setter Method for the Player Interface
     * @return value The Player Interface
     */
    PlayerInterface * getPlayerInterface(int player_number);
    
    /**
     * @brief Getter Method for the roles that are occupied in the game
     * @return vector<bool*> The roles that are occupied in the game
     */
    std::vector<bool> getRolesTaken() const;
    
    /**
     * @brief Setter Method for the roles that are occupied in the game
     * @param value The roles that are occupied in the game
     */
    void setRolesTaken(const std::vector<bool> &value);
    
    std::vector<int> getDemandPerWeek() const;
    void setDemandPerWeek(const std::vector<int> &value);
    
    /**
     * @brief Getter Method for game's orders to be executed    
     */
    std::map<int, std::vector<Order> > getOrdersToBeExecuted() const;
    /**
     * @brief Setter Method for game's orders to be executed
     * @param value orders to be executed
     */
    void setOrdersToBeExecuted(const std::map<int, std::vector<Order> > &value);

    /**
     * @brief Getter Method for game's Shipment to be executed    
     */
    std::map<int, std::vector<Shipment> > getShipmentsToBeExecuted() const;
    
    /**
     * @brief Setter Method for game's Shipment to be executed
     * @param value Shipment to be executed
     */
    void setShipmentsToBeExecuted(const std::map<int, std::vector<Shipment> > &value);
};

#endif //GAME_H
