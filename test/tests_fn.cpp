#include "gtest/gtest.h"
#include "../src/player.h"
#include "../src/playerinterface.h"
#include "../src/game.h"
#include "../src/instructor.h"
#include "../src/beergamewindow.h"

class BeerGameLogicTest : public ::testing::Test {
protected:
    BeerGameLogicTest() {}

    ~BeerGameLogicTest() {}

    void SetUp() override {
        char appName[] = {'t', 'e', 's', 't'};
        char* testArgV[] = {appName};
        int testArgC = 1;

        app = new QApplication(testArgC, testArgV);
        game = new Game();

        consumer = new Player(CONSUMER);
        retailer = new Player(RETAILER);
        wholesaler = new Player(WHOLESALER);
        distributor = new Player(DISTRIBUTOR);
        factory = new Player(FACTORY);

        consumerI = new PlayerInterface();
        retailerI = new PlayerInterface();
        wholesalerI = new PlayerInterface();
        distributorI = new PlayerInterface();
        factoryI = new PlayerInterface();

        consumer->setInterface(consumerI);
        consumerI->setGame(game);
        consumerI->setPlayer(consumer);

        retailer->setInterface(retailerI);
        retailerI->setGame(game);
        retailerI->setPlayer(retailer);

        wholesaler->setInterface(wholesalerI);
        wholesalerI->setGame(game);
        wholesalerI->setPlayer(wholesaler);

        distributor->setInterface(distributorI);
        distributorI->setGame(game);
        distributorI->setPlayer(distributor);

        factory->setInterface(factoryI);
        factoryI->setGame(game);
        factoryI->setPlayer(factory);

        game->addPlayerInterface(consumerI);
        game->addPlayerInterface(retailerI);
        game->addPlayerInterface(wholesalerI);
        game->addPlayerInterface(distributorI);
        game->addPlayerInterface(factoryI);
    }

    void TearDown() override {
        delete app;
        delete game;

        delete consumer;
        delete retailer;
        delete wholesaler;
        delete distributor;
        delete factory;

        delete consumerI;
        delete retailerI;
        delete wholesalerI;
        delete distributorI;
        delete factoryI;
    }

    QApplication* app;
    Game* game;
    Player *consumer, *retailer, *wholesaler, *distributor, *factory;
    PlayerInterface *consumerI, *retailerI, *wholesalerI, *distributorI, *factoryI;
};

// This tests whether the order placed by a player in the first week reaches the upstream in 3rd week
TEST_F(BeerGameLogicTest, orderReachesUpstreamTest) {
    // set game specific settings here
    // eg: game->setHoldingCost()..

    game->initGame();
    game->startGame();

    // Place an order of 6 in the first week. And check in third week if
    // the upstream receives this order
    retailerI->sendOrderToPlayer(6);
    wholesalerI->sendOrderToPlayer(6);
    distributorI->sendOrderToPlayer(6);
    factoryI->sendOrderToPlayer(6);

    // orders for 2nd week
    retailerI->sendOrderToPlayer(7);
    wholesalerI->sendOrderToPlayer(7);
    distributorI->sendOrderToPlayer(7);
    factoryI->sendOrderToPlayer(7);

    EXPECT_EQ(retailer->getDemand(), 6); // consumer by default orders 6 beers in 1st week
    EXPECT_EQ(wholesaler->getDemand(), 6);
    EXPECT_EQ(distributor->getDemand(), 6);
    EXPECT_EQ(factory->getDemand(), 6);
}

TEST_F(BeerGameLogicTest, shipmentReachesDownStream) {
    game->initGame();
    game->startGame();

    // store how many beers each player is sending to downstream in the first week
    int toConsumer = retailer->getOutgoingShipment();
    int toRetailer = wholesaler->getOutgoingShipment();
    int toWholesaler = distributor->getOutgoingShipment();
    int toDistributor = factory->getOutgoingShipment();
    // for factory shipment is demand
    int factoryOrder = 6;
    int toFactory = factoryOrder;

    // place orders for 1st and 2nd week
    retailerI->sendOrderToPlayer(6);
    wholesalerI->sendOrderToPlayer(6);
    distributorI->sendOrderToPlayer(6);
    factoryI->sendOrderToPlayer(factoryOrder);
    // orders for 2nd week
    retailerI->sendOrderToPlayer(7);
    wholesalerI->sendOrderToPlayer(7);
    distributorI->sendOrderToPlayer(7);
    factoryI->sendOrderToPlayer(7);

    // now in the third week, each players should get above mentioned shipmetns
    EXPECT_EQ(consumer->getIncomingShipment(), toConsumer);
    EXPECT_EQ(retailer->getIncomingShipment(), toRetailer);
    EXPECT_EQ(wholesaler->getIncomingShipment(), toWholesaler);
    EXPECT_EQ(distributor->getIncomingShipment(), toDistributor);
    EXPECT_EQ(factory->getIncomingShipment(), toFactory);
}
