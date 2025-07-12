#include "CustomTray.h"

CustomTray::CustomTray()
    : QWidget{}
{

    this->CreateTray();
}



void CustomTray::CreateTray(){


    trayIconMenu = new QMenu(this);

    this->nowPlaying = new QAction("Waiting for media..");

    trayIconMenu->addAction(nowPlaying);

    trayIconMenu->addSeparator();
    trayIconMenu->addAction(tr("Quit"), [=]{
        emit this->OnExit();
    });

    // trayIconMenu->addAction(maximizeAction);
    // trayIconMenu->addAction(restoreAction);
    // trayIconMenu->addSeparator();
    // trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    qDebug() << "bite";
    this->setWindowIcon(QIcon::fromTheme(QIcon::ThemeIcon::Battery));
    trayIcon->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::Battery));
    trayIcon->setVisible(true);
        qDebug() << "bite";
}


void CustomTray::SetNowPlaying(QString newText){
    this->nowPlaying->setText(QString(newText));

}

// void CustomTray::AddNewPlayer();
