#ifndef PLAYERINTERFACESERVER_H
#define PLAYERINTERFACESERVER_H

#include <QTcpSocket>
#include <QWidget>

#include "../playerinterface.h"
#include "../player.h"

class Player;
/**
 * @brief This class is PlayerInterfaceServer
 * 
*/
class PlayerInterfaceServer : public PlayerInterface {
    Q_OBJECT
    public:
    /**
    * @brief: PlayerInterfaceServer Constructor
    * @param parent
    */
        explicit PlayerInterfaceServer(QWidget* parent = nullptr);
    /**
     * @brief: setSocketDescriptor method
     * @param  socketDescriptor
    */
        virtual bool setSocketDescriptor(qintptr socketDescriptor);
    /**
     * @brief: method for sending Json data
     * @param  jsonData
    */
        void sendJson(const QJsonObject& jsonData);
     /**
     * @brief: setRole method
      * @param  role
     */
        void setRole(int role);
     /**
        *@brief: method for undating UI
     */
        void updateUi() override;

    signals:
        /**
         * @brief: jsonReceived method
         * @param jsonDoc
        */
        void jsonReceived(const QJsonObject& jsonDoc);
        /**
         * @brief: method for disconnection from Player
         */
        void disconnectedFromPlayer();
        /**
         * @brief: error method
        */
        void error();
        /**
         * @brief: logMessagePlayer method
         * @param msg
        */
        void logMessagePlayer(const QString& msg);

    public slots:
        /**
         * @brief: method for disconnecting from Player
        */
        void disconnectFromPlayer();

    private slots:
        /**
         * @brief: receiveJson method
        */
        void receiveJson();

    private:
        /**
         * @brief: private QTcpSocket* m_playerSocket
        */
        QTcpSocket* m_playerSocket;
};

#endif // PLAYERINTERFACESERVER_H
