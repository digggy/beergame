#include <QTcpSocket>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

#include <iostream>

#include "playerinterfaceserver.h"
#include "../playerinterface.h"

PlayerInterfaceServer::PlayerInterfaceServer(QWidget *parent) :
    PlayerInterface(parent),
    m_playerSocket(new QTcpSocket)
{
    connect(m_playerSocket, &QTcpSocket::readyRead, this, &PlayerInterfaceServer::receiveJson);
    connect(m_playerSocket, &QTcpSocket::disconnected, this, &PlayerInterfaceServer::disconnectFromPlayer);
    connect(m_playerSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &PlayerInterfaceServer::error);
}

void PlayerInterfaceServer::receiveJson()
{
    QByteArray jsonData;
    QDataStream socketStream(m_playerSocket);
//    socketStream.setVersion(QDataStream::Qt_5_14);
    for (;;) {
        socketStream.startTransaction();
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                if (jsonDoc.isObject()) {
                    emit jsonReceived(jsonDoc.object());
                }
                else
                    emit logMessagePlayer("Invalid message: " + QString::fromUtf8(jsonData));
            } else {
                emit logMessagePlayer("Invalid message: " + QString::fromUtf8(jsonData));
            }
        } else {
            break;
        }
    }
}

void PlayerInterfaceServer::sendJson(const QJsonObject &json)
{
    const QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);
    emit logMessagePlayer("Sending to " + QString::number(getRole()) + " - " + QString::fromUtf8(jsonData));
    QDataStream socketStream(m_playerSocket);
//    socketStream.setVersion(QDataStream::Qt_5_14);
    socketStream << jsonData;
}


bool PlayerInterfaceServer::setSocketDescriptor(qintptr socketDescriptor) {
    return m_playerSocket->setSocketDescriptor(socketDescriptor);
}

void PlayerInterfaceServer::disconnectFromPlayer() {
    m_playerSocket->disconnectFromHost();
    emit logMessagePlayer("Client disconnected");
}

void PlayerInterfaceServer::updateUi() {
    QJsonArray data;
    QJsonObject updateUiMessage;
    QJsonObject tempMessage;

    tempMessage["data"] = "inventory";
    tempMessage["value"] = std::to_string(player->getOldInventory()).c_str();
    data.append(tempMessage);
    tempMessage["data"] = "backlog";
    tempMessage["value"] = std::to_string(player->getOldBackOrder()).c_str();
    data.append(tempMessage);

    tempMessage["data"] = "inventoryafter";
    tempMessage["value"] = std::to_string(player->getInventory()).c_str();
    data.append(tempMessage);
    tempMessage["data"] = "backlogafter";
    tempMessage["value"] = std::to_string(player->getBackorder()).c_str();
    data.append(tempMessage);

    tempMessage["data"] = "incomingorder";
    tempMessage["value"] = std::to_string(player->getDemand()).c_str();
    data.append(tempMessage);
    tempMessage["data"] = "incomingshipment";
    tempMessage["value"] = std::to_string(player->getIncomingShipment()).c_str();
    data.append(tempMessage);
    tempMessage["data"] = "outgoingshipment";
    tempMessage["value"] = std::to_string(player->getOutgoingShipment()).c_str();
    data.append(tempMessage);

    tempMessage["data"] = "totalcost";
    tempMessage["value"] = std::to_string(player->getTotalCost()).c_str();
    data.append(tempMessage);

    tempMessage["data"] = "week";
    tempMessage["value"] = std::to_string(game->getCurrentWeek()).c_str();
    data.append(tempMessage);

    // Statistics Data
    std::vector<int> orders = player->getOrderHistory();
    std::vector<int> incomingShipment = player->getIncomingShipmentHistory();
    std::vector<int> outgoingShipment= player->getOutgoingShipmentHistory();

    QJsonArray playerHistory;

    QJsonArray player_orders;
    for (int i = 0 ; i< (int) orders.size();i++){
        player_orders.push_back(orders[i]);
    }

    QJsonArray player_incomingShipment;
    for (int i = 1 ; i< (int) incomingShipment.size();i++){
        player_incomingShipment.push_back(incomingShipment[i]);
    }

    QJsonArray player_outgoingShipment;
    for (int i = 1 ; i< (int) outgoingShipment.size();i++){
        player_outgoingShipment.push_back(outgoingShipment[i]);
    }

    playerHistory.append(player_orders);
    playerHistory.append(player_incomingShipment);
    playerHistory.append(player_outgoingShipment);

    tempMessage["data"] = "history";
    tempMessage["value"] = playerHistory;
    data.append(tempMessage);

    updateUiMessage["data"] = data;
    updateUiMessage["type"] = "updateUi";

    sendJson(updateUiMessage);
}
