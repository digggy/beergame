#ifndef ORDER_H
#define ORDER_H

#include "playerevent.h"
#include "player.h"

class Player;

/**
 * @brief This is the class for Order
*/


class Order : public PlayerEvent {
public:
    Order();

    Order(int, int, int, PlayerInterface*);

    void executeOrder();
};


#endif //ORDER_H
