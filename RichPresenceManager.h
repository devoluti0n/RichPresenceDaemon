#ifndef RICHPRESENCEMANAGER_H
#define RICHPRESENCEMANAGER_H


#include "discordpp.h"
#include <QTimer>

#include <QObject>
#include "MediaObject.h"
#include <QDebug>
// Defines SNOWFLAKE_APP_ID
#include "Secrets.h"


class RichPresenceManager : public QObject
{
    Q_OBJECT
public:
    static RichPresenceManager* GetInstance(QObject *parent = nullptr);


public slots:
    void SetActivity(MediaMetaData metadata);

private:
    static inline RichPresenceManager* self = nullptr;
    explicit RichPresenceManager(QObject *parent = nullptr);
    // Create our Discord Client
    std::shared_ptr<discordpp::Client> client = nullptr;


signals:
};

#endif // RICHPRESENCEMANAGER_H
