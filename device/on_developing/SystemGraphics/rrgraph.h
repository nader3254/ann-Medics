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
#define RR_RX2    527
#define RR_Ry     365
#define RR_RTime  40   /* 50 milli second */

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
private slots:
    void RRRender();

signals:
void rrChanged();


private:

 int   _rr=0;
 int   _x=0;
 int   _y=0;

 int i=0;

bool connection=false;
 QTimer *rr_t;
 QList <QPoint> points;
 QPoint pt;
void ConnectPoints(QPainter *painter);

};

#endif // RRGRAPH_H
