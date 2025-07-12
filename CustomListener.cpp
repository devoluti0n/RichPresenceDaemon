#include "CustomListener.h"

#include <QDebug>

CustomListener::CustomListener(const QUrl &url, QObject *parent)
    : QObject(parent), _url(url)
{
    connect(&_webSocket, &QWebSocket::connected, this, &CustomListener::OnConnected);
    connect(&_webSocket, &QWebSocket::disconnected, this, &CustomListener::Closed);
    _webSocket.open(_url);
    qDebug() << "Opened websocket on url: " << url;

    connect(&_webSocket, &QWebSocket::errorOccurred, this, [](QAbstractSocket::SocketError error){
        qDebug() << "Erreur WebSocket:" << error;
    });

}

void CustomListener::OnConnected()
{
    qDebug() << "WebSocket connecté";
    connect(&_webSocket, &QWebSocket::textMessageReceived,
            this, &CustomListener::OnTextMessageReceived);
}

void CustomListener::OnTextMessageReceived(const QString &message)
{
    qDebug() << "Message reçu:" << message;
    // Traitement du message ici
}
