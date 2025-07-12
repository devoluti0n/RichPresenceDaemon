#include "MediaObject.h"

MediaObject::MediaObject(QObject *parent)
    : QObject{parent}
{}




// MediaObject::MediaObject(Media::Status status,
//                          std::variant<Media::Music,Media::Series,Media::Movie> metaData,
//                          quint16 whereAt,
//                          QObject *parent)
//     :   _status{status},
//         _metaData{metaData},
//         _whereAt{whereAt},
//         QObject{parent}
// {
//     qDebug() << "Media object constructed";
//     emit OnChange();

// }

QString Media::Music::ToString(){
    QString final = this->track + "(" + QString::number(duration) +") - " + this->artist + "\r\n\t" + this->album;
    return final;
}



MediaObject* MediaObject::GetInstance(QObject *parent){
    if (self == nullptr){
        self = new MediaObject(parent);
    }
    return self;
}

void MediaObject::SetMetadata(MediaMetaData newData){
    qDebug() << "Set Meta Data called";
    qDebug() <<   std::get<Media::Music>(newData).ToString();
    this->_metaData = newData;
    emit this->OnChange(newData);

}


MediaObject * MediaObject::FromByteArray(const QByteArray & jsonAsByteArray, QObject* parent){

    return MediaObject::FromJsonDocument(QJsonDocument::fromJson( jsonAsByteArray) );


}

// std::holds_alternative<int>(data)to check for int in data
// std::get<int>(data) to get the int struct if data is int.
//    Otherwise get exception std::bad_variant_access.

// Static Constructor Qt flavor using From (instead of using an actual contrustor)
MediaObject * MediaObject::FromJsonDocument(const QJsonDocument & document,QObject *parent){
    QJsonObject object= document.object();

    // TODO: turn that into a singleton

    // First use: construct and then set metadata
    // Other uses: set metadata
    // Emit in set meta data



    QStringList validVersions;
    validVersions << "1.0";


    QString version = "0";
    std::variant<Media::Music,Media::Series,Media::Movie> metaData;

    /*
     *
     * MUSIC:
     * {
     *
     *
        "version": 1.0,
        "music" : {

            "track": "Demons are a girl best friend",
            "artist": "Powerwolf",
            "album": "Sacrement Of Sin",
            "duration": 240,
            "year" : 2008
        }
     *
     *
     *  SERIES:
     *
     *  "version": 1.0,
     *  "series: {

            "episodeName": "haikkido",
            "show": "La casa de papel",
            "season":2,
            "episode": 1,
            "duration": 3450
        }

     *
     * MOVIE:
     *
     *  "version": 1.0,
     *  "movie: {
     *     "movieName": "the dark knight",
            "duration": 6400,
            "year": 2008
     *  }
     *
     *
     *
     *
     */




    try{
        QJsonValue versionValue = object.value("version");
        qDebug() << versionValue.toString();
        if (versionValue.isUndefined()) {
            throw std::runtime_error("Undefined version");
        }

         version = versionValue.toString();


        // Check if version is contained in validVersions
         if (!validVersions.contains(version))
            throw std::runtime_error("Wrong json version");

        if (version == "1.0"){
            const QString MUSIC = "music";
            const QString SERIES = "series";
            const QString MOVIE  = "movie";


            if (object.keys().contains(MUSIC)){
                qDebug() << "pagchopp";
                const QString   TRACK = "track",
                                ARTIST = "artist",
                                ALBUM = "album",
                                DURATION = "duration";

                QString track,artist,album;
                qint16 duration;

                const QJsonObject musicObject = object.value(MUSIC).toObject();
                Media::Music musicMetadata;
                QJsonValue temp; // very unlikely someone would happen to name their song like this
                temp = musicObject.value(TRACK);
                if (!temp.isUndefined()){
                    musicMetadata.track = temp.toString();
                }else{
                    throw std::runtime_error("No song found");
                }
                musicMetadata.artist   = musicObject.value(ARTIST).toString("Unknown Artist");
                musicMetadata.album    = musicObject.value(ALBUM).toString("Unknown Album");
                musicMetadata.duration = musicObject.value(DURATION).toInt(0);

                musicMetadata.duration = 322;
                metaData = musicMetadata;







            }else if (object.keys().contains(SERIES)){
                const QJsonObject seriesObject = object.value(SERIES).toObject();

            }else if (object.keys().contains(MOVIE)){
                const QJsonObject movieObject = object.value(MOVIE).toObject();

            }else{
                throw std::runtime_error("Wrong/empty media found");
            }


            MediaObject* mediaObject = MediaObject::GetInstance(parent);
            mediaObject->SetMetadata(metaData);
            return mediaObject;




        }



    }catch(std::exception & e){
        qDebug() << "error parsing json, discarding new metadata..";
        qDebug() << e.what() ;
        throw (e);

    }
    MediaObject * mediaObject = MediaObject::GetInstance();
    mediaObject->SetMetadata(metaData);


    return mediaObject;




}



// connect OnChange to an update on discord rich presence API
// https://discord.com/developers/docs/rich-presence/using-with-the-discord-social-sdk

// Periodically update the timer using a QTimer ?
