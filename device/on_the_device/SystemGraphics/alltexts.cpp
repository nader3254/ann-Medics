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
     ATT->start();
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

void AllTexts::AllTextTest(bool st)
{

    _st=st;
}

void AllTexts::AllTextRender()
{
    if(_st==true)
    {
        i++;
        int hr[]={68,66,70,65,80,78,79,81,80,78};
        int spo2[]={98,96,97,98,97,96,95,94,98,97};
         SetHR(hr[i]);
         SetSpo2(spo2[i]);
         if(i==9)
         {
             i=0;
         }
         //SetNibp(i+2,i);
    }
    else
    {
        SetHR(0);
        SetSpo2(0);
        SetNibp(0,0);
    }


}
