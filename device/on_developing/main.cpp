#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQuickStyle>
#include <QQmlContext>


#include "./SystemGraphics/ecggraph.h"
#include "./SystemGraphics/spo2graph.h"
#include "./SystemGraphics/rrgraph.h"
#include "./SystemGraphics/batterymanager.h"
#include "./SystemGraphics/alltexts.h"
#include "tools/systemerrors.h"
#include "communication/deviceinterface.h"
#include "communication/wifi_config.h"

int main(int argc, char *argv[])
{

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    qmlRegisterType<EcgGraph>("ecg.graphics",1,0,"ECGGraph");    //take care
    qmlRegisterType<Spo2graph>("spo2.graphics",1,0,"SPO2Graph"); //take care
    qmlRegisterType<rrgraph>("rr.graphics",1,0,"RRGraph");       //take care

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    /***************************************************************/
        QObject *obj = engine.rootObjects()[0];                       //take care


      QObject *graph = obj->findChild<QObject*>("ecg_graph");
      EcgGraph *ecg_graphics_ptr= qobject_cast<EcgGraph*>(graph);
    /***************************************************************/
        QObject *obj2 = engine.rootObjects()[0];                       //take care
        QObject *graph2 = obj2->findChild<QObject*>("spo2_graph");
        Spo2graph *spo2_graphics_ptr= qobject_cast<Spo2graph*>(graph2);
   /***************************************************************/
        QObject *obj3 = engine.rootObjects()[0];                       //take care
        QObject *graph3 = obj3->findChild<QObject*>("rr_graph");
        Spo2graph *rr_graphics_ptr= qobject_cast<Spo2graph*>(graph3);
   /***************************************************************/
        BatteryManager *Bat = new BatteryManager(obj);
       //Bat->SetBatteryLevel(BatteryManager::level3); //for debugging
        Bat->BatteryGraphicTest();

        AllTexts *SystemValues =new AllTexts(obj);

        //SystemValues->AllTextTest();

        systemErrors *serror=new systemErrors(obj);
        engine.rootContext()->setContextProperty("system_errors",serror);
        spo2_graphics_ptr->setText(SystemValues);
        spo2_graphics_ptr->setSysERR(serror);

        QTimer t1; // i2=0;
        QObject::connect(&t1,&QTimer::timeout,[&]()
        {
            //qDebug()<<"inside";
            SystemValues->AllTextTest(spo2_graphics_ptr->isConnected());
        });
        t1.start(5);

        DeviceInterface *DI=new DeviceInterface(obj);
        DI->set_spo2Engine(spo2_graphics_ptr);
        engine.rootContext()->setContextProperty("deviceInterface",DI);

        wifi_config *wifi_t =new wifi_config();
        engine.rootContext()->setContextProperty("wifiConfig",wifi_t);

    return app.exec();
}
