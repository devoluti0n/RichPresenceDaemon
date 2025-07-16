#ifndef MEDIAOBJECT_H
#define MEDIAOBJECT_H

#include <QObject>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>





namespace Media{
    enum Status{
        PLAYING,
        PAUSED,
        UNKNOWN
    };

    struct Music{
        QString track, album, artist;
        quint16 duration;
    };

    struct Series{
        // La case de papel: S02E03 - Haikiddo

        QString episodeName;
        QString show;
        quint16 season;
        qint16 episode; // use 0 for specials (like doctor who)
        // Duration expressed in seconds
        quint16 duration;
        QString ToString();
    };

    struct Movie{
        QString movieName, director;
        qint16 duration, year = 0;
        QString ToString();
    };





}


//required because of Q_DECLARE_METATYPE using     MediaMetaData
// as macro expansion would fail on the commas

// it is required when connected to a slot
using MediaMetaData = std::variant<Media::Music, Media::Series, Media::Movie>;
// https://discord.com/developers/docs/discord-social-sdk/getting-started/using-c++







class MediaObject : public QObject
{
    Q_OBJECT
public:

    static MediaObject* GetInstance(QObject *parent = nullptr);

    static MediaObject* FromJsonDocument(const QJsonDocument & JSonDocument,QObject *parent = nullptr);
    static MediaObject* FromByteArray(const QByteArray & JsonAsbyteArray,QObject *parent = nullptr);

    // void SetMetaData( std::variant<Media::Music,Media::Series,Media::Movie> metaData);

    MediaMetaData GetMetadata();

    /**
     * MediaObjects should not be cloneable.
     */
    MediaObject(MediaObject &other) = delete;
    /**
     * MediaObjects should not be assignable.
     */
    void operator=(const MediaObject &) = delete;



signals:
    void OnChange(const MediaMetaData & newData);
private:


    explicit MediaObject(QObject *parent = nullptr);

    inline static MediaObject * self = nullptr;


    // This one might be useful, idk.
    // explicit MediaObject(Media::Status status,
    //                      std::variant<Media::Music,Media::Series,Media::Movie> metaData,
    //                      quint16 whereAt = 0,
    //                      QObject *parent = nullptr);



    Media::Status _status = Media::Status::UNKNOWN;
    // media max length
    quint16 _length = 0;
    // where are we at
    quint16 _whereAt = 0;
    // The following line crashes despite the using
    // std::variant<Media::Music,Media::Series,Media::Movie>  _metaData;
    MediaMetaData _metaData;



public slots:
    void SetMetadata(MediaMetaData newData);



};

#endif // MEDIAOBJECT_H
