#ifndef BATTERYMANAGER_H
#define BATTERYMANAGER_H

#include <QObject>
#include <QVariant>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QTimer>


#define ON   "true"
#define OFF  "false"

class BatteryManager : public QObject
{
    Q_OBJECT
public:
    typedef enum{full,empty,level3,level2,level1}BL_t;
    typedef enum{charging,discharging}Chrging_t;
    explicit BatteryManager(QObject *parent );

    void      SetBatteryLevel(BL_t battery_level);
    void      SetBatteryStatus(Chrging_t charge);
    BL_t      GetBatteryLevel();
    Chrging_t GetBatteryStatus();

    void BatteryGraphicTest();

private slots:
    void BatteryRender();
signals:

private:
  QObject *_full;
  QObject *_lvl3;
  QObject *_lvl2;
  QObject *_lvl1;
  QObject *_empty;
  QObject *_charging;

  BL_t      CurrLevel  = empty;
  Chrging_t CurrStatus = discharging;

   QTimer *bt;int tstv=0;

};

#endif // BATTERYMANAGER_H
