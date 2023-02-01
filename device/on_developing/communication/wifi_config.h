#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <QObject>
#include <QDebug>
#include "tools/filebrowser.h"

//#define wifi_path     "/etc/wpa_supplicant/wpa_supplicant.conf"
#define wifi_path     "wpa_supplicant.conf"

class wifi_config : public QObject
{
    Q_OBJECT
public:
    explicit wifi_config(QObject *parent = nullptr);

public slots:
    void connect_wifiNetwork(QString ssid,QString psk);
private:
    QString standard_wifi_file;

};

#endif // WIFI_CONFIG_H
