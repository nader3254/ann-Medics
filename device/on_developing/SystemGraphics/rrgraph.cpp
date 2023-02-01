#include "rrgraph.h"


rrgraph::rrgraph(QQuickItem *parent): QQuickPaintedItem(parent)
{
    rr_t=new QTimer(this);
    connect(rr_t, SIGNAL(timeout()), this, SLOT(RRRender()));
    rr_t->setInterval(RR_RTime);
    rr_t->start();
}

void rrgraph::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing,1);
    QPen p ;


       QFont font("Helvetica",18,QFont::Bold);
       painter->setFont(font);


       p.setColor(QColor(170, 255, 0 ,255));
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

int rrgraph::getrr()
{
   return _rr;
}

void rrgraph::setrr(int rt)
{
    if(_rr == rt)
            return;
          _rr = rt;
    update();
    emit rrChanged();
}

void rrgraph::isConnection(bool st)
{
    connection=st;
}

void rrgraph::RRRender()
{

    pt.setX(_x++);
    if(connection==true){pt.setY(RR_Ry-(25*sin(2*i*0.0174532925)));i++;}
    else {pt.setY(RR_Ry);}
    if(i==180){i=0;}
    points<<pt;
    if(!(points.size()<RR_RX2))
    {
        _x=0;
        points.clear();

    }
    update();

}
void rrgraph::ConnectPoints(QPainter *painter)
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
                    if(pnt.x()<RR_RX2)
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
                    if(pnt.x()<RR_RX2)
                             painter->drawPoint(pnt);
                }
            }

        }

    }

}
