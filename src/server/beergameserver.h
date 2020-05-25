#ifndef BEERGAMESERVER_H
#define BEERGAMESERVER_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QWidget>
#include <QObject>
#include <vector>

#include "../playerinterface.h"
#include "../player.h"
#include "../game.h"

#include "playerinterfaceserver.h"
#include "../instructorwindow.h"
#include "../ui_instructorwindow.h"

class PlayerInterfaceServer;
class Player;
class Game;

/**
 * \brief Responsible in creating a server for serving the beergame
 */


class BeerGameServer : public QTcpServer {
    Q_OBJECT
    Q_DISABLE_COPY(BeerGameServer)
    public:
        explicit BeerGameServer(QObject* parent = nullptr);

    Ui::InstructorWindow *getUi() const;
    void setUi(Ui::InstructorWindow *value);

protected:
    /**
    * @brief Adds the incoming connection to the server  
    * @param socketDescriptor The socket descriptor 
    */
    void incomingConnection(qintptr socketDescriptor) override;

    signals:
        void logMessageServer(const QString& msg);

    public slots:
        /**
        * @brief Method to stop the server  
        */
        void stopServer();
        /**
        * @brief Method to log the message for debugging  
        */        
        void displayLogMessage(const QString& msg);

    private slots:
        /**
        * @brief Method to stop the server  
        * @param sender Player Interface Server that sent the message/json
        * @param doc The message as json object
        */
        void receiveJson(PlayerInterfaceServer* sender, const QJsonObject& doc);
        /**
        * @brief Method to disconnect a playerinterfaceserver  
        * @param sender Player Interface Server that is disconnected
        */
        void playerDisconnected(PlayerInterfaceServer* sender);
        /**
        * @brief Method to show error for player interface  
        * @param sender Player Interface Server that has the error
        */
        void playerError(PlayerInterfaceServer* sender);

    private:
        /**
        * @brief Method to check the roles taken in a game hosted in server
        * @param game The game that the players are playing
        */
        void rolesTakenRefresh(Game* game);
        /**
        * @brief Method to stop the server  
        * @param destination Player Interface Server to send the message/json
        * @param message The message as json object
        */
        void sendJson(PlayerInterfaceServer* destination, const QJsonObject& message);
        /**
        * @brief Method the receives the json from new player interfaces
        * @param sender Player Interface Server that sent the message/json
        * @param doc The message as json object
        */
        void jsonFromLoggedOut(PlayerInterfaceServer* sender, const QJsonObject& doc);
        /**
        * @brief Method the receives the json from  player interfaces already connected to server
        * @param sender Player Interface Server that sent the message/json
        * @param doc The message as json object
        */        
        void jsonFromLoggedIn(PlayerInterfaceServer* sender, const QJsonObject& doc);

    private:
        QVector<PlayerInterfaceServer*> m_clients;
        QVector<Game*> m_games;
        Ui::InstructorWindow *ui;
//        std::vector<Game *>* m_games = new std::vector<Game*>(10);
};

#endif // BEERGAMESERVER_H
