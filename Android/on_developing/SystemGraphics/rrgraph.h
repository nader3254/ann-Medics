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
<<<<<<< HEAD
=======
#define RR_RX2    527
#define RR_Ry     340
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
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
<<<<<<< HEAD
    void isConnection(bool st);
public slots:
    void setCoords(int x,int y);
=======

>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
private slots:
    void RRRender();

signals:
void rrChanged();


private:

<<<<<<< HEAD
int RR_RX2;
int RR_Ry ;

=======
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
 int   _rr=0;
 int   _x=0;
 int   _y=0;

 int i=0;

<<<<<<< HEAD
bool connection=false;
=======

>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
 QTimer *rr_t;
 QList <QPoint> points;
 QPoint pt;


};

#endif // RRGRAPH_H
