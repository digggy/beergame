#include "playerclient.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <iostream>
PlayerClient::PlayerClient(QObject *parent)
    : QObject(parent)
    , m_clientSocket(new QTcpSocket(this))
    , m_loggedIn(false)
{
    // Forward the connected and disconnected signals
    connect(m_clientSocket, &QTcpSocket::connected, this, &PlayerClient::connected);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &PlayerClient::disconnected);
    // connect readyRead() to the slot that will take care of reading the data in
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &PlayerClient::onReadyRead);
    // Forward the error signal, QOverload is necessary as error() is overloaded, see the Qt docs
    //connect(m_clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &PlayerClient::error);
    // Reset the m_loggedIn variable when we disconnect. Since the operation is trivial we use a lambda instead of creating another slot
    connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});
}

void PlayerClient::joinGame(const int &GameId)
{
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) { // if the client is connected
        // create a QDataStream operating on the socket
        QDataStream clientStream(m_clientSocket);
        // set the version so that programs compiled with different versions of Qt can agree on how to serialise
        clientStream.setVersion(QDataStream::Qt_5_7);
        // Create the JSON we want to send
        QJsonObject message;
        QJsonObject message1;
        message["type"] = QStringLiteral("game-join");
        message["game"] = GameId;
        // send the JSON using QDataStream
        clientStream << QJsonDocument(message).toJson();
    }
}

void PlayerClient::login(const int& Gameid, const int& role)
{
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) { // if the client is connected
        // create a QDataStream operating on the socket
        QDataStream clientStream(m_clientSocket);
        // set the version so that programs compiled with different versions of Qt can agree on how to serialise
        clientStream.setVersion(QDataStream::Qt_5_7);
        // Create the JSON we want to send
        QJsonObject message;
        QJsonObject message1;
        message["type"] = QStringLiteral("login");
        message["role"] = role;
        message["game"] = Gameid;
        // send the JSON using QDataStream

        clientStream << QJsonDocument(message).toJson();
    }
}

void PlayerClient::sendMessage(const QString &text)
{
    if (text.isEmpty())
        return; // We don't send empty messages
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_clientSocket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message["type"] = QStringLiteral("message");
    message["numberOfBeers"] = text.toInt();
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
}

void PlayerClient::jsonReceived(const QJsonObject &docObj)
{
    std::cout<< QString(QJsonDocument(docObj).toJson(QJsonDocument::Compact)).toStdString() <<std::endl;
    // actions depend on the type of message
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return; // a message with no type was received so we just ignore it
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) == 0) { //It's a login message

    if (m_loggedIn)
        return; // if we are already logged in we ignore

        // the success field will contain the result of our attempt to login
        const QJsonValue resultVal = docObj.value(QLatin1String("success"));

        if (resultVal.isNull() || !resultVal.isBool())
            return; // the message had no success field so we ignore

        const bool loginSuccess = resultVal.toBool();

        if (loginSuccess) {
            // we logged in successfully and we notify it via the loggedIn signal
            playerName = docObj.value(QLatin1String("playerName")).toString();
            emit loggedIn();
            return;
        } else {
            QJsonArray takenRole = docObj[QLatin1String("takenRoles")].toArray();
            emit roleTaken(takenRole);
            return;
        }
        // the login attempt failed, we extract the reason of the failure from the JSON
        // and notify it via the loginError signal
        const QJsonValue reasonVal = docObj.value(QLatin1String("reason"));
        emit loginError(reasonVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("updateUi"), Qt::CaseInsensitive) == 0) { //It's a chat message
        // we extract the text field containing the chat text
        // we extract the sender field containing the username of the sender
        const QJsonArray senderVal = docObj["data"].toArray();
        for(QJsonValue x: senderVal){
            QJsonObject j = x.toObject();
            const QJsonValue value = j.value(QLatin1String("value"));
            const QJsonValue data = j.value(QLatin1String("data"));

            if(data != "history"){
                 emit messageReceived(value.toString(), data.toString());
            }else{
                QJsonArray value = j[QLatin1String("value")].toArray();
                emit setPlayerStatistics(value);
            }
        }
            return; // the sender field was invalid so we ignore
        // we notify a new message was received via the messageReceived signal

    } else if (typeVal.toString().compare(QLatin1String("newuser"), Qt::CaseInsensitive) == 0) { // A user joined the chat
        // we extract the username of the new user
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore
        // we notify of the new user via the userJoined signal
        emit userJoined(usernameVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("userdisconnected"), Qt::CaseInsensitive) == 0) { // A user left the chat
         // we extract the username of the new user
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore
        // we notify of the user disconnection the userLeft signal
        emit userLeft(usernameVal.toString());
    }
}
void PlayerClient::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}
void PlayerClient::connectToServer(const QHostAddress &address, quint16 port)
{
    m_clientSocket->connectToHost(address, port);
}

void PlayerClient::onReadyRead()
{
    // prepare a container to hold the UTF-8 encoded JSON we receive from the socket
    QByteArray jsonData;
    // create a QDataStream operating on the socket
    QDataStream socketStream(m_clientSocket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    socketStream.setVersion(QDataStream::Qt_5_7);
    // start an infinite loop
    int j = 0;
    for (;;) {
        // we start a transaction so we can revert to the previous state in case we try to read more data than is available on the socket
        socketStream.startTransaction();
        // we try to read the JSON data
        socketStream >> jsonData;
        std::cout<<j++<<std::endl;
        std::cout<<jsonData.toStdString()<<std::endl;
        if (socketStream.commitTransaction()) {
            // we successfully read some data
            // we now need to make sure it's in fact a valid JSON
            QJsonParseError parseError;
            // we try to create a json document with the data we received
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                // if the data was indeed valid JSON
                if (jsonDoc.isObject()) // and is a JSON object
                    jsonReceived(jsonDoc.object()); // parse the JSON
            }
            // loop and try to read more JSONs if they are available
        } else {
            // the read failed, the socket goes automatically back to the state it was in before the transaction started
            // we just exit the loop and wait for more data to become available
            break;
        }
    }
}
