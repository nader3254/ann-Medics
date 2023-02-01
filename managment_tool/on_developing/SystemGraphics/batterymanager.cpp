#include "batterymanager.h"



BatteryManager::BatteryManager(QObject *parent)
{


    _full     = parent->findChild<QObject*>("full");
    _lvl3     = parent->findChild<QObject*>("lvl3");
    _lvl2     = parent->findChild<QObject*>("lvl2");
    _lvl1     = parent->findChild<QObject*>("lvl1");
    _empty    = parent->findChild<QObject*>("empty");
    _charging = parent->findChild<QObject*>("charging");

    bt=new QTimer(this);
    connect(bt, SIGNAL(timeout()), this, SLOT(BatteryRender()));
    bt->setInterval(1000);


}

void BatteryManager::SetBatteryLevel(BL_t battery_level)
{

    QString f="false";QString t="true";
    switch (battery_level) {
    case full:

          _full->setProperty("visible",t);
          _lvl1->setProperty("visible",f);
          _lvl2->setProperty("visible",f);
          _lvl3->setProperty("visible",f);
          _empty->setProperty("visible",f);
          CurrLevel=full;

        break;
    case level1:

          _full->setProperty("visible",f);
          _lvl1->setProperty("visible",t);
          _lvl2->setProperty("visible",f);
          _lvl3->setProperty("visible",f);
          _empty->setProperty("visible",f);
          CurrLevel=level1;

        break;
    case level2:
          _full->setProperty("visible",f);
          _lvl1->setProperty("visible",f);
          _lvl2->setProperty("visible",t);
          _lvl3->setProperty("visible",f);
          _empty->setProperty("visible",f);
          CurrLevel=level2;
        break;
    case level3:
          _full->setProperty("visible",f);
          _lvl1->setProperty("visible",f);
          _lvl2->setProperty("visible",f);
          _lvl3->setProperty("visible",t);
          _empty->setProperty("visible",f);
          CurrLevel=level3;

        break;
    case empty:
          _full->setProperty("visible",f);
          _lvl1->setProperty("visible",f);
          _lvl2->setProperty("visible",f);
          _lvl3->setProperty("visible",f);
          _empty->setProperty("visible",t);
          CurrLevel=empty;

        break;
    default:

        break;
    }
}

void BatteryManager::SetBatteryStatus(Chrging_t charge)
{
    QString f="false";QString t="true";
    switch (charge) {
    case charging:
         _charging->setProperty("visible",t);
         CurrStatus=charging;

        break;
    default:
        _charging->setProperty("visible",f);
        CurrStatus=discharging;

        break;
    }
}

BatteryManager::BL_t BatteryManager::GetBatteryLevel()
{
    return CurrLevel;
}

BatteryManager::Chrging_t BatteryManager::GetBatteryStatus()
{
    return CurrStatus;
}

void BatteryManager::BatteryGraphicTest()
{
     bt->start();
}

void BatteryManager::BatteryRender()
{
    if(CurrLevel==full)
    {
        SetBatteryLevel(empty);
    }
   if(CurrLevel==level3)
   {
       SetBatteryLevel(full);
   }
   if(CurrLevel==level2)
   {
       SetBatteryLevel(level3);
   }
   if(CurrLevel==level1)
   {
       SetBatteryLevel(level2);
   }
   if(CurrLevel==empty)
   {
       SetBatteryLevel(level1);
   }

   if(CurrStatus==charging)
   {
       SetBatteryStatus(discharging);
   }
   else
   {
       SetBatteryStatus(charging);
   }


}
