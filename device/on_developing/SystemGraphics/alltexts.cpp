#include "alltexts.h"

AllTexts::AllTexts(QObject *parent)
{
  _HR      = parent->findChild<QObject*>("heartrate");
  _SPO2    = parent->findChild<QObject*>("spo2");
  NIBP_Min = parent->findChild<QObject*>("nbip_min");
  NIBP_Max = parent->findChild<QObject*>("nbi_pmax");


  ATT=new QTimer(this);
  connect(ATT, SIGNAL(timeout()), this, SLOT(AllTextRender()));
  ATT->setInterval(1500);
}

void AllTexts::SetHR(int val)
{
    _HR->setProperty("text",(int)val);
    hr=val;
}

void AllTexts::SetSpo2(int val)
{
     _SPO2->setProperty("text",(int)val);
     spo2=val;
}

void AllTexts::SetNibp(int max, int min)
{
     NIBP_Min->setProperty("text",(int)min);
     NIBP_Max->setProperty("text",(int)max);
     nibp_max=max;
     nibp_min=min;
}

int AllTexts::GetHR()
{
    return hr;
}

int AllTexts::GetSpo2()
{
    return spo2;
}

int AllTexts::GetNibp_min()
{
    return nibp_min;
}

int AllTexts::GetNibp_max()
{
    return nibp_max;
}

void AllTexts::AllTextTest()
{
    ATT->start();
}

void AllTexts::AllTextRender()
{
   i++;

    SetHR(i);
    SetSpo2(i);
    SetNibp(i+2,i);

}
