#ifndef DATABASECONTROL_H
#define DATABASECONTROL_H

#include <QtSql>
#include <qfileinfo>
#include <QStringList>
#include <QDebug>

class DatabaseControl
{
public:
    DatabaseControl();
    DatabaseControl(char* db_path);

    bool GetConnectionStatus();
    bool GetTransactionStatus();

    void UpdateTableRecord();
    QString     ReadFromTable(QString table , QString attribute ,int index);
    bool        ReadFromTable(QString table , QString attribute ,QString content);
    QStringList ReadFromTable(QString table , QString attribute);
private:
   QSqlDatabase SysDB;
   int LastIndex;
   bool ConnectionStatus;
   bool TransactionStatus;

};

#endif // DATABASECONTROL_H
