#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "webserver.h"
#include "jsonwriter.h"
#include "my_restAPI.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

     QObject *obj = engine.rootObjects()[0];
     QObject* serverLink = obj->findChild<QObject*>("serverLink");
     webServer WS;
     WS.start();
     JsonWriter *jw=new JsonWriter();
     jw->CreateJson();
     jw->AddKey_value("davice address",54);
     jw->AddKey_value("ecg",15800);
     jw->AddKey_value("ppg ir",148000);
     jw->AddKey_value("heart rate",68);
     jw->AddKey_value("spo2",96);
     QString json =jw->SaveJson();
     WS.SetPage(json);
     serverLink->setProperty("text",WS.getPageLink());

     RestAPI *api=new RestAPI(nullptr);


    return app.exec();
}
