#include "playerevent.h"
#include "shipment.h"
#include "playerinterface.h"

Shipment::Shipment() : Shipment(0, 0, 0, NULL) {}

Shipment::Shipment(int eventId, int nBeers, int execInWeek, PlayerInterface* receiver) :
    PlayerEvent(eventId, nBeers, execInWeek, receiver)
{}

void Shipment::executeShipment() {
    receiver->receiveShipment(numberOfBeers);
}
