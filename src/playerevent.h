#include "player.h"

#ifndef _PLAYER_EVENT_H
#define _PLAYER_EVENT_H

class PlayerInterface;

/**
 * @brief This is the class for PlayerEvent
*/

class PlayerEvent {
protected:
    int eventId;
    int numberOfBeers;
    int orderedInWeek; // in which week is this event executed
    PlayerInterface* receiver = nullptr;

    // for test cases
    int shippedInWeek;
    int toPlayerId;
    int fromPlayerId;
    int gId;


public:
    PlayerEvent() {}

    PlayerEvent(int eventId, int numberOfBeers, int orderedInWeek, PlayerInterface* receiver) :
        eventId(eventId),
        numberOfBeers(numberOfBeers),
        orderedInWeek(orderedInWeek),
        receiver(receiver)
    {};

    int setEventId(int id) {
        this->eventId = id;
    }

    int getEventId() const {
        return eventId;
    };

    void setOrderedInWeek(int week) {
        this->orderedInWeek = week;
    };

    int getOrderedInWeek() const {
        return orderedInWeek;
    };

    void setNumberOfBeers(int numberOfBeers) {
        this->numberOfBeers = numberOfBeers;
    }

    int getNumberOfBeers() {
        return numberOfBeers;
    }

    // for the sake of test case
    void setFromPlayerId(int s) {
        this->fromPlayerId = s;
    }

    int getFromPlayerId() {
        return fromPlayerId;
    }

    void setToPlayerId(int s) {
        this->toPlayerId = s;
    }

    int getToPlayerId() {
        return toPlayerId;
    }

    void setShippedInWeek(int s) {
        this->shippedInWeek = s;
    }

    int getShippedInWeek() {
        return shippedInWeek;
    }

    void setGId(int g) {
        this->gId = g;
    }

    void setReceiver(PlayerInterface* pi) {
        this->receiver = pi;
    }

    PlayerInterface* getReceiver() {
        return receiver;
    }

    int getGId() {
        return gId;
    }

    void setOrderId(int id) {
        this->eventId = id;
    }

    int getOrderId() {
        return eventId;
    }
};

#endif
