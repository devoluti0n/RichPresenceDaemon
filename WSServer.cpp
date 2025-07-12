#include "WSServer.h"
#include <QDebug>

WSServer::WSServer(quint16 port, QObject *parent)
    : QObject(parent),
    _server(new QWebSocketServer(QStringLiteral("Echo Server"),
                                  QWebSocketServer::NonSecureMode, this))
{
    if (_server->listen(QHostAddress::Any, port)) {
        qDebug() << "Serveur WebSocket en écoute sur le port" << port;
        connect(_server, &QWebSocketServer::newConnection,
                this, &WSServer::OnNewConnection);
        connect(_server, &QWebSocketServer::closed, this, &WSServer::closed);
    }
}

WSServer::~WSServer()
{
    _server->close();
    qDeleteAll(_clients);
}

void WSServer::OnNewConnection()
{
    // OnNewConnection add client to client list
    QWebSocket *clientSocket = _server->nextPendingConnection();
    connect(clientSocket, &QWebSocket::textMessageReceived,
            this, &WSServer::ProcessTextMessage);

    connect(clientSocket, &QWebSocket::binaryMessageReceived,this, &WSServer::ProcessByteArray);

    connect(clientSocket, &QWebSocket::disconnected,
            this, &WSServer::SocketDisconnected);
    _clients << clientSocket;
}

void WSServer::ProcessTextMessage(const QString & message)
{
    // get responsible object through QObject::sender()
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    // Make sure
    qDebug() << "Message reçu:" << message;

    emit TextMessageReceivedFromClient(client,message);
    // reply to client
    if (client){

        client->sendTextMessage(message);
        qDebug() << "replying to client";
    }
}

void WSServer::ProcessByteArray(const QByteArray &message){
    qDebug() << "Received ByteArray in WSServer::ProcessByteArray\r\nEmitting signal";
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    emit this->JsonReceivedFromClient(client,message);

}


void WSServer::SocketDisconnected()
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (client) {
        _clients.removeAll(client);
        client->deleteLater();
    }
}



