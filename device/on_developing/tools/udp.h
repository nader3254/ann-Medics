#ifndef UDP_H
#define UDP_H

#include <QUdpSocket>
#include <QObject>
#include <QDebug>

#define dbg   qDebug()<<
class udp : public QObject
{
    Q_OBJECT
public:
    udp(QString Address,int port);
    udp(int port);

    void send(QString Address,QByteArray data);
    void send(QString Address,QString data);
    void send(QString Address,char* data);

    bool Avilable();
    QByteArray read();
    QString getSenderAddress();

private slots:
    void recieve();



private:
    QUdpSocket *_udp;
    QByteArray  Bdata;
    QHostAddress haddr;
    QString senderAddrs;
    int _port;

};

#endif // UDP_H
