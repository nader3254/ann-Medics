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

void rrgraph::RRRender()
{

    pt.setX(_x++);pt.setY(RR_Ry);
    points<<pt;
    if(!(points.size()<RR_RX2))
    {
        _x=0;
        points.clear();

    }


    update();

}
