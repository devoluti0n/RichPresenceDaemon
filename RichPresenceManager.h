#ifndef RICHPRESENCEMANAGER_H
#define RICHPRESENCEMANAGER_H

#include <QObject>

class RichPresenceManager : public QObject
{
    Q_OBJECT
public:
    explicit RichPresenceManager(QObject *parent = nullptr);

signals:
};

#endif // RICHPRESENCEMANAGER_H
