#ifndef WSSERVER_H
#define WSSERVER_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <QList>

class WSServer : public QObject
{
    Q_OBJECT
public:
    explicit WSServer(quint16 port, QObject *parent = nullptr);
    ~WSServer();

signals:
    void closed();
    void TextMessageReceivedFromClient(QWebSocket* client, QString message);
    void JsonReceivedFromClient(QWebSocket* client, const QByteArray & message);

private slots:
    void OnNewConnection();
    void ProcessTextMessage(const QString& message);
    void ProcessByteArray(const QByteArray &message);

    void SocketDisconnected();

private:
    QWebSocketServer* _server;
    QList<QWebSocket*> _clients;
};

#endif // WSSERVER_H
