#include "spo2graph.h"

Spo2graph::Spo2graph(QQuickItem *parent): QQuickPaintedItem(parent)
{
    spo2_t=new QTimer(this);
    connect(spo2_t, SIGNAL(timeout()), this, SLOT(SPO2Render()));
    spo2_t->setInterval(SPO2_RTime);
    spo2_t->start();

    spo2_t2=new QTimer(this);
    connect(spo2_t2, SIGNAL(timeout()), this, SLOT(curve_changer()));
    spo2_t2->setInterval(SPO2_RTime2);
    spo2_t2->start();

    oneMT=new QTimer(this);
    connect(oneMT, SIGNAL(timeout()), this, SLOT(on_OMT()));
    oneMT->setInterval(15000);/* one miniute */
    oneMT->start();
   // "cd /home/pi/tst/MAX30102 && sudo python3 Red_IR.py" /* this command to run the script */

}

void Spo2graph::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing,1);
    QPen p ;


    QFont font("Helvetica",18,QFont::Bold);
    painter->setFont(font);

    p.setColor(QColor(0, 184, 255 ,255));
    painter->save();
    p.setWidth(2);
    painter->setPen(p);
    for(int j=0;j<points.size();j++)
    {
       painter->drawPoint(points.at(j));
    }
    ConnectPoints(painter);
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

bool Spo2graph::isSensorConnected()
{



   if(prev_ir!=IR)
   {
       prev_ir=IR;
       no_sensor_ctr=0;
       return true;
   }
   else
   {
       no_sensor_ctr++;
       if(no_sensor_ctr>=500)
       {

           no_sensor_ctr=0;
           return false;
       }
       else
       {
           return true;
       }
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

void Spo2graph::setText(AllTexts *txt)
{
    Txt=txt;
}

void Spo2graph::setSysERR(systemErrors *err)
{

    _err=err;
}

void Spo2graph::set_red_ir(long ir, long red)
{
    IR=ir;
    RED=red;

}

void Spo2graph::SPO2Render()
{

    readRED_IR();
    float ry;

    if(isConnected())
    {
        if(curve_change)
        {
            ry=SPO2_Ry-(35*cos(ir_dc_updater*2*0.0174532925)*tanh(ir_dc_updater*2*0.0174532925*sin(ir_dc_updater*2*0.0174532925)));
        }
        else
        {
           ry=SPO2_Ry-(41*cos(ir_dc_updater*1*0.0174532925*(1/cos(ir_dc_updater*1*0.0174532925)))*tanh(ir_dc_updater*1*0.0174532925*6));
        }
    }
    else
    {
        ry=SPO2_Ry;
    }


   if(ir_dc_updater<50000)
   {
       ir_dc_updater++;
   }
   else
    {
       ir_dc_updater=0;
    }

    pt.setX(_x++);
    pt.setY(ry);
    points<<pt;
    if(!(points.size()<SPO2_RX2))
    {
        _x=0;
        points.clear();

    }

    update();

    if(isSensorConnected()==false)
    {
      _err->add_error("no spo2 device connected , plese check \n"
                      "the wiring and restart the system...");
    }
//    if(isConnected()==false)
//    {
//      _err->add_warning("no finger connected to the spo2 \n");
//    }

}

void Spo2graph::curve_changer()
{
   if(curve_change==true)
   {
       curve_change=false;
   }
   else
   {
       curve_change=true;
   }
   irdc=160000;reddc=160000;
   max_ir=150000;

}

void Spo2graph::on_OMT()
{
    OM_passed=true;
}

void Spo2graph::readRED_IR()
{
  // will get red and ir using udp
    if(IR>120000&&IR<135000)
    {
        curve_change=false;
    }
    if(IR>135000)
    {
        curve_change=true;
    }
    spo2calculator();
    hrcalculator();

}

void Spo2graph::ConnectPoints(QPainter *painter)
{
    for(int j=0;j<points.size();j++)
    {
        if(j!=points.size()-1)
        {
            if(points.at(j).y()>points.at(j+1).y())
            {
                for(int k =points.at(j+1).y();k<points.at(j).y();k++)
                {

                    QPoint pnt;
                    pnt.setX(points.at(j).x());
                    pnt.setY(k);
                    if(pnt.x()<SPO2_RX2)
                        painter->drawPoint(pnt);
                }
            }
            else
            {
                //points.at(j).y()<points.at(j+1).y()
                for(int k =points.at(j).y();k<points.at(j+1).y();k++)
                {
                    QPoint pnt;
                    pnt.setX(points.at(j).x());
                    pnt.setY(k);
                    if(pnt.x()<SPO2_RX2)
                        painter->drawPoint(pnt);
                }
            }

        }

    }

}

void Spo2graph::spo2calculator()
{
    irac=IR;redac=RED;
    if((IR<irdc) && (IR>3000))
    {
        irdc=IR;
    }
    if((RED<reddc) && (RED>3000))
    {
        reddc=RED;
    }
    float div=((irac-irdc)*reddc);
    float prcent= ((irdc*(redac-reddc))/div);
    float spo;
    //qDebug()<<"percent : "<<prcent;
    if(IR>3000)
    {
        spo=104-(17*prcent);

    }
    else
    {
        spo=0;
    }
    if(spo>=0&&spo<100)
    {
      Txt->SetSpo2(spo);
    }

}
//to do :
// make algorithm on every falling edge using irdc
void Spo2graph::hrcalculator()
{
    if(IR>max_ir)
    {
        max_ir=IR;
    }
    if(IR>(max_ir-555))
    {
        hr_ctr++;
    }
    if(OM_passed)
    {
        OM_passed=false;
        //qDebug()<<"heart rate is :"<<hr_ctr;
        hr_ctr=0;
    }

}

