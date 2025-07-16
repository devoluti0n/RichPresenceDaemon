// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QApplication>
#include <ostream>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QMessageBox>
#include "CustomTray.h"
// #include "CustomListener.h"

#include "WSServer.h"


#include "MediaObject.h"

// #include "discordpp.h"
#include  "RichPresenceManager.h"

// Defines SNOWFLAKE_APP_ID
#include "Secrets.h"
#include <QTimer>





Q_DECLARE_METATYPE(Media::Music)
Q_DECLARE_METATYPE(Media::Series)
Q_DECLARE_METATYPE(Media::Movie)
Q_DECLARE_METATYPE(MediaMetaData)




int main(int argc, char *argv[])
{
    // Needed for  my qVariant to be able to work in signal and slots as a parameter

    qRegisterMetaType<Media::Music>("Media::Music");
    qRegisterMetaType<Media::Series>("Media::Series");
    qRegisterMetaType<Media::Movie>("Media::Movie");
    qRegisterMetaType<MediaMetaData>("MediaMetaData");

    QApplication app(argc, argv);
    // if (!QSystemTrayIcon::isSystemTrayAvailable()) {
    //     auto choice = QMessageBox::critical(nullptr, QObject::tr("Bite"),
    //                                         QObject::tr("I couldn't detect any system tray on this system."),
    //                                         QMessageBox::Close | QMessageBox::Ignore);
    //     if (choice == QMessageBox::Close)
    //         return 1;
    //     // Otherwise "lurk": if a system tray is started later, the icon will appear.
    // }
    // QApplication::setQuitOnLastWindowClosed(false);

    // Window window;
    CustomTray customTray;

    // connect OnExit to app close pog
    app.connect(&customTray, &CustomTray::OnExit,&app,[&](){
        // closing the servers and incoming connextion is handled by the destructor of WSServer
        // Which chould be called whenever WSServer is out of scope, that is, when main closes

        app.exit(0);
    });

    // customTray.SetNowPlaying(QString("Lose you Now - Lindsey Sterling & Mako"));


    // CustomListener listener(QUrl("ws://localhost:32322"),nullpttr);

//    customTray.show();

    WSServer server(32322,&app);

    // Declare it here to be able to connect it *before* it emits OnChange
    MediaObject * mediaObject = MediaObject::GetInstance(&app);
    RichPresenceManager* rpManager = RichPresenceManager::GetInstance(&app);


    app.connect(mediaObject, &MediaObject::OnChange,rpManager,&RichPresenceManager::SetActivity);

    app.connect(&server, &WSServer::JsonReceivedFromClient,&app, [&](QWebSocket* client, const QByteArray & message){
        qDebug() << "Should we add error handling in the lambda?";

        try{
            // Construct the Media Object out of the json
            mediaObject = MediaObject::FromByteArray(message);

        }catch(std::exception &e){
            qDebug() << "forsenE.what() " << e.what();
        }
    } );



    // Not sure if needed but better be safe than sorry

    // window.show();
    return app.exec();
}


#else
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString text("QSystemTrayIcon is not supported on this platform");

    QLabel *label = new QLabel(text);
    label->setWordWrap(true);

    label->show();
    qDebug() << text;

    app.exec();
}

#endif
