#ifndef CUSTOMTRAY_H
#define CUSTOMTRAY_H

#include <QObject>
#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QDebug>

class CustomTray : public QWidget
{
    Q_OBJECT

    public:
        explicit CustomTray();

        void CreateTray();
    public slots:
        void SetNowPlaying(QString newText);

    private:
        // The Tray itself
        QSystemTrayIcon *trayIcon;
        QMenu *trayIconMenu;

        QAction *nowPlaying;
    signals:
        void OnExit();



signals:
};

#endif // CUSTOMTRAY_H
