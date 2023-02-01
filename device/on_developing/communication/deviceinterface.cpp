#include "deviceinterface.h"

DeviceInterface::DeviceInterface(QObject *parent)
    : QObject{parent}
{
    SA = parent->findChild<QObject*>("device_addrs");

    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
         if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
         {
             myaddrs=address.toString();
             if(myaddrs!="")
             {
                 myaddrs+="     DEVICE ";
                 myaddrs+=DEVICE_ADDRESS;
                 SA->setProperty("text",myaddrs);
             }
             qDebug() << "your physical address is: " <<address.toString();
            // pageLink = address.toString()+":8080";
         }

     }


  // dbg adss;
    server=new udp(myaddrs,8084);
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(thread()));
    timer->setInterval(5);
    timer->start();

    rt=new QTimer(this);
    connect(rt, SIGNAL(timeout()), this, SLOT(get_cmd()));
    rt->setInterval(2);
    rt->start();

}

void DeviceInterface::set_spo2Engine(Spo2graph *engine)
{
    spo2_grf=engine;
}

void DeviceInterface::set_ecgEngine(EcgGraph *engine)
{
    ecg_grf=engine;
}

QString DeviceInterface::get_online()
{


    QString out;
    for(int i=0;i<onlineDevices.size();i++)
    {
        out+=onlineDevices.at(i);
        out+="#";
    }
    return out;
}

void DeviceInterface::thread()
{
    if(!StartStream)
    {
        if(validcmd==true)
        {
            validcmd=false;
            parse_cmd();
            excute_cmd();


        }
    }
    else
    {
        // i will stream for ever
        // get data from spo2 and ecg
        QString ir=QString::number(spo2_grf->getMax30102Values().ir);
        QString red=QString::number(spo2_grf->getMax30102Values().red);
        QString spo2=QString::number(spo2_grf->getMax30102Values().spo2);
        QString ecgAdc=QString::number(ecg_grf->getEcgAdc());

        QString cmd=MONITOR+" "+ir+" "+red+" "+ecgAdc;
        qDebug()<<"<Monitor cmd is:"<<cmd;
        custom_send(SenderAddress,cmd);

    }

}

void DeviceInterface::get_cmd()
{

    if(!StartStream)
    {
        QByteArray tmp =  server->read();
        SenderAddress  =  server->getSenderAddress();
        QString    raw=  QString::fromStdString(tmp.toStdString());
        if(raw.contains(SBYTE))
        {
          validcmd=true;
          rawcmd=raw;


        }
    }



}

void DeviceInterface::reconnect()
{

    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
         if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
         {
             myaddrs=address.toString();
             if(myaddrs!="")
             {
                 myaddrs+="     DEVICE ";
                 myaddrs+=DEVICE_ADDRESS;
                 SA->setProperty("text",myaddrs);
             }
             qDebug() << "your physical address is: " <<address.toString();

         }

     }


  // dbg adss;
    server=new udp(myaddrs,8084);
}



void DeviceInterface::parse_cmd()
{
   QStringList lst=rawcmd.split(" ");

   if(lst.size()>3)
   {

       deviceAddress=lst.at(1).toInt();
       device_cmd=lst.at(2);
       datasize=lst.at(3).toInt();
//       dbg "parse_cmd()=> device address:"<<deviceAddress;
//       dbg "parse_cmd()=> device command:"<<device_cmd;
//       dbg "parse_cmd()=> data size:"<<datasize;
       device_data.clear();
       if(datasize>0)
       {
           for(int i=4;i<lst.size();i++)
           {
               device_data<<lst.at(i);
           }
       }
//      dbg "parse_cmd()=> data :"<<device_data;

   }

   if(deviceAddress==255)
   {
       FromServer=true;
    qDebug()<<"command from server ...";
   }
   else
   {
       FromServer=false;
   }
}

void DeviceInterface::excute_cmd()
{
    if(device_cmd==WHO_ONLINE)
    {
//        qDebug()<<"command is:"<<I_AM_ONLINE;
//        qDebug()<<"server address is :"<<SenderAddress;
        custom_send(SenderAddress,I_AM_ONLINE);
        waitToConnect++;
        if((FromServer==true)&&(waitToConnect==1))
            StartStream=true;
    }


}

void DeviceInterface::custom_send(QString address, QString cmd)
{

    for(int i=0;i<20;i++)
    {
         server->send(address,cmd);
    }
}

void DeviceInterface::rst()
{
    device_cmd="";
    deviceAddress=1000;
    datasize=0;


}
