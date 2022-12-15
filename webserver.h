#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QTcpServer>
#include <QObject>
#include <QDebug>
#include <QNetworkInterface>
#include "clientconnection.h"

using namespace std;

class webServer : public QObject
{
    Q_OBJECT
public:
    explicit webServer(QObject *parent = nullptr);
    ~webServer() override;
        void    start();
        void    SetPage(QString msg);
        QString getPageLink();
private slots:
    void newConnection();

private:
    std::unique_ptr<QTcpServer> m_server;
    clientConnection *cc;
    QString page;
    QString pageLink;
};

#endif // WEBSERVER_H
