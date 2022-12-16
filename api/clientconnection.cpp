#include "clientconnection.h"

clientConnection::clientConnection(QTcpSocket *socket, QObject *parent)
    : QObject{parent},
      m_socket(socket)
{
    QObject::connect(m_socket.get(),&QAbstractSocket::disconnected,this,&QObject::deleteLater);
    QObject::connect(m_socket.get(),&QIODevice::readyRead,this,&clientConnection::readyRead);
}

void clientConnection::SetRespond(QString msg)
{
    QByteArray tmp = QByteArray::fromStdString(msg.toStdString());
    RespondMessage = tmp;
}

void clientConnection::readyRead()
{
    while (m_socket->canReadLine())
    {

        const auto line = m_socket->readLine();
        QString str =QString::fromStdString(line.toStdString());
        qDebug()<<line;
        if(line =="\r\n")
        {
            m_socket->write("HTTP/1.1 200 ok\r\n");
            m_socket->write("Connection: keep-alive\r\n");
            m_socket->write("Content-Lenght: 255\r\n");
            m_socket->write("\r\n");
            m_socket->write(RespondMessage);

        }

    }
     m_socket->close();
}

clientConnection::~clientConnection()=default;
