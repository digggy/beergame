#include "playerevent.h"
#include "order.h"
#include "playerinterface.h"

Order::Order() : Order(0, 0, 0, NULL) {}

Order::Order(int eventId, int nBeers, int execInWeek, PlayerInterface* receiver) :
    PlayerEvent(eventId, nBeers, execInWeek, receiver)
{}

void Order::executeOrder() {
    receiver->receiveOrder(numberOfBeers);
}
