#include "ecggraph.h"


EcgGraph::EcgGraph(QQuickItem *parent,QObject *obj): QQuickPaintedItem(parent)
{
    //QObject *graph = obj->findChild<QObject*>("ecg_graph");
   // ecg_graphics_ptr= qobject_cast<EcgGraph*>(graph);

    ecg_t=new QTimer(this);
    connect(ecg_t, SIGNAL(timeout()), this, SLOT(EcgRender()));
    ecg_t->setInterval(ECG_RTime);
    ecg_t->start();

    buzzTimer=new QTimer(this);
    connect(buzzTimer, SIGNAL(timeout()), this, SLOT(bpmTask()));
    buzzTimer->setInterval(880);
    buzzTimer->start();
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
    points<<pt;
    if(!(points.size()<ECG_RX2))
    {
        _x=0;
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

void EcgGraph::getECG()
{

    normalization=(adcValue)*0.00027751;
}




