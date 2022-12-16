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


    path=db_path;



}

DatabaseControl::~DatabaseControl()
{
    QSqlDatabase::removeDatabase(path);
    SysDB.close();
}

bool DatabaseControl:: GetConnectionStatus()
{
    return ConnectionStatus;

}
bool DatabaseControl:: GetTransactionStatus()
{
    return TransactionStatus;
}
//not completed
void DatabaseControl::UpdateTableRecord(QString table, int Colomuns_no, QString *coloumns_names, QString *Record_values)
{
    //"cmd  update table set col1='paramter1',col2='paramter2',..... where col1='paramter1',col2='paramter2'

      QString cmd = "update " + table + " set ";

      for(int i=0;i<Colomuns_no;i++)
      {
          cmd += coloumns_names[i];
          cmd += "='";
          cmd += Record_values[i] + "'";
          if(i != Colomuns_no-1)
          {
               cmd += ",";
          }
      }
      cmd +=" where ";
      cmd += coloumns_names[0];
      cmd += "='";
      cmd += Record_values[0] + "'";
      cmd += " AND ";
      cmd += coloumns_names[1];
      cmd += "='";
      cmd += Record_values[1] + "'";



      QSqlQuery query;
      query.prepare(cmd);
      query.exec();
      qDebug() << cmd;

}
//not completed
void DatabaseControl::RemoveTableRecord(QString table, int Colomuns_no, QString *coloumns_names, QString *Record_values)
{
    //"cmd  delete from table where col1='paramter1',col2='paramter2'

    QString cmd = "delete from " + table + " where ";
    for(int i=0;i<Colomuns_no-1;i++)
    {
        cmd += coloumns_names[i];
        cmd += "='";
        cmd += Record_values[i] + "'";
        if(i != Colomuns_no-2)
        {
             cmd += " AND ";
        }
    }

    QSqlQuery query;
    query.prepare(cmd);
    query.exec();
    qDebug() << cmd;
}


void DatabaseControl:: AddTableRecord(QString table , int Colomuns_no , QString *coloumns_names ,QString *Record_values )
{
    QString cmd = "INSERT INTO "+ table +"(";

    for(int i=0;i<Colomuns_no;i++)
    {
        cmd += coloumns_names[i];
        if(i != Colomuns_no-1)
           cmd += ", ";

    }
    cmd += ") "
            "VALUES (";

    for(int i=0;i<Colomuns_no;i++)
    {
        cmd += ":";
        cmd += coloumns_names[i];
        if(i != Colomuns_no-1)
           cmd += ", ";

    }
    cmd += ") ";

    QSqlQuery query;
    query.prepare(cmd);
    for(int i=0;i<Colomuns_no;i++)
    {

       query.bindValue(":"+coloumns_names[i], Record_values[i]);
    }
    query.exec();
    qDebug() << cmd;
  /*
   *
    QSqlQuery query;
    query.prepare("INSERT INTO person (id, forename, surname) "
                  "VALUES (:id, :forename, :surname)");
    query.bindValue(":id", 1001);
    query.bindValue(":forename", "Bart");
    query.bindValue(":surname", "Simpson");
    query.exec();
  */




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

        if(query.value(nameCol).toString() != "")
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
            if(query.value(nameCol).toString() != "")
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
        return "ReadFromDatabase(): invalid index ";
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

        if(query.value(nameCol).toString() != "")
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
            if(query.value(nameCol).toString() != "")
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

int DatabaseControl::TableSize(QString table)
{
    QSqlQuery query("SELECT * FROM "+ table);
    QSqlRecord rec = query.record();
    QStringList lst = ReadFromTable( table , rec.fieldName(1));
   // qDebug() <<"table record 0= "<<lst.at(0);

    return lst.size()-1;
}

int DatabaseControl::IndexOf(QString table, QString fieled, QString content)
{
    QStringList lst = ReadFromTable( table ,fieled );
    int x=0;
    for(int i=0;i<lst.size();i++)
    {
       // qDebug()<<"inside "<<i<<lst.at(i)<<"content"<<content;
        if(content.contains(lst.at(i)))
        {
           x=i;
           break;
        }
    }

    return x;
}



