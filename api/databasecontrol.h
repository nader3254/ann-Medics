#ifndef DATABASECONTROL_H
#define DATABASECONTROL_H

#include <QtSql>
#include <qfileinfo>
#include <QStringList>
#include <QDebug>




/*
 * DatabaseControl(char* db_path) =>
 *     try to open at db_path directory
 *
 * GetConnectionStatus()          =>
 *     return true if the database oppened successfully
 *
 * UpdateTableRecord(QString table , int Colomuns_no , QString *coloumns_names ,QString *Record_values );
 *     update table record values but you need to send all field values and
 *     the old and new values of the record you need also to send the fieled numbers
 *
 * RemoveTableRecord(QString table , int Colomuns_no , QString *coloumns_names ,QString *Record_values );
 *      Remove table record values but you need to send all field values and
 *      the old values of the record you need also to send the fieled numbers
 *
 * AddTableRecord(QString table , int Colomuns_no   , QString *coloumns_names ,QString *Record_values )
 *      add new record to table but you need to send all field values and
 *      the new values of the record you need also to send the fieled numbers
 *
 * ReadFromTable(QString table  , QString attribute ,int index);
 *      read table  field nammed "attribute" at "index" return string
 *
 * ReadFromTable(QString table  , QString attribute ,QString content);
 *      check if the fieled "attribute" has item called "content" or not
 *      return true if available useful for authihentication problems
 *
 *  ReadFromTable(QString table  , QString attribute);
 *      read tabe fieled "attribute" and return the whole items
 *      of the field in form of QStringList
 *
 * TableSize(QString table );
 *     return the table size
 *
 * IndexOf(QString table , QString fieled ,QString content);
 *     return index of "content" at "fieled" of "table"
 *
 *
 * Resources :
 *     //update
 *     //https://www.youtube.com/watch?v=q_NYqgOXXS8&list=PLS1QulWo1RIZjrD_OLju84cUaUlLRe5jQ&index=17&ab_channel=ProgrammingKnowledge
*
*     //remove
*     //https://www.youtube.com/watch?v=NIp6pMtEhC0&list=PLS1QulWo1RIZjrD_OLju84cUaUlLRe5jQ&index=18&ab_channel=ProgrammingKnowledge
*
*     //load table
*     //https://www.youtube.com/watch?v=OrHitqwJu8Q&list=PLS1QulWo1RIZjrD_OLju84cUaUlLRe5jQ&index=19&ab_channel=ProgrammingKnowledge
*
*
*     //list widget
*     //https://www.youtube.com/watch?v=dRLLQr4aWnk&ab_channel=LearnQT
*
*    //https://doc.qt.io/qt-5/qsqlquery.html#first
*    //https://www.youtube.com/watch?v=LiHHm7cd5Bs&list=PL2D1942A4688E9D63&index=52&ab_channel=VoidRealms
*    //https://www.youtube.com/watch?v=ahT9xRkBavc&list=PL2D1942A4688E9D63&index=53&ab_channel=VoidRealms
*    //https://doc.qt.io/qt-5/qsqlrecord.html#count
*    //https://doc.qt.io/qt-5/qstringlist.html
*
*/


class DatabaseControl
{
public:
     DatabaseControl();
     DatabaseControl(char* db_path);
    ~DatabaseControl();

    bool        GetConnectionStatus();
    bool        GetTransactionStatus();
    void        UpdateTableRecord(QString table , int Colomuns_no , QString *coloumns_names ,QString *Record_values );
    void        RemoveTableRecord(QString table , int Colomuns_no , QString *coloumns_names ,QString *Record_values );
    void        AddTableRecord(QString table , int Colomuns_no   , QString *coloumns_names ,QString *Record_values );
    QString     ReadFromTable(QString table  , QString attribute , int index);
    bool        ReadFromTable(QString table  , QString attribute , QString content);
    QStringList ReadFromTable(QString table  , QString attribute);
    int         TableSize(QString table );
    int         IndexOf(QString table , QString fieled ,QString content);

private:
   QSqlDatabase SysDB;
   QString      path;
   int          LastIndex;
   bool         ConnectionStatus;
   bool         TransactionStatus;

};

#endif // DATABASECONTROL_H
