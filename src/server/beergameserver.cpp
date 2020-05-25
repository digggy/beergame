#include <iostream>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "beergameserver.h"
#include "playerinterfaceserver.h"

#include "../player.h"
#include "../game.h"
#include "../playerinterface.h"


BeerGameServer::BeerGameServer(QObject *parent) :
    QTcpServer(parent)
{
    std::cout << "Starting server" << std::endl;
    this->ui = nullptr;
    Game* game = new Game;
    Player* consumer = new Player(0);
    PlayerInterface* consumerI = new PlayerInterface;
    consumerI->setPlayer(consumer);
    consumerI->setGame(game);
    game->addPlayerInterface(consumerI);
    m_games.append(game);
}

void BeerGameServer::incomingConnection(qintptr socketDescriptor) {
    PlayerInterfaceServer* playerInterfaceServer = new PlayerInterfaceServer(nullptr);
    // try to bind the socket to the interface
    if(!playerInterfaceServer->setSocketDescriptor(socketDescriptor)) {
        playerInterfaceServer->deleteLater();
        return;
    }

    connect(playerInterfaceServer, &PlayerInterfaceServer::disconnectedFromPlayer,
            this, std::bind(&BeerGameServer::playerDisconnected, this, playerInterfaceServer));
    connect(playerInterfaceServer, &PlayerInterfaceServer::error,
            this, std::bind(&BeerGameServer::playerError, this, playerInterfaceServer));
    connect(playerInterfaceServer, &PlayerInterfaceServer::jsonReceived,
            this, std::bind(&BeerGameServer::receiveJson, this, playerInterfaceServer, std::placeholders::_1));
    connect(playerInterfaceServer, &PlayerInterfaceServer::logMessagePlayer,
            this, &BeerGameServer::displayLogMessage);
    connect(this, &BeerGameServer::logMessageServer,
            this, &BeerGameServer::displayLogMessage);

    std::cout << "HELLLO CLIENT" << std::endl;

    m_clients.append(playerInterfaceServer);
    emit logMessageServer(QStringLiteral("New client Connected"));

}

void BeerGameServer::rolesTakenRefresh(Game* game){
    // Roles taken
    QJsonObject takenRoles;
    takenRoles["type"] = QStringLiteral("login");
    takenRoles["success"] = false;
    std::vector<bool>rolesTaken = game->getRolesTaken();

    QJsonArray rolesBool;
    for (int i = 0 ; i< (int) rolesTaken.size();i++){
        bool current_bool = rolesTaken[i] ? true : false;
        rolesBool.push_back(current_bool);
    }
    takenRoles["takenRoles"] = rolesBool;

    if(ui!= nullptr){
        std::vector<bool> roles_occupied;
        foreach (const QJsonValue & v, rolesBool){
             roles_occupied.push_back(v.toBool());
        }
        if(roles_occupied[0]){
            ui->r_container->setEnabled(true);
        }

        if(roles_occupied[1]){
            ui->w_container->setEnabled(true);
        }

        if(roles_occupied[2]){
            ui->d_container->setEnabled(true);
        }

        if(roles_occupied[3]){
            ui->f_container->setEnabled(true);
        }
    }

    QVector<PlayerInterfaceServer*> my_clients = m_clients;

    for (auto s_client : m_clients){
        sendJson(s_client, takenRoles);
    }
}


void BeerGameServer::sendJson(PlayerInterfaceServer* destination, const QJsonObject& message)
{
    std::cout << "SendJson BeerGameServer" << std::endl;
    Q_ASSERT(destination);
    destination->sendJson(message);
}

void BeerGameServer::receiveJson(PlayerInterfaceServer* sender, const QJsonObject& doc)
{
    Q_ASSERT(sender);
    emit logMessageServer("JSON received " + QString::fromUtf8(QJsonDocument(doc).toJson()));
    if (sender->getRole() < 0)
        return jsonFromLoggedOut(sender, doc);

    jsonFromLoggedIn(sender, doc);
}

void BeerGameServer::jsonFromLoggedIn(PlayerInterfaceServer* sender, const QJsonObject &docObj) {
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) != 0)
        return;

    const QJsonValue nBeersVal = docObj.value(QLatin1String("numberOfBeers"));
    const int nBeers = nBeersVal.toInt();
    emit logMessageServer("ORDER: Player " + QString(sender->getRole()) + " placed " + QString(nBeers) + " orders.");

    sender->sendOrderToPlayer(nBeers);
}

Ui::InstructorWindow *BeerGameServer::getUi() const
{
    return ui;
}

void BeerGameServer::setUi(Ui::InstructorWindow *value)
{
    ui = value;
}

void BeerGameServer::jsonFromLoggedOut(PlayerInterfaceServer* sender, const QJsonObject &docObj) {
    emit logMessageServer("Request from logged out user");
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull())
        return;
    // process for game attribute
    const QJsonValue gameNumVal = docObj.value(QLatin1String("game"));
    if (gameNumVal.isNull())
        return;
    const int gameNumber = gameNumVal.toInt();

    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) == 0)
    {
        // process for role attribute
        const QJsonValue roleVal = docObj.value(QLatin1String("role"));
        if (roleVal.isNull())
            return;
        const int role = roleVal.toInt();
        if (role < 0)
            return;

        Game* game = (m_games)[gameNumber - 1];
        Player* player = new Player(role);
        switch (role){
            case 0 :
                std::cout << "Consumer Connected" << std::endl;
                break;
            case 1 :
            {
                if(game->getPRetailerId() == 0){
                    game->setPRetailerId(game->getGId()+1);
                }

                break;
            }
            case 2 :
            {
                if(game->getPWholesalerId() == 0){
                    game->setPWholesalerId(game->getGId()+2);
                }
                break;
            }
            case 3 :
            {
                if(game->getPDistributorId() == 0){
                    game->setPDistributorId(game->getGId()+3);
                }
                break;
            }
            case 4 :
            {
                if(game->getPFactId() == 0){
                    game->setPFactId(game->getGId()+4);
                }
                break;
            }
            default :
            std::cout << "Invalid player role" << std::endl;
        }

            sender->setPlayer(player);
            game->setPlayerInterface(sender,role);
//            sender->setGame(game);
//            game->addPlayerInterface(sender);

            QJsonObject successMessage;
            successMessage["type"] = QStringLiteral("login");
            successMessage["success"] = true;
            successMessage["playerName"] = QString::fromUtf8(PLAYER_NAMES[role].c_str());
            sendJson(sender, successMessage);

            //Refresh the roles taken
            rolesTakenRefresh(game);

            if((m_games)[gameNumber - 1]->isGamePlayable()) {
                (m_games)[gameNumber - 1]->initGame();
                (m_games)[gameNumber - 1]->startGame();
            }

    } else if (typeVal.toString().compare(QLatin1String("game-join"), Qt::CaseInsensitive) == 0) {
        Game* game = (m_games)[gameNumber - 1];
        sender->setGame(game);
        game->addPlayerInterface(sender);

        //Refresh the roles taken
        rolesTakenRefresh(game);
    } else {
        // Invalid json with key type
        return;
    }

}

void BeerGameServer::playerDisconnected(PlayerInterfaceServer *sender)
{
    m_clients.removeAll(sender);
    int playerRole = sender->getRole();
    if (playerRole >= 0) {
        QJsonObject disconnectedMessage;
        disconnectedMessage["type"] = QStringLiteral("playerDisconnected");
        disconnectedMessage["role"] = playerRole;
//        broadcast(disconnectedMessage, nullptr);
    }
    sender->deleteLater();
}

void BeerGameServer::playerError(PlayerInterfaceServer* sender)
{
    Q_UNUSED(sender)
    int playerRole= sender->getRole();
    emit logMessageServer("Error from " + QString::number(playerRole));
}

void BeerGameServer::stopServer() {
    for (PlayerInterfaceServer *worker : m_clients) {
        worker->disconnectFromPlayer();
    }
    close();
}

void BeerGameServer::displayLogMessage(const QString &msg) {
    std::cout << msg.toStdString() << std::endl;
}
