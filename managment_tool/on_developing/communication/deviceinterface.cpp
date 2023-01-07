#include "deviceinterface.h"

DeviceInterface::DeviceInterface(QObject *parent)
    : QObject{parent}
{
    online_ui= parent->findChild<QObject*>("online_ui");
    monitor_ui= parent->findChild<QObject*>("monitor_ui");
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
         if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
         {
            myaddrs=address.toString();

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

    if(!deviceConnected)
    {
        // search the whole network
        QStringList lst= myaddrs.split(".");
        QString address;//="192.168.1."+QString::number(devorder);devorder++;
        for(int i=0;i<lst.size()-1;i++)
        {
            address+=lst.at(i);
            address+=".";
        }
        address+=QString::number(devorder);devorder++;
        qDebug()<<"device predicted address is:: "<<address;
        if(devorder>255)
        {
           devorder=2;
        }
        if(!address.contains(myaddrs))
              server->send(address,WHO_ONLINE);
    }
    if(validcmd==true)
    {
        qDebug()<<"valid cmd";
        validcmd=false;
        parse_cmd();
        excute_cmd();


    }
}

void DeviceInterface::get_cmd()
{

  QByteArray tmp=  server->read();
  QString    raw=  QString::fromStdString(tmp.toStdString());
  if(raw!="")
    qDebug()<<"raw cmd is:"<<raw;
  if(raw.contains(SBYTE))
  {
    qDebug()<<"contain start byte:";
    validcmd=true;
    rawcmd=raw;


  }


}

bool DeviceInterface::connect_device(QString adds)
{

    QString tmp=adds;
    tmp.replace("device ","");
    toConnAddress=tmp.toInt();
    dbg "connected to :"<<toConnAddress;
    // close online devices ui and go to minitoring ui
    if(toConnAddress>0)
    {
        deviceConnected=true;
        online_ui->setProperty("visible","false");
        monitor_ui->setProperty("visible","true");
        return true;
    }
    else
    {
        return false;
    }

}

void DeviceInterface::set_spo2Engine(Spo2graph *engine)
{
    spo2_grf=engine;

}

void DeviceInterface::parse_cmd()
{
   QStringList lst=rawcmd.split(" ");

   if(lst.size()>3)
   {

       deviceAddress=lst.at(1).toInt();
       device_cmd=lst.at(2);
       datasize=lst.at(3).toInt();
       dbg "parse_cmd()=> device address:"<<deviceAddress;
       dbg "parse_cmd()=> device command:"<<device_cmd;
       dbg "parse_cmd()=> data size:"<<datasize;
       device_data.clear();
       if(datasize>0)
       {
           for(int i=4;i<lst.size();i++)
           {
               device_data<<lst.at(i);
           }
       }
       dbg "parse_cmd()=> data :"<<device_data;

   }
}

void DeviceInterface::excute_cmd()
{
    if(device_cmd==I_AM_ONLINE)
    {
        if(!onlineDevices.contains("device "+QString::number(deviceAddress)))
                        onlineDevices<<"device "+QString::number(deviceAddress);
    }
    if(device_cmd==MONITOR)
    {
        if(deviceAddress==toConnAddress)
        {
            spo2_grf->set_red_ir(device_data.at(0).toLong(),device_data.at(1).toLong());
        }

    }


}

void DeviceInterface::rst()
{
    device_cmd="";
    deviceAddress=1000;
    datasize=0;


}
