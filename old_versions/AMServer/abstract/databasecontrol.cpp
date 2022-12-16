#include "databasecontrol.h"



DatabaseControl::DatabaseControl()
{

}
DatabaseControl::DatabaseControl(char* db_path)
{
    SysDB = QSqlDatabase::addDatabase("QSQLITE");
    SysDB.setDatabaseName(db_path);

    if(!SysDB.open())
    {
        ConnectionStatus = false;

    }
    else
    {
        ConnectionStatus = true;
    }


}

bool DatabaseControl:: GetConnectionStatus()
{
    return ConnectionStatus;

}
bool DatabaseControl:: GetTransactionStatus()
{
    return TransactionStatus;
}


void DatabaseControl:: UpdateTableRecord()
{
    //to do
    //add data on attributes


    //https://doc.qt.io/qt-5/qsqlquery.html#first

    //https://doc.qt.io/qt-5/qsqlrecord.html#count
    //https://doc.qt.io/qt-5/qstringlist.html


}

// read specific attribute on record and fieled specified
QString DatabaseControl:: ReadFromTable(QString table , QString attribute ,int index)
{
    QSqlQuery query("SELECT * FROM "+ table);
    QSqlRecord rec = query.record();
    int nameCol = rec.indexOf(attribute); // index of the field "name"
    QString data;int x=1;

    while (query.first())
    {

        if(query.value(nameCol).toString() != NULL)
         {
            data += query.value(nameCol).toString(); // output first name
            data += "###";
            break;
         }
    }

    QString tmp="#RST#";
    while(1)
    {
        while (query.next())
        {
           // qDebug() << query.value(nameCol).toString(); // output all names
            if(query.value(nameCol).toString() != NULL)
            {
                  tmp = query.value(nameCol).toString(); // output next name
                  x++;
                break;
            }
         }
        if(tmp != "#RST#")
        {
            data+= tmp;
            data += "###";
            tmp="#RST#";

        }
        else
        {
            break;
        }
    }

    QStringList tmplst  = data.split("###");
    if(index > x)
    {
        return " invalid index ";
        TransactionStatus = false;

    }
    else
    {
      return tmplst.at(index).toLocal8Bit().constData();
      TransactionStatus = true;

    }

}

// check if the content available on table and fieled specified
bool DatabaseControl::ReadFromTable(QString table , QString attribute ,QString content)
{
    QStringList lst =ReadFromTable(table,attribute);
    bool val=false;
    for (int i = 0; i < lst.size(); ++i)
    {
        if(lst.at(i).toLocal8Bit().constData()==content)
        {
            val= true;
            break;
        }
        else
        {
            val=false;

        }
    }
    return val ;

}

// read all field at table
QStringList DatabaseControl:: ReadFromTable(QString table , QString attribute)
{
    QSqlQuery query("SELECT * FROM "+ table);
    QSqlRecord rec = query.record();
    int nameCol = rec.indexOf(attribute); // index of the field "name"
    QString data;

    while (query.first())
    {

        if(query.value(nameCol).toString() != NULL)
         {
            data += query.value(nameCol).toString(); // output first name
            data += "###";
            break;
         }
    }

    QString tmp="#RST#";
    while(1)
    {
        while (query.next())
        {
           // qDebug() << query.value(nameCol).toString(); // output all names
            if(query.value(nameCol).toString() != NULL)
            {
                  tmp = query.value(nameCol).toString(); // output next name

                break;
            }
         }
        if(tmp != "#RST#")
        {
            data+= tmp;
            data += "###";
            tmp="#RST#";

        }
        else
        {
            break;
        }
    }

    QStringList tmplst  = data.split("###");

    return tmplst;

}
