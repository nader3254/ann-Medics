#include "ecggraph.h"


EcgGraph::EcgGraph(QQuickItem *parent,QObject *obj): QQuickPaintedItem(parent)
{
    //QObject *graph = obj->findChild<QObject*>("ecg_graph");
   // ecg_graphics_ptr= qobject_cast<EcgGraph*>(graph);

    ecg_t=new QTimer(this);
    connect(ecg_t, SIGNAL(timeout()), this, SLOT(EcgRender()));
    ecg_t->setInterval(ECG_RTime);
    ecg_t->start();

<<<<<<< HEAD
    buzzTimer=new QTimer(this);
    connect(buzzTimer, SIGNAL(timeout()), this, SLOT(bpmTask()));
    buzzTimer->setInterval(880);
    buzzTimer->start();
=======

>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
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

<<<<<<< HEAD
int EcgGraph::getrx()
{

}

void EcgGraph::setrx(int mv)
{

}

int EcgGraph::getry()
{

}

void EcgGraph::setry(int mv)
{

}

void EcgGraph::setCoords(int x,int y)
{
    ECG_RX2=x;
    ECG_Ry=y;
}

void EcgGraph::isConnection(bool st)
{
    connection=st;
}

void EcgGraph::setEcgAdv(int x)
{
    adcValue=x;
}


void EcgGraph::EcgRender()
{
    getECG();
    pt.setX(_x++);
    if(buzz==true && (normalization>=0.2))
    {
        normalization=0.80;
        buzz=false;
    }
    pt.setY(ECG_Ry-((ECG_Ry-60)*normalization));
=======
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
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
    points<<pt;
    if(!(points.size()<ECG_RX2))
    {
        _x=0;
<<<<<<< HEAD
        points.clear();

    }
   update();

}

void EcgGraph::bpmTask()
{

    if(connection==true)
    {
        makeBuzz();
    }
}

void EcgGraph::makeBuzz()
{
    buzz=true;
    //make voice
=======
               points.clear();

    }

   i++;
   if(i==10)
   {
       i=0;
   }
    update();

>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
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
<<<<<<< HEAD

void EcgGraph::getECG()
{

    normalization=(adcValue)*0.00027751;
}




=======
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
