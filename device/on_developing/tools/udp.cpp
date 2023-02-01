#include "udp.h"



udp::udp(QString Address, int port): QObject()
{
    _port = port;
    _udp  = new QUdpSocket();
    QHostAddress *addr =new QHostAddress(Address);
    _udp->bind(*addr, port);
    QObject:: connect(_udp, &QUdpSocket::readyRead,this, &udp::recieve);
}

udp::udp(int port)
{
    _port = port;
    _udp  = new QUdpSocket();
    _udp->bind(QHostAddress::LocalHost, port);
    QObject:: connect(_udp, &QUdpSocket::readyRead,this, &udp::recieve);
}

void udp::send(QString Address,QByteArray data)
{
    QHostAddress addr(Address);
    _udp->writeDatagram(data,addr,_port);

}

void udp::send(QString Address, QString data)
{
    QHostAddress addr(Address);
    QByteArray _data;
    _data.append(data);
    _udp->writeDatagram(_data,addr,_port);
}

void udp::send(QString Address,char* data)
{
    QHostAddress addr(Address);
    int size=0;
    while (data[size] != NULL)
    {
         size++;
    }
    _udp->writeDatagram(data,size,addr,_port);
}

bool udp::Avilable()
{
    if(_udp->pendingDatagramSize()>0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

QByteArray udp::read()
{
    recieve();
    return Bdata;
}

QString udp::getSenderAddress()
{
    return senderAddrs;

}

void udp::recieve()
{

    Bdata.clear();
    Bdata.resize(_udp->pendingDatagramSize());
    quint16 port;
    haddr.clear();
    _udp->readDatagram(Bdata.data(),Bdata.size(),&haddr,&port);
    //dbg "address from udp tool is: " << haddr.toString();
    if( haddr.toString()!="")
    {
        senderAddrs= haddr.toString();
    }

}


