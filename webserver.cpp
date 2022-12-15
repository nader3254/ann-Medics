#include "webserver.h"

webServer::webServer(QObject *parent)
    : QObject{parent},
      m_server(std::make_unique<QTcpServer>())
{
    QObject::connect(m_server.get(),&QTcpServer::newConnection,this,&webServer::newConnection);
}

void webServer::newConnection()
{
        qDebug()<<"new connection request";
        const auto connection=m_server->nextPendingConnection();
        if(!connection)
            return;
       cc =  new clientConnection(connection);
        cc->SetRespond(page);
}

void webServer::start()
{
    m_server->listen(QHostAddress::Any,8080);


    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
        {
           // qDebug() << "your physical address is: " <<address.toString();
            pageLink = address.toString()+":8080";
        }

    }

    qDebug()<<"page link :: "<<pageLink;
}

void webServer::SetPage(QString msg)
{
    page = msg;
}

QString webServer::getPageLink()
{
    return pageLink;
}

webServer::~webServer()=default;
