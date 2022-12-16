#include "spo2graph.h"

Spo2graph::Spo2graph(QQuickItem *parent): QQuickPaintedItem(parent)
{
    spo2_t=new QTimer(this);
    connect(spo2_t, SIGNAL(timeout()), this, SLOT(SPO2Render()));
    spo2_t->setInterval(SPO2_RTime);
    spo2_t->start();

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

       painter->restore();


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
    pt.setX(_x++);pt.setY(SPO2_Ry);
    points<<pt;
    if(!(points.size()<SPO2_RX2))
    {
        _x=0;
        points.clear();

    }


    update();
  //  emit voltageChanged();
}

