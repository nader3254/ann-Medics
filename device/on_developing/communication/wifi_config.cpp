#include "wifi_config.h"

wifi_config::wifi_config(QObject *parent)
    : QObject{parent}
{
   standard_wifi_file="ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev\nupdate_config=1\ncountry=EG\nnetwork={\n          ssid=\"##SSID##\"\n          psk=\"##PASSWORD##\"\n}\n";
}


void wifi_config::connect_wifiNetwork(QString ssid, QString psk)
{
   //system("sudo rm /etc/wpa_supplicant/wpa_supplicant.conf");
//   qDebug()<<"ssid is:"<<ssid<<"password is:"<<psk;
   FileBrowser *fb=new FileBrowser(wifi_path);
   QString out=standard_wifi_file;
   out.replace("##SSID##",ssid);
   out.replace("##PASSWORD##",psk);
   fb->WriteFile(wifi_path,out);


   qDebug()<<"the new configuration";
   system("sudo cp wpa_supplicant.conf /etc/wpa_supplicant/");
   system("wpa_cli -i wlan0 reconfigure");
<<<<<<< HEAD
   system("sudo reboot ");
=======
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
   //system("sudo ip link set wlan0 up");


}
