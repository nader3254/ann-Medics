#ifndef RRGRAPH_H
#define RRGRAPH_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QString>
#include <QPainter>
#include <QPen>
#include <QtMath>
#include <QTimer>
#include <QList>
#include <QPoint>

#define RR_RX1    0
#define RR_RTime  40   /* 40 milli second */

class rrgraph : public QQuickPaintedItem
{
    Q_PROPERTY(int rr  READ getrr  WRITE setrr  NOTIFY rrChanged    );
    Q_OBJECT
public:
    rrgraph(QQuickItem *parent = nullptr);
    void  paint(QPainter *painter);

    int   getrr();
    void  setrr(int rt);
    void isConnection(bool st);
public slots:
    void setCoords(int x,int y);
private slots:
    void RRRender();

signals:
void rrChanged();


private:

int RR_RX2;
int RR_Ry ;

 int   _rr=0;
 int   _x=0;
 int   _y=0;

 int i=0;

bool connection=false;
 QTimer *rr_t;
 QList <QPoint> points;
 QPoint pt;


};

#endif // RRGRAPH_H
