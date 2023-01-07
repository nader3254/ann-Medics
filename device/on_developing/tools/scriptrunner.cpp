#include "scriptrunner.h"


scriptRunner::scriptRunner(QString script)
{
    scrpt=script;

}

void scriptRunner::run()
{

    QByteArray cmd=scrpt.toUtf8();
    if(en=true)
    {
       system(cmd);
       en=false;
    }
}

void scriptRunner::retry()
{
    en=true;
}
