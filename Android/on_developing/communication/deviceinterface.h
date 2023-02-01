#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H

#include <QTimer>
#include <QObject>
#include <QNetworkInterface>
#include "SystemGraphics/spo2graph.h"
<<<<<<< HEAD
#include "SystemGraphics/ecggraph.h"
#include "tools/udp.h"
#include <QThread>
=======
#include "tools/udp.h"
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813

#define SBYTE         "94"
#define WHO_ONLINE    ((QString)"94 255 1 0")


#define I_AM_ONLINE   "2"
#define MONITOR       "6"



class DeviceInterface : public QObject
{
    Q_OBJECT
public:
    explicit DeviceInterface(QObject *parent = nullptr);
    void set_spo2Engine(Spo2graph *engine);
<<<<<<< HEAD
    void set_ecgEngine(EcgGraph *engine);
=======
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813

public slots :
    QString  get_online();
    void     thread();
    void     get_cmd();
    bool     connect_device(QString adds);

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
    Spo2graph    *spo2_grf;
<<<<<<< HEAD
    EcgGraph     *ecg_grf;
=======
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
    QObject      *online_ui;
    QObject      *monitor_ui;



    void  parse_cmd();
    void  excute_cmd();
    void  rst();
};

#endif // DEVICEINTERFACE_H
