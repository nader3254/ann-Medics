#ifndef MY_RESTAPI_H
#define MY_RESTAPI_H
#include <QDebug>
#include <QStringList>
#include <QList>
#include <QTimer>
#include "databasecontrol.h"
#include "filebrowser.h"


#define TCP_SCRIPT_PATH            "cd ./scripts &&  send.bat"
#define RECIEVE_BUFFER_PATH        "./scripts/recieved.txt"
#define DEFAULT_BUFFER             "default recieve file....."

#define SENDER_BUFFER_PATH        "./scripts/tosend.txt"
/*********************************************
 * The restAPI is the Middle layer between   *
 * the batabase and the javascript functions *
 *                                           *
 * i need to do this :                       *
 * 1) run tcp script                         *
 * 2) make send and recieve                  *
 *                                           *
***********************************************/

/********** C O M M A N D S ***********/
/*
 * GET_CONNECTION_STATUS = 1
 * UPDATE_TABLE_RECORD
 * REMOVE_TABLE_RECORD
 * ADD_TABLE_RECORD
 * READ_BY_INDEX
 * READ_BY_VALUE
 * READ_BY_COLOMUN
 * GET_TABLE_ROW_LENGHT
 * GET_INDEX_BY_VALUE
*/
/**********  D A T A   T Y P E S  ***********/
/*
 * TABLE_NAME ='!'
 * COLMUN_NAMES ='%'
 * COLOMUN_VALUES ='~'
 * STRING
 * INT
 * ERROR
*/
/********** COMMUNICATION PROTOCOL **********/
/*************** CLIENT REQUEST *************/
/*********************************************************************
 *            *     *   *           *       *   *        *           *
 * START_BYTE * CMD * # * DATA_TYPE * data1 * # *........* END_BYTE  *
 *            *     *   *           *       *   *        *           *
**********************************************************************/
/*************** CLIENT RESPOND *************/
/*************************************************************************
 *            *         *   *           *       *   *        *           *
 * START_BYTE *   CMD   * # * DATA_TYPE * data1 * # *........* END_BYTE  *
 *            * RESPOND *   *           *       *   *        *           *
 *            *         *   *           *       *   *        *           *
**************************************************************************/

#define START_BYTE         '$'
#define END_BYTE           '@'

#define TABLE_NAME         '!'
#define COLMUN_NAMES       '%'
#define COLOMUN_VALUES     '~'
#define STRING             '^'
#define INT                '*'
#define ERROR              '?'



class RestAPI:public QObject
{
public:
     RestAPI(QObject *parent);   /* will start the python script */
    ~RestAPI();

     void RespondClient();      /* will prepare data and respond the client */
     bool IsClientRequest();    /* will check if any request or not */
     void ExecuteCMD();         /* will execute the  cmd */
     void ParseClientCommand(); /* will set the data types values */



private slots:
     void thread();


private:
 /* commands definition */   enum{ GET_CONNECTION_STATUS=1,UPDATE_TABLE_RECORD,REMOVE_TABLE_RECORD,ADD_TABLE_RECORD,READ_BY_INDEX,READ_BY_VALUE,READ_BY_COLOMUN,GET_TABLE_ROW_LENGHT,GET_INDEX_BY_VALUE };
 /* data types */

  int         Encoded_CMD;
  QString     Respond_CMD;
  QString     Raw_CMD;
  QString     TableName;
  QStringList C_names;
  QStringList C_values;
  QTimer      *ThreadEngine;

  DatabaseControl *DB;

  QString    recieve();
  void       send(QString msg);

  QString    get_conn_st();
  QString    get_table_lenght();
  QString    get_idx_by_value();
  QString    rd_by_idx();
  QString    rd_by_val();
  QString    rd_by_col();
  void       upd_tr();
  void       rem_tr();
  void       add_tr();
  void       CLR();



};

#endif // MY_RESTAPI_H
