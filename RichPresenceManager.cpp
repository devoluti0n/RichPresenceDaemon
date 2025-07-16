#include "RichPresenceManager.h"

RichPresenceManager::RichPresenceManager(QObject *parent)
    : QObject{parent}
{

    client = std::make_shared<discordpp::Client>();
    qDebug() << SNOWFLAKE_APP_ID;
    client->SetApplicationId(SNOWFLAKE_APP_ID);

    client->AddLogCallback([=](auto message, auto severity) {
        qDebug() << "[" << QString::fromStdString(EnumToString(severity)) << "] " << QString::fromStdString(message);
    }, discordpp::LoggingSeverity::Info);

    client->SetStatusChangedCallback([](discordpp::Client::Status status, discordpp::Client::Error error, int32_t errorDetail) {
        qDebug() << "🔄 Status changed: " << QString::fromStdString(discordpp::Client::StatusToString(status));

        if (status == discordpp::Client::Status::Ready) {
            qDebug() << "✅ Client is ready! You can now call SDK functions.\n";
        } else if (error != discordpp::Client::Error::None) {
            qDebug() << "❌ Connection Error: " << QString::fromStdString(discordpp::Client::ErrorToString(error)) << " - Details: " << errorDetail;
        }
    });


    // Execute discord callbacks
    QTimer* timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, [&](){
        discordpp::RunCallbacks();

    });

    timer->start(10);



}


RichPresenceManager* RichPresenceManager::GetInstance(QObject* parent){
    if (self == nullptr){
        self = new RichPresenceManager(parent);
    }
    return self;

}

void RichPresenceManager::SetActivity(MediaMetaData metadata){



    discordpp::Activity activity;
    activity.SetType(discordpp::ActivityTypes::Playing);
    activity.SetDetails("Pompompom je descends gaiement");
    activity.SetState("pompompom niquer ta maaman");

    if (client != nullptr){
        // Update the presence
        client->UpdateRichPresence(activity, [=](discordpp::ClientResult result) {
            if (result.Successful()) {
                qDebug() << "✅ Rich presence updated!\n";
            }
        });
    }else{
        qDebug() << "Client is still nullptr in SetActivity();";
    }




}


// Create a new activity




