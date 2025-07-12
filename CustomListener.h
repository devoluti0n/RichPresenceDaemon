#ifndef CUSTOMLISTENER_H
#define CUSTOMLISTENER_H

#include <QObject>
#include <QtWebSockets/QWebSocket>



// Composition over inheritance
class CustomListener : public QObject
{
    Q_OBJECT
public:
    explicit CustomListener(const QUrl &url, QObject *parent = nullptr);

signals:
    void Closed();

private slots:
    void OnConnected();
    void OnTextMessageReceived(const QString &message);

private:
    QWebSocket _webSocket;
    QUrl _url;

signals:
};

#endif // CUSTOMLISTENER_H
