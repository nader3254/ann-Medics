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

<<<<<<< HEAD
void rrgraph::isConnection(bool st)
{
     connection=st;
}

void rrgraph::setCoords(int x, int y)
{
    RR_RX2=x;
    RR_Ry=y;
}

void rrgraph::RRRender()
{

    pt.setX(_x++);
    if(connection==true){pt.setY(RR_Ry-((RR_Ry*0.08)*sin(2*i*0.0174532925)));i++;}
    else {pt.setY(RR_Ry);}
    if(i==180){i=0;}
=======
void rrgraph::RRRender()
{

    pt.setX(_x++);pt.setY(RR_Ry);
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
    points<<pt;
    if(!(points.size()<RR_RX2))
    {
        _x=0;
        points.clear();

    }
<<<<<<< HEAD
=======


>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
    update();

}
