#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>
#include <memory>
#include <QTcpSocket>
#include <QDebug>

using namespace std;

class clientConnection : public QObject
{
    Q_OBJECT
public:
    explicit clientConnection(QTcpSocket *socket ,QObject *parent = nullptr);
    ~clientConnection() override;
     void SetRespond(QString msg);

private slots:
    void readyRead();
private:
    const std::unique_ptr<QTcpSocket> m_socket;
    QByteArray RespondMessage;

};



#endif // CLIENTCONNECTION_H
