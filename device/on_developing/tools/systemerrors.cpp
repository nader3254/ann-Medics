#include "systemerrors.h"

systemErrors::systemErrors(QObject *parent)
    : QObject{parent}
{
  s_err_txt = parent->findChild<QObject*>("s_err");
  warning   = parent->findChild<QObject*>("warning_btn");
  err       = parent->findChild<QObject*>("err_btn");
  tmr=new QTimer(this);
  connect(tmr, SIGNAL(timeout()), this, SLOT(err_task()));
  tmr->setInterval(700);/* one miniute */
  tmr->start();


}

void systemErrors::add_error(QString msg)
{
    external_error=true;
    s_err_txt->setProperty("color","#ff0000");
    s_err_txt->setProperty("text",msg);
}

void systemErrors::add_warning(QString msg)
{
    external_warning=true;
    s_err_txt->setProperty("color","#ffff00");
    s_err_txt->setProperty("text",msg);
}

void systemErrors::err_task()
{
    if(external_warning)
    {
        toggle_warning();
    }
    if(external_error)
    {
        toggle_err();
    }
}

void systemErrors::stop()
{
    external_error=false;
    external_warning=false;
}

void systemErrors::toggle_warning()
{
    if(prev_warning)
    {
        warning->setProperty("visible","false");
        prev_warning=false;
    }
    else
    {
        warning->setProperty("visible","true");
        prev_warning=true;
    }
}

void systemErrors::toggle_err()
{
    if(prev_error)
    {
        err->setProperty("visible","false");
        prev_error=false;
    }
    else
    {
        err->setProperty("visible","true");
        prev_error=true;
    }
}
