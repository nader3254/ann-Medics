#include "spo2graph.h"

Spo2graph::Spo2graph(QQuickItem *parent): QQuickPaintedItem(parent)
{
    spo2_t=new QTimer(this);
    FB = new FileBrowser("");
    connect(spo2_t, SIGNAL(timeout()), this, SLOT(SPO2Render()));
    spo2_t->setInterval(SPO2_RTime);
    spo2_t->start();
   // system("cd /home/pi/tst/MAX30102 && sudo python3 Red_IR.py");

}
void Spo2graph::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing,1);
    QPen p ;


    QFont font("Helvetica",18,QFont::Bold);
       painter->setFont(font);


      p.setColor(QColor(0, 184, 255 ,255));
      //p.setColor(QColor(0, 0, 255 ,255));


       painter->save();
       p.setWidth(2);
       painter->setPen(p);
       for(int j=0;j<points.size();j++)
       {
          painter->drawPoint(points.at(j));
       }

       painter->restore();


}

bool Spo2graph::isConnected()
{
    if(IR>130000 && IR<160000)
    {
        return true;
    }
    else
    {
        return false;
    }

}

int Spo2graph::getspo2()
{
       return c_spo2;
}

void Spo2graph::setspo2(int sp)
{
    if(c_spo2 == sp)
              return;
          c_spo2 = sp;
            update();
            emit spo2Changed();
}

void Spo2graph::SPO2Render()
{

    readRED_IR();
    float ry;
        if(IR>130000 && IR<160000)
        {
            ry=SPO2_Ry-(23*cos(ir_dc_updater*2*0.0174532925));
        }
        else
        {
            ry=250;
        }


    //ry=ry*1.6-;
     // float ry=IR*2.7/10000;
        pt.setX(_x++);
        pt.setY(ry);
        //qDebug()<<"ry : "<<ry;

    points<<pt;
    if(!(points.size()<SPO2_RX2))
    {
        _x=0;
        points.clear();

    }

    update();



}

void Spo2graph::readRED_IR()
{
    QString rir =FB->ReadFile("/home/pi/tst/MAX30102/rir.txt");
    QStringList lst = rir.split("###");
    if(lst.size()>1)
    {
        ir_dc_updater++;
        QString irstr =lst.at(0);
        QString redstr =lst.at(1);
        irstr.remove("###");
        redstr.remove("###");
        IR=irstr.toLong();
        RED=redstr.toLong();

        if((IR<IR_dc)&&(IR>50000))
        {

            IR_dc=IR;

        }
//        if((IR>120000)&&(IR>50000))
//        {
//            IR_dc=120000;
//            if((IR>130000)&&(IR>50000))
//            {
//                IR_dc=130000;
//                if((IR>140000)&&(IR>50000))
//                {
//                     IR_dc=140000;
//                     if((IR>150000)&&(IR>50000))
//                     {
//                          IR_dc=150000;
//                          if((IR>160000)&&(IR>50000))
//                          {
//                               IR_dc=160000;
//                          }
//                     }
//                }
//            }
//        }

       if(ir_dc_updater==360)
       {
          IR_dc=160000;
           ir_dc_updater=0;
        }



       // qDebug()<<"ir:"<<IR<<"red:"<<RED<<"\n";
    }

    //qDebug()<<rir;

}
/*
 *     if(yyy>0)
    {
       ry_prev= SPO2_Ry-(yyy*19);
       pt.setY(SPO2_Ry-(yyy*19));
    }
    else
    {
        if(ry_prev<=0)
        {
            ry_prev=0;
        }
        else
        {
           ry_prev--;
        }

       pt.setY(SPO2_Ry-ry_prev);
    }
*/
