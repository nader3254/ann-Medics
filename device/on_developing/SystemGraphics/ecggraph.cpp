#include "ecggraph.h"


EcgGraph::EcgGraph(QQuickItem *parent,QObject *obj): QQuickPaintedItem(parent)
{
    QObject *graph = obj->findChild<QObject*>("ecg_graph");
    ecg_graphics_ptr= qobject_cast<EcgGraph*>(graph);

    ecg_t=new QTimer(this);
    connect(ecg_t, SIGNAL(timeout()), this, SLOT(EcgRender()));
    ecg_t->setInterval(ECG_RTime);
    ecg_t->start();


}

void EcgGraph::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::SmoothPixmapTransform,1);
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
    // connect all points
    ConnectPoints(painter);
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
   // _x+=14;
    pt.setX(_x++);
    //pt.setY(ECG_Ry-test[i]);
    pt.setY(ECG_Ry);
  //  pt.setY(ECG_Ry-sin(2*i++*0.0174532925 )*50);
    points<<pt;
    if(!(points.size()<ECG_RX2))
    {
        _x=0;
               points.clear();

    }

   i++;
   if(i==10)
   {
       i=0;
   }
    update();

}

void EcgGraph::ConnectPoints(QPainter *painter)
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
                    if(pnt.x()<ECG_RX2)
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
                    if(pnt.x()<ECG_RX2)
                             painter->drawPoint(pnt);
                }
            }

        }

    }

}
