#include "ecggraph.h"


EcgGraph::EcgGraph(QQuickItem *parent,QObject *obj): QQuickPaintedItem(parent)
{
    //QObject *graph = obj->findChild<QObject*>("ecg_graph");
   // ecg_graphics_ptr= qobject_cast<EcgGraph*>(graph);

    ecg_t=new QTimer(this);
    connect(ecg_t, SIGNAL(timeout()), this, SLOT(EcgRender()));
    ecg_t->setInterval(ECG_RTime);
    ecg_t->start();


}

void EcgGraph::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing,1);
    QPen p ;


    QFont font("Helvetica",18,QFont::Bold);
       painter->setFont(font);


       p.setColor(QColor(0, 255, 200,255));
       painter->save();
       p.setWidth(2);
       painter->setPen(p);
       for(int j=0;j<points.size();j++)
       {
             painter->drawPoint(points.at(j));
       }

       painter->restore();


}

float EcgGraph::getVoltage()
{
    return m_volt;
}

void EcgGraph::setVolyage(float mv)
{
    if(m_volt == mv)
              return;
          m_volt = mv;
            update();
            emit voltageChanged();
}

void EcgGraph::EcgRender()
{
    pt.setX(_x++);//pt.setY(ECG_Ry-(sin(i++*0.0174532925)*40));
    pt.setY(ECG_Ry);
    points<<pt;
    if(!(points.size()<ECG_RX2))
    {
        _x=0;
       // for(int j=0;j<points.size();j++)
               points.clear();

    }


    update();
  //  emit voltageChanged();
}
