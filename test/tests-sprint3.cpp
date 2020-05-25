#include "gtest/gtest.h"
#include "../src/player.h"
#include "../src/playerinterface.h"
#include "../src/game.h"
#include "../src/instructor.h"
#include "../src/playerevent.h"

/** Tests for class Player  **/

TEST(playerTest, setPIdTest) {
    Player p;
    p.setPId(1);
    EXPECT_EQ(p.getPId(), 1);
}

TEST(playerTest, getPIdTest) {
    Player p;
    p.setPId(1);
    EXPECT_EQ(p.getPId(), 1);
}

TEST(playerTest, setRoleTest) {
    Player p;
    p.setRole(1);
    EXPECT_EQ(p.getRole(), 1);
}

TEST(playerTest, getRoleTest) {
    Player p;
    p.setRole(1);
    EXPECT_EQ(p.getRole(), 1);
}

TEST(playerTest, getInventoryTest){
    Player p;
    p.setInventory(6);
    EXPECT_EQ(p.getInventory(), 6);
}

TEST(playerTest, setInventoryTest){
    Player p;
    p.setInventory(6);
    EXPECT_EQ(p.getInventory(), 6);
}

TEST(playerTest, getBackorderTest){
    Player p;
    p.setBackorder(6);
    EXPECT_EQ(p.getBackorder(), 6);
}

TEST(playerTest, setBackorderTest){
    Player p;
    p.setBackorder(6);
    EXPECT_EQ(p.getBackorder(), 6);
}

TEST(playerTest, setIncomingOrderTest){
    Player p;
    p.setDemand(6);
    EXPECT_EQ(p.getDemand(), 6);
}

TEST(playerTest, getIncomingOrderTest){
    Player p;
    p.setDemand(6);
    EXPECT_EQ(p.getDemand(), 6);
}

TEST(playerTest, setIncomingShipmentTest){
    Player p;
    p.setIncomingShipment(1);
    EXPECT_EQ(p.getIncomingShipment(), 1);
}

TEST(playerTest, getIncomingShipmentTest){
    Player p;
    p.setIncomingShipment(1);
    EXPECT_EQ(p.getIncomingShipment(), 1);
}

TEST(playerTest, setOutgoingShipmentTest){
    Player p;
    p.setOutgoingShipment(1);
    EXPECT_EQ(p.getOutgoingShipment(), 1);
}

TEST(playerTest, getOutgoingShipmentTest){
    Player p;
    p.setOutgoingShipment(1);
    EXPECT_EQ(p.getOutgoingShipment(), 1);
}

TEST(playerTest, getCostTest){
    Player p;
    p.setOutgoingShipment(1);
    EXPECT_EQ(p.getOutgoingShipment(), 1);

}

TEST(playerTest, setCostTest){
    Player p;
    p.setOutgoingShipment(1);
    EXPECT_EQ(p.getOutgoingShipment(), 1);
}

TEST(playerTest, getTotalCostTest){
    Player p;
    EXPECT_EQ(p.getTotalCost(), 0);
}

TEST(playerTest, setTotalCostTest){
    Player p;
    p.setTotalCost(3);
    EXPECT_EQ(p.getTotalCost(), 3);
}

TEST(playerTest, isOrderReceivedTest){
    Player p;
    p.receiveOrder(5);
    EXPECT_EQ(p.isOrderReceived(), true);
}

TEST(playerTest, setOrderReceivedTest){
    Player p;
    p.receiveOrder(5);
    EXPECT_EQ(p.isOrderReceived(), true);
}

TEST(playerTest, isShipmentReceivedTest){
    Player p;
    p.receiveShipment(5);
    EXPECT_EQ(p.isShipmentReceived(), true);
}

TEST(playerTest, setShipmentReceivedTest){
    Player p;
    p.receiveShipment(5);
    EXPECT_EQ(p.isShipmentReceived(), true);
}

TEST(playerTest, setOrderPlacedTest) {
    Player p;
    p.placeOrder(5);
    EXPECT_EQ(p.isOrderPlaced(), true);
}

TEST(playerTest, isOrderPlacedTest) {
    Player p;
    p.placeOrder(5);
    EXPECT_EQ(p.isOrderPlaced(), true);
}

TEST(playerTest, setShipmentPlacedTest) {
    Player p;
    p.placeShipment(5);
    EXPECT_EQ(p.isShipmentPlaced(), true);
}

TEST(playerTest, isShipmentPlacedTest) {
    Player p;
    p.placeShipment(5);
    EXPECT_EQ(p.isShipmentPlaced(), true);
}

TEST(playerTest, setDemandTest) {
   Player p;
   p.setDemand(6);
   EXPECT_EQ(p.getDemand(),6);
}

TEST(playerTest, getDemandTest) {
   Player p;
   p.setDemand(6);
   EXPECT_EQ(p.getDemand(),6);
}

TEST(playerTest, getGameTest) {
    char appName[] = {'t', 'e', 's', 't'};
    char* testArgV[] = {appName};
    int testArgC = 1;

    QApplication* app = new QApplication(testArgC, testArgV);
    PlayerInterface* pi = new PlayerInterface();
    Game* game = new Game();
    pi->setGame(game);
    EXPECT_EQ(pi->getGame(), game);

    delete pi;
    delete game;
    delete app;
}

TEST(playerTest, setGameTest) {
    char appName[] = {'t', 'e', 's', 't'};
    char* testArgV[] = {appName};
    int testArgC = 1;

    QApplication* app = new QApplication(testArgC, testArgV);
    PlayerInterface* pi = new PlayerInterface();
    Game* game = new Game();
    pi->setGame(game);
    EXPECT_EQ(pi->getGame(), game);

    delete pi;
    delete game;
    delete app;
}

//placeOrder should call Game's addOrder method
TEST(playerTest, placeOrderTest ) {

}

//placeOrder should call Game's addShipment method
TEST(playerTest, placeShipmentTest) {
    // part of functional test: tests_fn.cpp
}

//getAvailableShipment returns the number of beers that are available for shipment to the next Player
TEST(playerTest, getAvailableShipmentTest) {
    // part of functional test: tests_fn.cpp
}

TEST(playerTest, receiveShipmentTest){
    Player p;
    p.receiveShipment(1);
    EXPECT_EQ(p.isShipmentReceived(), true);
}

TEST(playerTest, receiveOrderTest){
    Player p;
    p.receiveOrder(1);
    EXPECT_EQ(p.isOrderReceived(), true);
}

TEST(playerTest, decreaseInventoryTest ) {
    Player p;
    p.setInventory(6);
    p.decreaseInventory(2);
    EXPECT_EQ(p.getInventory(), 4);
}

TEST(playerTest, increaseInventoryTest) {
    Player p;
    p.setInventory(6);
    p.increaseInventory(2);
    EXPECT_EQ(p.getInventory(), 8);
}


TEST(playerTest, getIncomingShipmentHistoryTest)
{

    Player p;
    std::vector<int> history = {1,2,3,4,5,6};
    p.setIncomingShipmentHistory(history);
    EXPECT_EQ(history, p.getIncomingShipmentHistory());
}

TEST(playerTest, setIncomingShipmentHistoryTest)
{

    Player p;
    std::vector<int> history = {1,2,3,4,5,6};
    p.setIncomingShipmentHistory(history);
    EXPECT_EQ(history, p.getIncomingShipmentHistory());
}


TEST(playerTest, getOutgoingShipmentHistoryTest)
{

    Player p;
    std::vector<int> history = {1,2,3,4,5,6};
    p.setOutgoingShipmentHistory(history);
    EXPECT_EQ(history, p.getOutgoingShipmentHistory());
}

TEST(playerTest, setOutgoingShipmentHistoryTest)
{

    Player p;
    std::vector<int> history = {1,2,3,4,5,6};
    p.setOutgoingShipmentHistory(history);
    EXPECT_EQ(history, p.getOutgoingShipmentHistory());
}


TEST(playerTest, getOrderHistoryTest)
{

    Player p;
    std::vector<int> history = {1,2,3,4,5,6};
    p.setOrderHistory(history);
    EXPECT_EQ(history, p.getOrderHistory());
}

TEST(playerTest, setOrderHistoryTest)
{

    Player p;
    std::vector<int> history = {1,2,3,4,5,6};
    p.setOrderHistory(history);
    EXPECT_EQ(history, p.getOrderHistory());
}


/** Tests for class Game **/


TEST(gameTest, setShipmentDelayTest) {

    Game g;
    g.setShipmentDelay(3);
    EXPECT_EQ(3, g.getShipmentDelay());
}

TEST(gameTest, getShipmentDelayTest) {

    Game g;
    g.setShipmentDelay(8);
    EXPECT_EQ(8, g.getShipmentDelay());
}

TEST(gameTest, setOrderDelayTest) {

    Game g;
    g.setOrderDelay(3);
    EXPECT_EQ(3, g.getOrderDelay());
}

TEST(gameTest, getOrderDelayTest) {

    Game g;
    g.setOrderDelay(10);
    EXPECT_EQ(10, g.getOrderDelay());
}


TEST(gameTest, setGIdTest){

    Game g;
    g.setGId(34);
    EXPECT_EQ(34, g.getGId());
}

TEST(gameTest, getGIdTest){

    Game g;
    g.setGId(6);
    EXPECT_EQ(6, g.getGId());
}

TEST(gameTest, setInstrIdTest){

    Game g;
    g.setInstrId(20);
    EXPECT_EQ(20, g.getInstrId());
}

TEST(gameTest, getInstrIdTest){

    Game g;
    g.setInstrId(2);
    EXPECT_EQ(2, g.getInstrId());
}

TEST(gameTest, setPFactIdTest){

    Game g;
    g.setPFactId(100);
    EXPECT_EQ(100, g.getPFactId());
}

TEST(gameTest, getPFactIdTest){

    Game g;
    g.setPFactId(1030);
    EXPECT_EQ(1030, g.getPFactId());
}

TEST(gameTest, getPDistributorIdTest){

    Game g;
    g.setPDistributorId(56);
    EXPECT_EQ(56, g.getPDistributorId());
}

TEST(gameTest, setPDistributorIdTest){

    Game g;
    g.setPDistributorId(45);
    EXPECT_EQ(45, g.getPDistributorId());
}

TEST(gameTest, getPWholesalerIdTest){

    Game g;
    g.setPWholesalerId(56);
    EXPECT_EQ(56, g.getPWholesalerId());
}

TEST(gameTest, setPWholesalerIdTest){

    Game g;
    g.setPWholesalerId(12);
    EXPECT_EQ(12, g.getPWholesalerId());
}

TEST(gameTest, setPRetailerIdTest){

    Game g;
    g.setPRetailerId(24);
    EXPECT_EQ(24, g.getPRetailerId());
}

TEST(gameTest, getPRetailerIdTest){

    Game g;
    g.setPRetailerId(24);
    EXPECT_EQ(24, g.getPRetailerId());
}

TEST(gamTest, getOrderTimeDelayTest){

    Game g;
    g.setOrderTimeDelay(3);
    EXPECT_EQ(3, g.getOrderTimeDelay());
}

TEST(gamTest, setOrderTimeDelayTest){

    Game g;
    g.setOrderTimeDelay(4);
    EXPECT_EQ(4, g.getOrderTimeDelay());
}

TEST(gameTest, advanceWeekTest){

    Game g;
    int currweek = g.getCurrentWeek();
    EXPECT_EQ(currweek+1, g.advanceWeek());
}

TEST(gameTest, setWeeksToBePlayedTest){

    Game g;
    g.setWeeksToBePlayed(2);
    EXPECT_EQ(2, g.getWeeksToBePlayed());
}

TEST(gameTest, getWeeksToBePlayedTest) {

    Game g;
    EXPECT_EQ(26, g.getWeeksToBePlayed()); //checking default value
    g.setWeeksToBePlayed(2);
    EXPECT_EQ(2, g.getWeeksToBePlayed());
}

TEST(gameTest, setInfoCodeTest){

    Game g;
    g.setInfoCode(3);
    EXPECT_EQ(3, g.getInfoCode());
}

TEST(gameTest, getInfoCodeTest) {

    Game g;
    g.setInfoCode(3);
    EXPECT_EQ(3, g.getInfoCode());
}

TEST(gameTest, setHoldingCostTest){

    Game g;
    g.setHoldingCost(6.3);
    EXPECT_EQ(6.3, g.getHoldingCost());
}

TEST(gameTest, getHoldingCostTest){

    Game g;
    EXPECT_EQ(0.5, g.getHoldingCost()); //checking default value
    g.setHoldingCost(9);
    EXPECT_EQ(9, g.getHoldingCost());
}

TEST(gameTest, setStartingInventoryTest){

    Game g;
    g.setStartingInventory(4);
    EXPECT_EQ(4, g.getStartingInventory());
}

TEST(gameTest, getStartingInventoryTest){

    Game g;
    EXPECT_EQ(12, g.getStartingInventory()); //checking default value
    g.setStartingInventory(14);
    EXPECT_EQ(14, g.getStartingInventory());
}

TEST(gameTest, getBackorderCostTest){

    Game g;
    g.setBackorderCost(5.7);
    EXPECT_EQ(5.7, g.getBackorderCost());
}

TEST(gameTest, getCurrentWeekTest) {

    Game g;
    EXPECT_EQ(0, g.getCurrentWeek()); //checking default value
    g.setCurrentWeek(5);
    EXPECT_EQ(5, g.getCurrentWeek());
}

TEST(gameTest, setCurrentWeekTest) {

    Game g;
    g.setCurrentWeek(1);
    EXPECT_EQ(1, g.getCurrentWeek());
}

TEST(gameTest, setOrdersToBeExecutedTest) {
    // part of functionality test in test/tests_fn.cpp
}

TEST(gameTest, getOrdersToBeExecutedTest) {
    // part of functionality test in test/tests_fn.cpp
}

TEST(gameTest, setShipmentsToBeExecutedTest) {
    // part of functionality test in test/tests_fn.cpp
}

TEST(gameTest, getShipmentsToBeExecutedTest) {
    // part of functionality test in test/tests_fn.cpp
}

TEST(gameTest, setPlayerInterfaceTest) {

}

TEST(gameTest, getPlayersTest) {
    // part of functionality test in test/tests_fn.cpp
}

TEST(gameTest, setConsumerDemandPerWeekTest) {
    // part of functionality test in test/tests_fn.cpp
}

TEST(gameTest, getConsumerDemandPerWeekTest) {
    Game g;
    std::vector<int> consumerDemandPerWeek = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    g.setDemandPerWeek(consumerDemandPerWeek);
    EXPECT_EQ(consumerDemandPerWeek, g.getDemandPerWeek());
}

TEST(gameTest, setConsumerDemandPerweekTest) {
    Game g;
    std::vector<int> consumerDemandPerWeek = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    g.setDemandPerWeek(consumerDemandPerWeek);
    EXPECT_EQ(consumerDemandPerWeek, g.getDemandPerWeek());
}

TEST(gameTest, setBackorderCostTest){
    Game game;
    game.setBackorderCost(1);
    EXPECT_EQ(game.getBackorderCost(), 1);
}

TEST(gameTest, setFactoryDelayTest){
    Game game;
    game.setFactoryDelay(1);
    EXPECT_EQ(game.getFactoryDelay(), 1);
}

TEST(gameTest, getFactoryDelayTest) {
    Game game;
    game.setFactoryDelay(1);
    EXPECT_EQ(game.getFactoryDelay(), 1);
}

TEST(gameTest, getRolesTakenTest) {
    Game game;
    std::vector<bool> rolesTaken = {false,false,false,false};
    game.setRolesTaken(rolesTaken);
    EXPECT_EQ(game.getRolesTaken(), rolesTaken);
}

TEST(gameTest, setRolesTakenTest) {
    Game game;
    std::vector<bool> rolesTaken = {false,false,false,false};
    game.setRolesTaken(rolesTaken);
    EXPECT_EQ(game.getRolesTaken(), rolesTaken);
}

TEST(gameTest, setNumberOfPlayersTest){
    // not implemented yet
}

TEST(gameTest, getNumberOfPlayersTest) {
    // not implemented yet
}

TEST(gameTest, startGameTest){
    // part of functionality test; tests_fn.cpp

}

//In executeOrdersForCurrentWeek, the Order objects in the map ordersToBeExecuted are executed (the method
// executeOrder for each object is called)
TEST(gameTest, executeOrdersForCurrentWeekTest){
    // part of functionality test in test/tests_fn.cpp
}

//In executeShipmentsForCurrentWeek, the Shipment objects in the map setShipmentsToBeExecuted are executed (the method
// executeShipment for each object is called)
TEST(gameTest, executeShipmentsForCurrentWeekTest){
    // part of functionality test in test/tests_fn.cpp
}

TEST(gameTest, updatePlayerInventoriesTest){
    // part of functionality test in test/tests_fn.cpp
}

TEST(gameTest, getConsumerOrderForWeekTest){
    Game g;
    g.startGame();
    EXPECT_EQ(g.getConsumerOrderForWeek(), 6); //defaultvalue
}

// In addOrder, an object of class Order is created and put into the map setOrdersToBeExecuted
TEST(gameTest, addOrderTest){
    // part of functionality test; tests_fn.cpp
}

// In addShipment, an object of class Shipment is created and put into the map setShipmentsToBeExecuted
TEST(gameTest, addShipmentTest){
    // part of functionality test; tests_fn.cpp
}

TEST(gameTest, addPlayerTest){
    // part of functionality test; tests_fn.cpp
}

TEST(gameTest, getDownstreamTest){
    // part of functionality test; tests_fn.cpp
}

TEST(gameTest, getUpstreamTest){
    // part of functionality test; tests_fn.cpp
}

/** Tests for class Instructor **/

TEST(instructorTest, setInstrEmailTest){

    Instructor i;
    i.setInstrEmail("hi.there@jacobs-university.de");
    EXPECT_EQ("hi.there@jacobs-university.de", i.getInstrEmail());
}

TEST(instructorTest, getInstrEmailTest){

  Instructor i;
  i.setInstrEmail("hi.again@jacobs-university.de");
  std::string email = "hi.again@jacobs-university.de";
  EXPECT_EQ( email, i.getInstrEmail());
}

TEST(instructorTest, setInstrPasswordTest){

    Instructor i;
    i.setInstrPassword("superstrongpassword");
    EXPECT_EQ("superstrongpassword", i.getInstrPassword());
}

TEST(instructorTest, getInstrPasswordTest){

  Instructor i;
  i.setInstrPassword("weakpassword");
  EXPECT_EQ("weakpassword", i.getInstrPassword());
}

TEST(instructorTest, setInstrIdTest){

  Instructor i;
  i.setInstrId(2020);
  EXPECT_EQ(2020, i.getInstrId());
}

TEST(instructorTest, getInstrIdTest){

  Instructor i;
  i.setInstrId(30);
  EXPECT_EQ(30, i.getInstrId());
}

TEST(instructorTest, setGamesTest){
    // not implemented yet
    // part of functionality tests: tests_fn.cpp
}

TEST(instructorTest, getGamesTest){
    // not implemented yet
}

TEST(instructorTest, showGamesStatusTest){
    // not implemented yet
    // part of functionality tests: tests_fn.cpp
}

TEST(instructorTest, createGameTest){
    // not implemented yet
    // part of functionality tests: tests_fn.cpp
}

TEST(instructorTest, createGamesTest){
    // not implemented yet
    // part of functionality tests: tests_fn.cpp
}


/** Tests for class PlayerEvent **/

TEST(playerEventTest, getEventIdTest){
    PlayerEvent ev;
    ev.setEventId(1);
    EXPECT_EQ(ev.getEventId(), 1);
}

TEST(playerEventTest, setEventIdTest){
    PlayerEvent ev;
    ev.setEventId(1);
    EXPECT_EQ(ev.getEventId(), 1);
}

TEST(playerEventTest, getGIdTest){
    PlayerEvent ev;
    ev.setGId(1);
    EXPECT_EQ(ev.getGId(), 1);
}

TEST(playerEventTest, setGIdTest){
    PlayerEvent ev;
    ev.setGId(1);
    EXPECT_EQ(ev.getGId(), 1);
}

TEST(playerEventTest, setNumberOfBeersTest){
    PlayerEvent ev;
    ev.setNumberOfBeers(1);
    EXPECT_EQ(ev.getNumberOfBeers(), 1);
}

TEST(playerEventTest, getNumberOfBeersTest){
    PlayerEvent ev;
    ev.setNumberOfBeers(1);
    EXPECT_EQ(ev.getNumberOfBeers(), 1);
}

TEST(playerEventTest, getOrderedInWeekTest){
    PlayerEvent ev;
    ev.setOrderedInWeek(1);
    EXPECT_EQ(ev.getOrderedInWeek(), 1);
}

TEST(playerEventTest, setOrderedInWeekTest){
    PlayerEvent ev;
    ev.setOrderedInWeek(1);
    EXPECT_EQ(ev.getOrderedInWeek(), 1);
}

TEST(playerEventTest, getShippedInWeekTest){
    PlayerEvent ev;
    ev.setShippedInWeek(1);
    EXPECT_EQ(ev.getShippedInWeek(), 1);
}

TEST(playerEventTest, setShippedInWeekTest){
    PlayerEvent ev;
    ev.setShippedInWeek(1);
    EXPECT_EQ(ev.getShippedInWeek(), 1);
}

TEST(playerEventTest, getReceiverTest){
    char appName[] = {'t', 'e', 's', 't'};
    char* testArgV[] = {appName};
    int testArgC = 1;

    QApplication* app = new QApplication(testArgC, testArgV);
    PlayerInterface* pi = new PlayerInterface();

    PlayerEvent ev;
    ev.setReceiver(pi);
    EXPECT_EQ(ev.getReceiver(), pi);

    delete pi;
    delete app;
}

TEST(playerEventTest, setReceiverTest){
    char appName[] = {'t', 'e', 's', 't'};
    char* testArgV[] = {appName};
    int testArgC = 1;

    QApplication* app = new QApplication(testArgC, testArgV);
    PlayerInterface* pi = new PlayerInterface();

    PlayerEvent ev;
    ev.setReceiver(pi);
    EXPECT_EQ(ev.getReceiver(), pi);

    delete pi;
    delete app;
}

TEST(playerEventTest, getToPlayerIdTest){
    PlayerEvent ev;
    ev.setToPlayerId(1);
    EXPECT_EQ(ev.getToPlayerId(), 1);
}

TEST(playerEventTest, setToPlayerIdTest){
    PlayerEvent ev;
    ev.setToPlayerId(1);
    EXPECT_EQ(ev.getToPlayerId(), 1);
}

TEST(playerEventTest, getFromPlayerIdTest){
    PlayerEvent ev;
    ev.setFromPlayerId(1);
    EXPECT_EQ(ev.getFromPlayerId(), 1);
}

TEST(playerEventTest, setFromPlayerIdTest){
    PlayerEvent ev;
    ev.setFromPlayerId(1);
    EXPECT_EQ(ev.getFromPlayerId(), 1);
}


/** Tests for class Shipment **/

TEST(shipmentTest, executeShipmentTest){
    // part of functionality tests: tests_fn.cpp
}


/** Tests for class Order **/

TEST(orderTest, executeOrderTest){
    // part of functionality tests: tests_fn.cpp
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
