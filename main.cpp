// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QApplication>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QMessageBox>
#include "CustomTray.h"
// #include "CustomListener.h"

#include "WSServer.h"


#include "MediaObject.h"

using MediaMetaData = std::variant<Media::Music, Media::Series, Media::Movie>;
Q_DECLARE_METATYPE(MediaMetaData)




/*
 *
 *  TODO: write a small GUI ton configure which port to listen to and if we allow only from localhost or network as well
 *          JSON validator?
 *      Once project complete move cpp and headers to variables in CMakeLists
 *
 *
 *  Test using
 *  Install-Module WebSocket -Scope CurrentUser -Force
 *  Import-Module WebSocket -Force -PassThru
 *  $socketClient = Get-WebSocket -SocketUrl "ws://localhost:32322/"
 * $socketClient.Send("Hello WebSocket")
 * $socketClient | Receive-Job -Keep (pour lire la reponse du client renvoyé par client->sendTextMessage)
 *
 * */




int main(int argc, char *argv[])
{
    // Needed for  my qVariant to be able to work in signal and slots as a parameter
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



    //app.connect(&server, &WSServer::MessageReceivedFromClient, &app, [=](QWebSocket* client, QString message){ /*implement here if needed */});

    app.connect(&server, &WSServer::JsonReceivedFromClient,&app, [=](QWebSocket* client, const QByteArray & message){
        qDebug() << "Should we add error handling in the lambda?";

        // Construct the Media Object out of the json

        try{
            MediaObject * mediaObject = MediaObject::FromByteArray(message);
            mediaObject->deleteLater();

        }catch(std::exception &e){
            qDebug() << "forsenE.what() " << e.what();
        }




        // mark to delete when event loop is over


        //Convert to json document here and do some stuff with it?
        // Should it be its own class or what, i'm confused

    } );

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
