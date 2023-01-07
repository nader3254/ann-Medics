#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H

#include <QTimer>
#include <QObject>
#include <QNetworkInterface>
#include "SystemGraphics/spo2graph.h"
#include "tools/udp.h"
#include <QVariant>


#define DEVICE_ADDRESS   ((QString)"1")
#define SBYTE            "94"
#define WHO_ONLINE       "1"
#define I_AM_ONLINE      ((QString)"94 ")+((QString)DEVICE_ADDRESS)+((QString)" 2 0")
#define MONITOR          ((QString)"94 ")+((QString)DEVICE_ADDRESS)+((QString)" 6 12")



class DeviceInterface : public QObject
{
    Q_OBJECT
public:
    explicit DeviceInterface(QObject *parent = nullptr);
    void set_spo2Engine(Spo2graph *engine);

public slots :
    QString  get_online();
    void     thread();
    void     get_cmd();
    void     reconnect();


private:
    udp          *server;
    QTimer       *timer;
    QTimer       *rt;
    QString      rawcmd;
    QString      myaddrs;
    bool         validcmd=false;
    bool         deviceConnected=false;

    QStringList  onlineDevices;
    QStringList  cmd_decoded;
    int          devorder=2;
    int          deviceAddress;
    int          toConnAddress;
    int          datasize;
    QString      device_cmd;
    QStringList  device_data;
    QString      SenderAddress;
    bool         FromServer;
    bool         StartStream=false;
    Spo2graph    *spo2_grf;
    int          waitToConnect=0;
    QObject* SA ;

    void  parse_cmd();
    void  excute_cmd();
    void  custom_send(QString address,QString cmd);
    void  rst();
};

#endif // DEVICEINTERFACE_H
