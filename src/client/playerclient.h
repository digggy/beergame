#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H
#include <QDialog>
#include <QHostAddress>
#include <QTcpSocket>
/**
 * This class is resposnible for direct communication with the
 * server. It has a QTCpSocket variable responsible for sending
 * and receiving data from the server. It establishes connection with the
 * server, sends data to the server in JSON format, receives
 *
 */

/**
 * \brief This class is resposnible for direct communication with the server.
 */

class PlayerClient: public QObject
{
    Q_OBJECT
        Q_DISABLE_COPY(PlayerClient)
    public:
        explicit PlayerClient(QObject *parent = nullptr);
        QString playerName = "";
    public slots:
        /**
         * @brief Connects to the server given the IP address and the port number.
         * \param addres ip address of server
         * \param port port number
         */
        void connectToServer(const QHostAddress &address, quint16 port);
        /**
         * @brief Logs in to the game using valid game id
         * \param GameId id of the game to connect to
         */
        void joinGame(const int &GameId);
        /**
         * @brief Logs in to the game using valid game id and role
         * \param GameId id of the game to connect to
         * \param role  Game role
         */
        void login(const int &GameId, const int& role);
        /**
         * @brief send message to the server
         * sends message to the server in proper json format
         *
         */
        void sendMessage(const QString &text);
        /**
         * @brief disconnects from the host
         *
         */
        void disconnectFromHost();
    private slots:
        /**
         * @brief This function is called when the socket receives data. Calls the jsonReceived
         * method for every QJSonObject.
         *
         */
        void onReadyRead();
    signals:
        /**
         * @brief signals for different cases.
         *
         */

        void connected();
        void loggedIn();
        void roleTaken(QJsonArray& takenRole);
        void setPlayerStatistics(QJsonArray&);
        void loginError(const QString &reason);
        void disconnected();
        void messageReceived(const QString &sender, const QString &text);
        //void error(QAbstractSocket::SocketError socketError);
        void userJoined(const QString &username);
        void userLeft(const QString &username);
    private:
        QTcpSocket *m_clientSocket;
        bool m_loggedIn;
        void jsonReceived(const QJsonObject &doc);
};

#endif // PLAYERCLIENT_H
