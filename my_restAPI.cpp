#include "my_restAPI.h"



RestAPI::RestAPI(QObject *parent)
{

   ThreadEngine =new QTimer(this);
   QObject::connect(ThreadEngine,&QTimer::timeout,this,&RestAPI::thread);
   ThreadEngine->setInterval(2);
   ThreadEngine->start();
   DB = new DatabaseControl("./database/ann_medics.db");
   if(!DB->GetConnectionStatus())
   {
       qDebug() <<"database doesnt exist or some failure exist....";
   }
   else
   {
       qDebug() <<"database oppened succesfully";
   }
   qDebug() <<"thread starting ....";
  // qDebug()<<"index= "<<DB->IndexOf("users","name","ahmed");
   CLR();
}


void RestAPI::thread()
{


   if(IsClientRequest())
   {

        qDebug()<<"recieved request is : "<<Raw_CMD;
        ParseClientCommand();
        qDebug()<<"passed from parsing......";
        ExecuteCMD();
        qDebug()<<"passed from execution......";
        RespondClient();
        qDebug()<<"passed from responding......";
   }
}

void RestAPI::send(QString msg)
{
   FileBrowser *FB=new FileBrowser("");
   FB->WriteFile(SENDER_BUFFER_PATH,msg);
   system(TCP_SCRIPT_PATH);

}

QString RestAPI::get_conn_st()
{
    QByteArray rscmd;
    rscmd.append(START_BYTE);
    if(!DB->GetConnectionStatus())
    {
         rscmd.append("#0#");
    }
    else
    {
         rscmd.append("#1#");
    }
    rscmd.append(END_BYTE);
    QString GCcmd=QString::fromStdString(rscmd.toStdString());
    return GCcmd;
}

QString RestAPI::get_table_lenght()
{
    QString sz =QString::number(DB->TableSize(TableName));
    QByteArray by;
    by.append(START_BYTE);
    by.append("#");
    by.append(INT);
    by.append("#");
    by.append(sz.toStdString());
    by.append("#");
    by.append(END_BYTE);

    QString sz_str = QString::fromStdString(by.toStdString());
    return sz_str;
}

QString RestAPI::get_idx_by_value()
{
    QStringList idxs;QByteArray by;
    QString rscmd;
    by.append(START_BYTE);
    by.append("#");
    for (int i = 0; i < C_names.size(); i++)
    {
      idxs <<QString::number(DB->IndexOf(TableName,C_names.at(i),C_values.at(i)));
    }
    for(int i=0;i<idxs.size();i++)
    {
        by.append(INT);
        by.append("#");
        by.append(idxs.at(i).toStdString());
        by.append("#");
    }
     by.append(END_BYTE);
     rscmd=QString::fromStdString(by.toStdString());

     return rscmd;
}

QString RestAPI::rd_by_idx()
{
    QList<int> idxs;QByteArray by;
    QString rscmd;QStringList rdv;
    by.append(START_BYTE);
    by.append("#");
    for(int i=0;i<C_values.size();i++)
    {
        idxs<<C_values.at(i).toInt();
    }
    for(int i=0;i<idxs.size();i++)
    {
        rdv << DB->ReadFromTable(TableName,C_names.at(i),idxs.at(i));
    }
    by.append(STRING);
    by.append("#");
    for(int i=0;i<rdv.size();i++)
    {
       by.append(rdv.at(i).toStdString()) ;
       by.append("#");
    }
    by.append(END_BYTE);
    rscmd=QString::fromStdString(by.toStdString());

    return rscmd;
}

QString RestAPI::rd_by_val()
{
    QByteArray by;QString rscmd;
    QList<char> tf;
    by.append(START_BYTE);
    by.append("#");
    by.append(INT);
    by.append("#");
    for(int i=0;i<C_values.size();i++)
    {
      if( DB->ReadFromTable(TableName,C_names.at(i),C_values.at(i)))
      {
          tf<<'1';
      }
      else
      {
          tf<<'0';
      }

    }
    for(int i=0;i<tf.size();i++)
    {
        by.append(tf.at(i));
        by.append("#");
    }
    by.append(END_BYTE);
    rscmd=QString::fromStdString(by.toStdString());

    return rscmd;
}

QString RestAPI::rd_by_col()
{
    QByteArray by;QString rscmd;
    QStringList rdv;
    by.append(START_BYTE);
    by.append("#");
    by.append(STRING);
    by.append("#");
    for(int i=0;i<C_names.size();i++)
    {
        rdv<<DB->ReadFromTable(TableName,C_names.at(i));

    }
    for(int i=0;i<rdv.size();i++)
    {
        by.append(rdv.at(i).toStdString());
        if(i!=rdv.size()-1)
        {
          by.append("^#");
        }

    }
    by.append(END_BYTE);
    rscmd=QString::fromStdString(by.toStdString());

    return rscmd;
}

void RestAPI::upd_tr()
{
    int sz = C_names.size();//C_names
    QString cn[sz],cv[sz];
    for(int i=0;i<sz;i++)
    {
        cn[i]=C_names.at(i);
        cv[i]=C_values.at(i);
    }


    DB->UpdateTableRecord(TableName,sz,cn,cv);

}

void RestAPI::rem_tr()
{
    int sz = C_names.size();//C_names
    QString cn[sz],cv[sz];
    for(int i=0;i<sz;i++)
    {
        cn[i]=C_names.at(i);
        cv[i]=C_values.at(i);
    }


    DB->RemoveTableRecord(TableName,sz,cn,cv);
}

void RestAPI::add_tr()
{
    int sz = C_names.size();//C_names
    QString cn[sz],cv[sz];
    for(int i=0;i<sz;i++)
    {
        cn[i]=C_names.at(i);
        cv[i]=C_values.at(i);
    }


    DB->AddTableRecord(TableName,sz,cn,cv);
}

void RestAPI::CLR()
{
    Encoded_CMD = 0;
    Respond_CMD = "";
    Raw_CMD     = "";
    TableName   = "";
    C_names.clear();
    C_values.clear();
}

QString RestAPI::recieve()
{
    FileBrowser *FB=new FileBrowser("");
    QString tmp = FB->ReadFile(RECIEVE_BUFFER_PATH);
    FB->WriteFile(RECIEVE_BUFFER_PATH,DEFAULT_BUFFER);
    return tmp;
}

bool RestAPI::IsClientRequest()
{
   QString may_be_cmd = recieve();
   if( may_be_cmd.contains(DEFAULT_BUFFER) || (may_be_cmd=="file not found") )
   {
       return false;
   }
   else
   {
        Raw_CMD = may_be_cmd;
        return true;
   }
}

void RestAPI::ExecuteCMD()
{
    switch (Encoded_CMD) {
    case GET_CONNECTION_STATUS: Respond_CMD = get_conn_st(); break;
    case GET_TABLE_ROW_LENGHT:  Respond_CMD = get_table_lenght(); break;
    case GET_INDEX_BY_VALUE:    Respond_CMD = get_idx_by_value(); break;
    case UPDATE_TABLE_RECORD:                 upd_tr(); break;
    case REMOVE_TABLE_RECORD:                 rem_tr(); break;
    case ADD_TABLE_RECORD:                    add_tr(); break;
    case READ_BY_INDEX:         Respond_CMD = rd_by_idx(); break;
    case READ_BY_VALUE:         Respond_CMD = rd_by_val(); break;
    case READ_BY_COLOMUN:       Respond_CMD = rd_by_col(); break;
    default:
        qDebug()<<"invalid cmd from ExecuteCMD()....";
        Respond_CMD ="invalid";
        break;
    }

}

void RestAPI::ParseClientCommand()
{
    QStringList parsed_cmd = Raw_CMD.split("#");
    QStringList parsed_cmd2;
    for(int i=0;i<parsed_cmd.size();i++)
    {
        QString tmp = parsed_cmd.at(i);
        tmp.remove("#");
        parsed_cmd2<<tmp;
    }
    qDebug()<<parsed_cmd2;
    if(parsed_cmd2.at(0)==START_BYTE&&parsed_cmd2.at(parsed_cmd2.size()-1)==END_BYTE)
    {
        qDebug()<<"Valid request has been recieved..... ";
        QString cmd=parsed_cmd2.at(1);
        // encode the request command
        Encoded_CMD = cmd.toInt();
        qDebug()<<"from parse_cmd"<<Encoded_CMD;
        // encode the request table name
        if(parsed_cmd2.at(2)==TABLE_NAME)
        {
          TableName = parsed_cmd2.at(3);
          qDebug()<<"table name is : "<<TableName;
        }

        // encode the request colomuns names
        int last_idex_of_CN=0;
        if(parsed_cmd2.at(4)==COLMUN_NAMES)
        {
          for(int i=5;i<2000;i++)
          {
              last_idex_of_CN = i;
              if(parsed_cmd2.at(i)==COLOMUN_VALUES || parsed_cmd2.at(i)==END_BYTE)
              {
                  break;
              }
              else
              {
                  C_names<<parsed_cmd2.at(i);
              }
          }
        }
        else
        {
           qDebug()<<"No colomouns names .....";
        }

        // encode the request colomuns names
        if(parsed_cmd2.at(last_idex_of_CN)==COLOMUN_VALUES)
        {
          for(int i=last_idex_of_CN+1;i<2000;i++)
          {
              if(parsed_cmd2.at(i)==END_BYTE)
              {
                  break;
              }
              else
              {
                  C_values<<parsed_cmd2.at(i);
              }


          }
        }
        else
        {
           qDebug()<<"No colomouns values .....";
        }

       /************* debugging ***********/
        qDebug()<<"colomun names ..........";
        for(int i=0;i<C_names.size();i++)
        {
            qDebug()<<C_names.at(i);
        }
        qDebug()<<"colomun values ..........";
        for(int i=0;i<C_values.size();i++)
        {
            qDebug()<<C_values.at(i);
        }



    }
    else
    {
       qDebug()<<"invalid request ..... ";
    }

}
void RestAPI::RespondClient()
{
   if(Respond_CMD!="invalid")
   {
       send(Respond_CMD);
       CLR();
   }

}

RestAPI::~RestAPI()
{

}





